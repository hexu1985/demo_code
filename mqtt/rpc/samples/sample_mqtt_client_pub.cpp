#include <iostream>
#include <string>
#include <cstdlib>
#include "MqttClientBase.hpp"

using namespace std;
using namespace mqtt_rpc;

const std::string DFLT_SERVER_ADDRESS	{ "tcp://localhost:1883" };
const std::string DFLT_CLIENT_ID		{ "sample_mqtt_client_pub" };
const std::string TOPIC					{ "hello" };

class MqttPubClient: public MqttClientBase {
public:
	MqttPubClient(const MqttClientSettings &settings): MqttClientBase(settings)
	{}

	void onDeliveryComplete(std::shared_ptr<mqtt::delivery_token> token) override
	{
		std::cout << "onDeliveryComplete for token: " << token.get() << std::endl;
	}

	MqttError publish(const std::string &topic, const std::string &msg)
	{
		auto pub_ret = MqttClientBase::publish(topic, msg.data(), msg.size());
		if (pub_ret.first) {
			std::cout << "publish wait for token: " << pub_ret.second.get() << std::endl;
			MqttClientBase::wait(pub_ret.second);
		}
		return pub_ret.first;
	}
};

int main(int argc, char *argv[])
{
	string	address  = (argc > 1) ? string(argv[1]) : DFLT_SERVER_ADDRESS,
			clientID = (argc > 2) ? string(argv[2]) : DFLT_CLIENT_ID;

	MqttClientSettings settings;
	settings.setBrokerAddress(address);
	settings.setClientID(clientID);

	MqttPubClient client(settings);

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

	ret = client.publish(TOPIC, "hello world!");
	if (!ret) {
		std::cout << "publish error: "
				<< ret.getType() << ", " << ret.getCode()
				<< std::endl;
		exit(1);
	}
	
	std::cout << "publish success" << std::endl;

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
