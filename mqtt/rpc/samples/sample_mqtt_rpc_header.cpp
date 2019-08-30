#include "MqttRpcHeader.hpp"
#include "dump_functions.hpp"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace mqtt_rpc;
using namespace mini_utils;

int main(int argc, char *argv[])
{
	// ============================================================
	// MqttRpcFixHeader test
	// ============================================================
	MqttRpcFixHeader fix_header = { 0x01, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02 };

	std::cout << "length of MqttRpcFixHeader: " << sizeof (MqttRpcFixHeader) << std::endl; 
	std::cout << "fix_header: " << std::endl;
	dump((uint8_t *) &fix_header, sizeof (fix_header), NULL);

	// ============================================================
	// MqttRpcU16Item test
	// ============================================================
	MqttRpcU16Item message_type;
	set_uint16_to_bigend(message_type.type, 0x0001);
	set_uint16_to_bigend(message_type.data, 0x0002);
	
	std::cout << "length of MqttRpcU16Item: " << sizeof (MqttRpcU16Item) << std::endl; 
	std::cout << "message_type: " << std::endl;
	dump((uint8_t *) &message_type, sizeof (message_type), NULL);

	// ============================================================
	// MqttRpcU32Item test
	// ============================================================
	uint32_t count = 15;
	MqttRpcU32Item message_id;
	set_uint16_to_bigend(message_id.type, 0x0002);
	set_uint32_to_bigend(message_id.data, count);

	std::cout << "length of MqttRpcU32Item: " << sizeof (MqttRpcU32Item) << std::endl; 
	std::cout << "message_id: " << std::endl;
	dump((uint8_t *) &message_id, sizeof (message_id), NULL);

	std::cout << "message_id.data: " << get_uint32_from_bigend(message_id.data) << endl;

	// ============================================================
	// MqttRpcStrItem test
	// ============================================================
	std::string str = "hello world!";
	int method_length = sizeof(MqttRpcStrItem) + str.size();
	MqttRpcStrItem *method = (MqttRpcStrItem *) new uint8_t[method_length];
	set_uint16_to_bigend(method->type, 0x0004);
	set_str_to_bigend(method->length, method->data, str);

	std::cout << "length of MqttRpcStrItem: " << sizeof (MqttRpcStrItem) << std::endl; 
	std::cout << "method: " << std::endl;
	dump((uint8_t *) method, method_length , NULL);

	std::cout << "method.data: " << get_str_from_bigend(method->length, method->data) << endl;
	
	return 0;
}
