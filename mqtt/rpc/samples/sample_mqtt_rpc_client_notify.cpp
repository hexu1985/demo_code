#include <iostream>
#include <string>
#include <cstdlib>
#include "MqttRpcClient.hpp"

using namespace std;
using namespace mqtt_rpc;

const std::string DFLT_SERVER_ADDRESS	{ "tcp://localhost:1883" };
const std::string DFLT_CLIENT_ID		{ "sample_mqtt_rpc_client_notify" };
const std::string TOPIC					{ "hello" };
const std::string METHOD				{ "notify|test" };

int main(int argc, char *argv[])
{
	string	address  = (argc > 1) ? string(argv[1]) : DFLT_SERVER_ADDRESS,
			clientID = (argc > 2) ? string(argv[2]) : DFLT_CLIENT_ID;

	MqttClientSettings settings;
	settings.setBrokerAddress(address);
	settings.setClientID(clientID);

	MqttRpcClient::set_subscribe_topic(settings, TOPIC+"/"+clientID);
	MqttRpcClient::set_publish_topic(settings, TOPIC);

	MqttRpcClient client(settings);

	MqttError ret = client.open();
	if (!ret) {
		std::cout << "open error: " 
				<< ret.getType() << ", " << ret.getCode()
				<< std::endl;
		exit(1);
	}

	std::cout << "open success!" << std::endl; 

	std::string payload = "hello world!";
	ret = client.notify(METHOD, payload.data(), payload.length());
	if (!ret) {
		std::cout << "notify error: "
				<< ret.getType() << ", " << ret.getCode()
				<< std::endl;
		exit(1);
	}
	
	std::cout << "notify success" << std::endl;

	ret = client.close();

	if (!ret) {
		std::cout << "close error: "
				<< ret.getType() << ", " << ret.getCode()
				<< std::endl;
		exit(1);
	}

	std::cout << "close success " << std::endl;

	return 0;
}
