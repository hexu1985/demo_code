#include <iostream>
#include <string>
#include "MqttClientBase.hpp"
#include "MqttRpcUnpack.hpp"
#include "MqttRpcServerPack.hpp"
#include "dump_functions.hpp"

using namespace std;
using namespace mqtt_rpc;
using namespace mini_utils;

const std::string DFLT_SERVER_ADDRESS	{ "tcp://localhost:1883" };
const std::string DFLT_CLIENT_ID		{ "sample_mqtt_rpc_server_query_stub" };
const std::string TOPIC					{ "hello" };

class MqttSubClient: public MqttClientBase {
public:
	MqttSubClient(const MqttClientSettings &settings): MqttClientBase(settings)
	{}

	void onMessageArrived(std::shared_ptr<const mqtt::message> msg) override
	{
		std::cout << "onMessageArrived" << std::endl;
		std::cout << "\ttopic: '" << get_topic(msg) << "'" << std::endl;
		std::cout << "\tpayload: " << std::endl;
		auto payload = get_payload(msg);
		dump((const uint8_t *) payload.data(), payload.size(), NULL);

		MqttRpcUnpack unpack;
		MqttError ret;
		ret = unpack.unpack((const uint8_t *) payload.data(), payload.size());
		if (!ret) {
			std::cout << "unpack error: " << ret.getType() << ", " << ret.getCode() << std::endl;
			return;
		}

		std::cout << "unpack success\n";

		if (unpack.hasMessageType()) {
			std::cout << "\tmessage type: " << std::hex << unpack.getMessageType() << std::endl;
		}

		if (unpack.hasMessageID()) {
			std::cout << "\tmessage id: " << std::dec << unpack.getMessageID() << std::endl;
		}

		if (unpack.hasClientID()) {
			std::cout << "\tclient id: " << unpack.getClientID() << std::endl;
		}

		if (unpack.hasMethod()) {
			std::cout << "\tmethod: " << unpack.getMethod() << std::endl;
		}

		if (unpack.hasPayload()) {
			std::cout << "\trpc payload: " 
					<< std::string((const char *) unpack.getPayload(),
							unpack.getPayloadLength())
					<< std::endl;
		}

		if (!unpack.hasClientID() || !unpack.hasMessageID()) {
			std::cout << "no client id or no message id" << std::endl;
			return;
		}

		std::thread(&MqttSubClient::do_send_reply, this, unpack.getClientID(), unpack.getMessageID()).detach();
	}

	void do_send_reply(std::string client_id, uint32_t message_id)
	{
		std::cout << "send reply to client: " << client_id << std::endl;
		std::string reply_topic = TOPIC + "/" + client_id; 
		std::string answer_str = "test answer!";
		std::vector<uint8_t> buffer;
		pack_.packReplyPacket(buffer, client_id, message_id, 0, answer_str.data(), answer_str.size());
		MqttClientBase::publish(reply_topic, buffer.data(), buffer.size());
	}

private:
	MqttRpcServerPack pack_;
};

int main(int argc, char *argv[])
{
	string	address  = (argc > 1) ? string(argv[1]) : DFLT_SERVER_ADDRESS,
			clientID = (argc > 2) ? string(argv[2]) : DFLT_CLIENT_ID;

	MqttClientSettings settings;
	settings.setBrokerAddress(address);
	settings.setClientID(clientID);

	MqttSubClient client(settings);

	MqttError ret = client.connect();
	if (!ret) {
		std::cout << "Connect to " << settings.getBrokerAddress()
				<< " failure, clientID: " << settings.getClientID()
				<< " error: " << ret.getType() << ", " << ret.getCode()
				<< std::endl;
		exit(1);
	}

	std::cout << "Connect to " << settings.getBrokerAddress()
		<< " success, clientID: " << settings.getClientID()
		<< std::endl;

	ret = client.subscribe(TOPIC);

	if (!ret) {
		std::cout << "subscribe error: "
				<< ret.getType() << ", " << ret.getCode()
				<< std::endl;
		exit(1);
	}

	std::cout << "subscribe success " << std::endl;

	std::cout << "\nPress Q<Enter> to quit\n" << std::endl;
	// wait for quit
	while (std::tolower(std::cin.get()) != 'q')
		;

	ret = client.disconnect();

	if (!ret) {
		std::cout << "disconnect error: "
				<< ret.getType() << ", " << ret.getCode()
				<< std::endl;
		exit(1);
	}

	std::cout << "disconnect success " << std::endl;

	return 0;
}
