#ifndef MQTT_RPC_MQTT_RPC_CLIENT_PACK_INC
#define MQTT_RPC_MQTT_RPC_CLIENT_PACK_INC

#include <string>
#include <vector>
#include <atomic>
#include <ctime>
#include "MqttRpcHeader.hpp"
#include "RandomNumber.hpp"

namespace mqtt_rpc {

class MqttRpcClientPack {
public:
	MqttRpcClientPack(const std::string &client_id): client_id_(client_id)
	{
		memset(&fix_header_, 0x00, sizeof(fix_header_));
		set_uint16_to_bigend(fix_header_.gw_proto_ver, DEFAULT_PRODUCT_PROTO_VER);
		set_uint16_to_bigend(fix_header_.product_id, DEFAULT_PRODUCT_ID);
		set_uint16_to_bigend(fix_header_.product_proto_ver, DEFAULT_PRODUCT_PROTO_VER);

		mini_utils::RandomNumber random(time(0));
		last_message_id_ = static_cast<uint32_t>(random.randInt(0, 40000)) * 100000;
	}

	void set_message_id_begin(uint32_t message_id)
	{
		last_message_id_ = message_id;
	}

	typedef uint32_t message_id_type;

	message_id_type packQueryPacket(std::vector<uint8_t> &buffer, 
		const std::string &method, const void *payload, size_t len)
	{
		return packClientImpl(buffer, method, payload, len, MESSAGE_TYPE_QUERY);
	}

	message_id_type packNotifyPacket(std::vector<uint8_t> &buffer, 
		const std::string &method, const void *payload, size_t len)
	{
		return packClientImpl(buffer, method, payload, len, MESSAGE_TYPE_NOTIFY);
	}

private:
	message_id_type packClientImpl(std::vector<uint8_t> &buffer, 
		const std::string &method, const void *payload, size_t len, 
		uint16_t message_type)
	{
		buffer.clear();
		size_t packet_length = header_length(method) + len;
		buffer.resize(packet_length);

		int offset = 0;

		// packet fix header
		memcpy(get_offset_ptr(buffer, offset), &fix_header_, SIZE_FIX_HEADER);
		offset += SIZE_FIX_HEADER;

		// packet message type
		pack_message_type(get_offset_ptr(buffer, offset), message_type);
		offset += SIZE_MESSAGE_TYPE_ITEM;

		// packet message id
		uint32_t message_id = generate_message_id();
		pack_message_id(get_offset_ptr(buffer, offset), message_id);
		offset += SIZE_MESSAGE_ID_ITEM;

		// packet client id
		pack_client_id(get_offset_ptr(buffer, offset), client_id_);
		offset += SIZE_CLIENT_ID_ITEM + client_id_.length();

		// packet method
		pack_method(get_offset_ptr(buffer, offset), method);
		offset += SIZE_METHOD_ITEM + method.length();

		// pack payload start
		pack_payload_start(get_offset_ptr(buffer, offset));
		offset += SIZE_PAYLOAD_START_ITEM;

		// pack payload
		pack_payload(get_offset_ptr(buffer, offset), payload, len);
		offset += len;

		return message_id;
	}

	size_t header_length(const std::string &method) const
	{
		static const size_t fix_length = SIZE_FIX_HEADER 
								+ SIZE_MESSAGE_TYPE_ITEM
								+ SIZE_MESSAGE_ID_ITEM
								+ SIZE_CLIENT_ID_ITEM 
								+ SIZE_METHOD_ITEM 
								+ SIZE_PAYLOAD_START_ITEM; 
		return fix_length + method.length() + client_id_.length();
	}

	static uint8_t *get_offset_ptr(std::vector<uint8_t> &buffer, int offset)
	{
		return buffer.data() + offset;
	}

	uint32_t generate_message_id()
	{
		return last_message_id_++;
	}

	void pack_message_type(uint8_t *ptr, uint16_t message_type)
	{
		MqttRpcMessageTypeItem *item = reinterpret_cast<MqttRpcMessageTypeItem *>(ptr);
		set_uint16_to_bigend(item->type, TYPE_MESSAGE_TYPE);
		set_uint16_to_bigend(item->data, message_type);
	}

	void pack_message_id(uint8_t *ptr, uint32_t message_id)
	{
		MqttRpcMessageIDItem *item = reinterpret_cast<MqttRpcMessageIDItem *>(ptr);
		set_uint16_to_bigend(item->type, TYPE_MESSAGE_ID);
		set_uint32_to_bigend(item->data, message_id);
	}

	void pack_client_id(uint8_t *ptr, const std::string &client_id)
	{
		MqttRpcClientIDItem *item = reinterpret_cast<MqttRpcClientIDItem *>(ptr);
		set_uint16_to_bigend(item->type, TYPE_CLIENT_ID); 
		set_str_to_bigend(item->length, item->data, client_id);
	}

	void pack_method(uint8_t *ptr, const std::string &method)
	{
		MqttRpcMethodItem *item = reinterpret_cast<MqttRpcMethodItem *>(ptr);
		set_uint16_to_bigend(item->type, TYPE_METHOD); 
		set_str_to_bigend(item->length, item->data, method);
	}

	void pack_payload_start(uint8_t *ptr)
	{
		MqttRpcPayloadStartItem *item = reinterpret_cast<MqttRpcPayloadStartItem *>(ptr);
		set_uint16_to_bigend(item->type, TYPE_PAYLOAD_START); 
		set_uint16_to_bigend(item->data, VALUE_PAYLOAD_START);
	}

	void pack_payload(uint8_t *ptr, const void *payload, size_t len)
	{
		memcpy(ptr, payload, len);
	}

private:
	MqttRpcFixHeader fix_header_;
	std::string client_id_;
	std::atomic<uint32_t> last_message_id_;
};

}	// namespace mqtt_rpc

#endif
