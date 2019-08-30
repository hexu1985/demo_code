#include "MqttRpcClientPack.hpp"
#include "dump_functions.hpp"
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>

using namespace std;
using namespace mqtt_rpc;
using namespace mini_utils;

int main(int argc, char *argv[])
{
	std::string client_id = "client1234";
	std::string payload = "hello world!";

	MqttRpcClientPack pack(client_id);
	pack.set_message_id_begin(1);

	vector<uint8_t> buffer;
	pack.packQueryPacket(buffer, "query|/test/a", payload.data(), payload.length());
	std::cout << "query packet:" << std::endl;
	dump(buffer.data(), buffer.size(), NULL);
	std::cout << std::endl;

	std::cout << "====================================================================\n\n";

	pack.packNotifyPacket(buffer, "notify|/test/a", payload.data(), payload.length());
	std::cout << "notify packet:" << std::endl;
	dump(buffer.data(), buffer.size(), NULL);
	std::cout << std::endl;

	return 0;
}
