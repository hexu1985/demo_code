#ifndef MQTT_RPC_MQTT_RPC_PROTOCOL_INC
#define MQTT_RPC_MQTT_RPC_PROTOCOL_INC

#include <cstdint>
#include <cstring>
#include <string>

namespace mqtt_rpc {

/**
 * @brief format: gw_proto_ver|reserved|product_id|product_proto_ver -> uint16|uint16|uint16|uint16
 */
struct MqttRpcFixHeader {
	uint8_t gw_proto_ver[2];
	uint8_t reserved[2];
	uint8_t product_id[2];
	uint8_t product_proto_ver[2];
};

struct MqttRpcItemBase {
	uint8_t type[2];
};

/**
 * @brief format: type|value -> uint16|uint16
 */
struct MqttRpcU16Item {
	uint8_t type[2];
	uint8_t data[2];
};

/**
 * @brief format: type|value -> uint16|uint32
 */
struct MqttRpcU32Item {
	uint8_t type[2];
	uint8_t data[4];
};

/**
 * @brief format: type|data -> uint16|(uint16|uint8s)
 */
struct MqttRpcStrItem {
	uint8_t type[2];
	uint8_t length[2];
	uint8_t data[0];
};

inline
uint16_t get_uint16_from_bigend(const uint8_t *data)
{
	return (((uint16_t) data[0]) << 8) | ((uint16_t) data[1]);
}

inline
void set_uint16_to_bigend(uint8_t *data, uint16_t value)
{
	data[0] = (value >> 8);
	data[1] = value & 0xff;
}

inline
uint32_t get_uint32_from_bigend(const uint8_t *data)
{
	return (((uint32_t) data[0]) << 24) |
			(((uint32_t) data[1]) << 16) |
			(((uint32_t) data[2]) << 8) |
			((uint32_t) data[3]);
}

inline
void set_uint32_to_bigend(uint8_t *data, uint32_t value)
{
	data[0] = value >> 24;
	data[1] = value >> 16;
	data[2] = value >> 8;
	data[3] = value & 0xff;
}

inline
std::string get_str_from_bigend(const uint8_t *length, const uint8_t *data)
{
	size_t n = get_uint16_from_bigend(length);
	return std::string(reinterpret_cast<const char *>(data), n);
}

inline
void set_str_to_bigend(uint8_t *length, uint8_t *data, const std::string &value)
{
	set_uint16_to_bigend(length, static_cast<uint16_t>(value.length()));
	std::memcpy(data, value.data(), value.length());
}

}	// namespace mqtt_rpc

#endif
