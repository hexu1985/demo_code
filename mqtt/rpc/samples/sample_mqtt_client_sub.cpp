#include <iostream>
#include <string>
#include "MqttClientBase.hpp"

using namespace std;
using namespace mqtt_rpc;

const std::string DFLT_SERVER_ADDRESS	{ "tcp://localhost:1883" };
const std::string DFLT_CLIENT_ID		{ "sample_mqtt_client_sub" };
const std::string TOPIC					{ "hello" };

class MqttSubClient: public MqttClientBase {
public:
	MqttSubClient(const MqttClientSettings &settings): MqttClientBase(settings)
	{}

	void onMessageArrived(std::shared_ptr<const mqtt::message> msg) override
	{
		std::cout << "onMessageArrived" << std::endl;
		std::cout << "\ttopic: '" << get_topic(msg) << "'" << std::endl;
		std::cout << "\tpayload: '" << get_payload(msg) << "'\n" << std::endl;
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
