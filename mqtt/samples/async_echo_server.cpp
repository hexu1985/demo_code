
#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>	// For sleep
#include <atomic>
#include <chrono>
#include <cstring>
#include "mqtt/async_client.h"

using namespace std;

const std::string DFLT_SERVER_ADDRESS	{ "tcp://localhost:1883" };
const std::string DFLT_CLIENT_ID		{ "async_echo_server" };

const std::string SERVER_TOPIC("/req/echo");
const std::string CLIENT_TOPIC("/resp/echo");
const int	QOS = 1;
const char* LWT_PAYLOAD = "Last will and testament.";

const int	N_RETRY_ATTEMPTS = 5;

/**
 * A base action listener.
 */
class PubActionListener : public virtual mqtt::iaction_listener
{
protected:
	void on_failure(const mqtt::token& tok) override {
		cout << "\t PubListener failure for token: "
			<< tok.get_message_id() << endl;
	}

	void on_success(const mqtt::token& tok) override {
		cout << "\tPubListener success for token: "
			<< tok.get_message_id() << endl;
	}
};

// Callbacks for the success or failures of requested actions.
// This could be used to initiate further action, but here we just log the
// results to the console.

class SubActionListener : public virtual mqtt::iaction_listener
{
	std::string name_;

	void on_failure(const mqtt::token& tok) override {
		std::cout << name_ << " failure";
		if (tok.get_message_id() != 0)
			std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
		std::cout << std::endl;
	}

	void on_success(const mqtt::token& tok) override {
		std::cout << name_ << " success";
		if (tok.get_message_id() != 0)
			std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
		auto top = tok.get_topics();
		if (top && !top->empty())
			std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
		std::cout << std::endl;
	}

public:
	SubActionListener(const std::string& name) : name_(name) {}
};

/**
 * Local callback & listener class for use with the client connection.
 * This is primarily intended to receive messages, but it will also monitor
 * the connection to the broker. If the connection is lost, it will attempt
 * to restore the connection and re-subscribe to the topic.
 */
class Callback : public virtual mqtt::callback,
					public virtual mqtt::iaction_listener

{
	// Counter for the number of connection retries
	int nretry_;
	// The MQTT client
	mqtt::async_client& cli_;
	// Options to use if we need to reconnect
	mqtt::connect_options& connOpts_;
	// An action listener to display the result of actions.
	SubActionListener subListener_;
	
	string clientID_;

	PubActionListener pubActionListener_;

	// This deomonstrates manually reconnecting to the broker by calling
	// connect() again. This is a possibility for an application that keeps
	// a copy of it's original connect_options, or if the app wants to
	// reconnect with different options.
	// Another way this can be done manually, if using the same options, is
	// to just call the async_client::reconnect() method.
	void reconnect() {
		std::this_thread::sleep_for(std::chrono::milliseconds(2500));
		try {
			cli_.connect(connOpts_, nullptr, *this);
		}
		catch (const mqtt::exception& exc) {
			std::cerr << "Error: " << exc.what() << std::endl;
			exit(1);
		}
	}

	// Re-connection failure
	void on_failure(const mqtt::token& tok) override {
		std::cout << "Connection attempt failed" << std::endl;
		if (++nretry_ > N_RETRY_ATTEMPTS)
			exit(1);
		reconnect();
	}

	// (Re)connection success
	// Either this or connected() can be used for callbacks.
	void on_success(const mqtt::token& tok) override {}

	// (Re)connection success
	void connected(const std::string& cause) override {
		std::cout << "\nConnection success" << std::endl;
		std::cout << "\nSubscribing to topic '" << SERVER_TOPIC << "'\n"
			<< "\tfor client " << clientID_
			<< " using QoS" << QOS << "\n"
			<< "\nPress Q<Enter> to quit\n" << std::endl;

		cli_.subscribe(SERVER_TOPIC, QOS, nullptr, subListener_);
	}

	// Callback for when the connection is lost.
	// This will initiate the attempt to manually reconnect.
	void connection_lost(const std::string& cause) override {
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;

		std::cout << "Reconnecting..." << std::endl;
		nretry_ = 0;
		reconnect();
	}

	// Callback for when a message arrives.
	void message_arrived(mqtt::const_message_ptr msg) override {
		std::cout << "Message arrived" << std::endl;
		std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
		std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;

		// echo
		mqtt::message_ptr echo_msg = mqtt::make_message(CLIENT_TOPIC, msg->get_payload_ref(), QOS, false);
		cli_.publish(echo_msg, nullptr, pubActionListener_);
	}

	void delivery_complete(mqtt::delivery_token_ptr token) override {
		cout << "\tDelivery complete for token: "
			<< (token ? token->get_message_id() : -1) << endl;
	}

public:
	Callback(mqtt::async_client& cli, mqtt::connect_options& connOpts, 
			const string &clientID)
				: nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription"), clientID_(clientID) {}
};

int main(int argc, char *argv[])
{
	string	address  = (argc > 1) ? string(argv[1]) : DFLT_SERVER_ADDRESS;
	string  clientID = (argc > 2) ? string(argv[2]) : DFLT_CLIENT_ID;

	// pub client connect
	cout << "Initializing for server '" << address << "'..." << endl;
	mqtt::async_client echo_server(address, clientID);

	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);

	Callback cb(echo_server, connOpts, clientID);
	echo_server.set_callback(cb);

	cout << "  ...OK" << endl;

	cout << "\nConnecting..." << endl;
	mqtt::token_ptr conntok = echo_server.connect(connOpts);
	cout << "Waiting for the connection..." << endl;
	conntok->wait();
	cout << "  ...OK" << endl;

	// wait for quit
	while (std::tolower(std::cin.get()) != 'q')
		;

	// Double check that there are no pending tokens

	auto toks = echo_server.get_pending_delivery_tokens();
	if (!toks.empty())
		cout << "Error: There are pending delivery tokens!" << endl;

	// Disconnect

	try {
		std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
		echo_server.disconnect()->wait();
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}

	return 0;
}
