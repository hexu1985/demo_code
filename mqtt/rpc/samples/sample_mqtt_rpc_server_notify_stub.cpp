#include <iostream>
#include <string>
#include <cstdlib>
#include "MqttClientBase.hpp"
#include "MqttRpcUnpack.hpp"
#include "dump_functions.hpp"

using namespace std;
using namespace mqtt_rpc;
using namespace mini_utils;

const std::string DFLT_SERVER_ADDRESS	{ "tcp://localhost:1883" };
const std::string DFLT_CLIENT_ID		{ "sample_mqtt_rpc_server_notify_stub" };
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
	}
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
	while (tolower(std::cin.get()) != 'q')
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
