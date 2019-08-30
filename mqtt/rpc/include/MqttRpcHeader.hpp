#ifndef MQTT_RPC_MQTT_RPC_HEADER_INC
#define MQTT_RPC_MQTT_RPC_HEADER_INC

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
 * @brief format: type|length|data -> uint16|uint16|uint8s
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

typedef MqttRpcU16Item MqttRpcMessageTypeItem;
typedef MqttRpcU32Item MqttRpcMessageIDItem;
typedef MqttRpcStrItem MqttRpcClientIDItem;
typedef MqttRpcStrItem MqttRpcMethodItem;
typedef MqttRpcU16Item MqttRpcReturnCodeItem;
typedef MqttRpcU16Item MqttRpcPayloadStartItem;

// fix header
constexpr uint16_t DEFAULT_GW_PROTO_VER      = 0x0001;
constexpr uint16_t DEFAULT_PRODUCT_ID        = 0x0001;
constexpr uint16_t DEFAULT_PRODUCT_PROTO_VER = 0x0001;

constexpr size_t SIZE_FIX_HEADER = sizeof (MqttRpcFixHeader);

// variable item type
constexpr uint16_t TYPE_MESSAGE_TYPE  = 0x0001;
constexpr uint16_t TYPE_MESSAGE_ID    = 0x0002;
constexpr uint16_t TYPE_CLIENT_ID     = 0x0003;
constexpr uint16_t TYPE_METHOD        = 0x0004;
constexpr uint16_t TYPE_RETURN_CODE   = 0x0005;
constexpr uint16_t TYPE_PAYLOAD_START = 0xfffe;

// variable item size
constexpr size_t SIZE_MESSAGE_TYPE_ITEM  = sizeof (MqttRpcMessageTypeItem);
constexpr size_t SIZE_MESSAGE_ID_ITEM    = sizeof (MqttRpcMessageIDItem);
constexpr size_t SIZE_CLIENT_ID_ITEM     = sizeof (MqttRpcClientIDItem);
constexpr size_t SIZE_METHOD_ITEM        = sizeof (MqttRpcMethodItem);
constexpr size_t SIZE_RETURN_CODE_ITEM   = sizeof (MqttRpcReturnCodeItem);
constexpr size_t SIZE_PAYLOAD_START_ITEM = sizeof (MqttRpcPayloadStartItem);

// message type
constexpr uint16_t MESSAGE_TYPE_QUERY  = 0x0001;
constexpr uint16_t MESSAGE_TYPE_REPLY  = 0x0002;
constexpr uint16_t MESSAGE_TYPE_NOTIFY = 0x0003;

// payload start
constexpr uint16_t VALUE_PAYLOAD_START = 0xfffe;

}	// namespace mqtt_rpc

#endif
