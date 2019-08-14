
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
const std::string DFLT_CLIENT_ID		{ "mqttpp_ping" };

const std::string TOPIC("hello");
const int	QOS = 1;
const char* LWT_PAYLOAD = "Last will and testament.";

const int	N_RETRY_ATTEMPTS = 5;

const int MAX_PING_PKG_NUM = 50;
using Clock = chrono::high_resolution_clock;
using TimePoint = Clock::time_point;
TimePoint g_pub_time;
TimePoint g_sub_time;
TimePoint pub_time_array[MAX_PING_PKG_NUM] = {};
TimePoint sub_time_array[MAX_PING_PKG_NUM] = {};

int g_ping_pkg_num = 0; 

char g_send_msg[1] = {'A'}; 

// Convert a duration to a count of milliseconds
template <class Rep, class Period>
double msec(const std::chrono::duration<Rep, Period>& dur) {
	return chrono::duration_cast<chrono::microseconds>(dur).count() / 1000.0;
}

/**
 * A callback class for use with the main MQTT client.
 */
class PubCallback : public virtual mqtt::callback
{
public:
	void connection_lost(const string& cause) override {
		cout << "\nPubConnection lost" << endl;
		if (!cause.empty())
			cout << "\tcause: " << cause << endl;
	}

	void delivery_complete(mqtt::delivery_token_ptr tok) override {
		cout << "\tPubDelivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << endl;
	}
};

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
	mqtt::async_client& pubCli_;
	PubActionListener pubActionListener_;

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

		// pub
		mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC, g_send_msg, 1, QOS, false);
		g_send_msg[0] += 1;
		g_pub_time = Clock::now(); 
		pubCli_.publish(pubmsg, nullptr, pubActionListener_);
	}

public:
	SubActionListener(const std::string& name, mqtt::async_client& pubCli) : name_(name), pubCli_(pubCli) {}
};

/**
 * Local callback & listener class for use with the client connection.
 * This is primarily intended to receive messages, but it will also monitor
 * the connection to the broker. If the connection is lost, it will attempt
 * to restore the connection and re-subscribe to the topic.
 */
class SubCallback : public virtual mqtt::callback,
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

	mqtt::async_client& pubCli_;
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
		std::cout << "\nSubConnection success" << std::endl;
		std::cout << "\nSubscribing to topic '" << TOPIC << "'\n"
			<< "\tfor client " << clientID_
			<< " using QoS" << QOS << "\n"
			<< "\nPress Q<Enter> to quit\n" << std::endl;

		cli_.subscribe(TOPIC, QOS, nullptr, subListener_);
	}

	// Callback for when the connection is lost.
	// This will initiate the attempt to manually reconnect.
	void connection_lost(const std::string& cause) override {
		std::cout << "\nSubConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;

		std::cout << "SubReconnecting..." << std::endl;
		nretry_ = 0;
		reconnect();
	}

	// Callback for when a message arrives.
	void message_arrived(mqtt::const_message_ptr msg) override {
		g_sub_time = Clock::now();
		std::cout << "SubMessage arrived" << std::endl;
		std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
		std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;
		std::cout << "\ttime=" << msec(g_sub_time-g_pub_time) << " ms" << std::endl;

		g_ping_pkg_num++; 
		if (g_ping_pkg_num >= MAX_PING_PKG_NUM)
			return;

		// pub
		mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC, g_send_msg, 1, QOS, false);
		g_send_msg[0] += 1;
		g_pub_time = Clock::now(); 
		pubCli_.publish(pubmsg, nullptr, pubActionListener_);
	}

	void delivery_complete(mqtt::delivery_token_ptr token) override {}

public:
	SubCallback(mqtt::async_client& cli, mqtt::connect_options& connOpts, 
			const string &clientID, mqtt::async_client& pubCli)
				: nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription", pubCli), clientID_(clientID), pubCli_(pubCli) {}
};

int main(int argc, char *argv[])
{
	string	address  = (argc > 1) ? string(argv[1]) : DFLT_SERVER_ADDRESS;
	string  clientID = (argc > 2) ? string(argv[2]) : DFLT_CLIENT_ID;

	// pub client connect
	cout << "Initializing for server '" << address << "'..." << endl;
	mqtt::async_client pub_client(address, clientID+".pub");

	PubCallback pub_cb;
	pub_client.set_callback(pub_cb);

	mqtt::connect_options pub_conopts;
	mqtt::message willmsg(TOPIC, LWT_PAYLOAD, 1, true);
	mqtt::will_options will(willmsg);
	pub_conopts.set_will(will);
#ifdef USE_MQTTVERSION_5
	pub_conopts.set_mqtt_version(MQTTVERSION_5);
	pub_conopts.set_clean_start(true);
#endif

	cout << "  ...OK" << endl;

	cout << "\nPubConnecting..." << endl;
	mqtt::token_ptr conntok = pub_client.connect(pub_conopts);
	cout << "PubWaiting for the connection..." << endl;
	conntok->wait();
	cout << "  ...OK" << endl;

	// sub client connect
	mqtt::connect_options sub_connopts;
	sub_connopts.set_keep_alive_interval(20);
#ifdef USE_MQTTVERSION_5
	sub_connopts.set_mqtt_version(MQTTVERSION_5);
	sub_connopts.set_clean_start(true);
#else
	sub_connopts.set_clean_session(true);
#endif

	mqtt::async_client sub_client(address, clientID+".sub");

	SubCallback sub_cb(sub_client, sub_connopts, clientID+".sub", pub_client);
	sub_client.set_callback(sub_cb);

	std::cout << "Connecting to the MQTT server..." << std::flush;
	sub_client.connect(sub_connopts, nullptr, sub_cb);

	// wait for quit
	while (std::tolower(std::cin.get()) != 'q')
		;


	// Double check that there are no pending tokens

	auto toks = pub_client.get_pending_delivery_tokens();
	if (!toks.empty())
		cout << "Error: There are pending delivery tokens!" << endl;

	// Disconnect
	cout << "\nDisconnecting..." << endl;
	conntok = pub_client.disconnect();
	conntok->wait();
	cout << "  ...OK" << endl;

	// Disconnect

	try {
		std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
		sub_client.disconnect()->wait();
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}

	return 0;
}
