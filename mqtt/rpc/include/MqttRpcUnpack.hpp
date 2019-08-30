#ifndef MQTT_RPC_MQTT_RPC_UNPACK_INC
#define MQTT_RPC_MQTT_RPC_UNPACK_INC

#ifdef DEBUG
#include <iostream>
#include "dump_functions.hpp"
#endif

#include "MqttError.hpp"
#include "MqttRpcErrorEnum.hpp"
#include "MqttRpcHeader.hpp"

namespace mqtt_rpc {

class MqttRpcUnpack {
public:
	MqttRpcUnpack() {}

	MqttError unpack(const uint8_t *packet, size_t packet_length)
	{
#ifdef DEBUG
		std::cout << "unpackReplyPacket(" << packet_length << "): " << std::endl;
		mini_utils::dump(packet, packet_length, nullptr);
		std::cout << std::endl;
#endif

		size_t offset = 0;
		MqttError ret;
		ret = check_packet_length(packet_length);
		if (!ret) {
#ifdef DEBUG
			std::cout << "check_packet_length fail!" << std::endl;
#endif
			return ret;
		}

		fix_header_ = reinterpret_cast<const MqttRpcFixHeader *>(packet+offset);
		ret = check_fix_header();
		if (!ret) {
#ifdef DEBUG
			std::cout << "check_fix_header fail!" << std::endl;
#endif
			return ret;
		}
		offset += SIZE_FIX_HEADER;
		
		while (payload_start_item_ == nullptr && offset < packet_length) {
			uint16_t item_type = get_item_type(packet+offset);
			switch (item_type) {
			case TYPE_MESSAGE_TYPE:
				message_type_item_ = reinterpret_cast<const MqttRpcMessageTypeItem *>(packet+offset);
				offset += SIZE_MESSAGE_TYPE_ITEM; 
				break;
			case TYPE_MESSAGE_ID:
				message_id_item_ = reinterpret_cast<const MqttRpcMessageIDItem *>(packet+offset);
				offset += SIZE_MESSAGE_ID_ITEM;
				break;
			case TYPE_CLIENT_ID:
				client_id_item_ = reinterpret_cast<const MqttRpcClientIDItem *>(packet+offset);
				offset += SIZE_CLIENT_ID_ITEM + get_uint16_from_bigend(client_id_item_->length);
				break;
			case TYPE_METHOD:
				method_item_ = reinterpret_cast<const MqttRpcMethodItem *>(packet+offset);
				offset += SIZE_CLIENT_ID_ITEM + get_uint16_from_bigend(method_item_->length);
				break;
			case TYPE_RETURN_CODE:
				return_code_item_ = reinterpret_cast<const MqttRpcReturnCodeItem *>(packet+offset);
				offset += SIZE_RETURN_CODE_ITEM;
				break;
			case TYPE_PAYLOAD_START:
				payload_start_item_ = reinterpret_cast<const MqttRpcPayloadStartItem *>(packet+offset);
				ret = check_payload_start_item();
				if (!ret) {
#ifdef DEBUG
					std::cout << "check_payload_start_item fail!" << std::endl;
#endif
					return ret;
				}
				offset += SIZE_PAYLOAD_START_ITEM;
				payload_ = packet+offset;
				payload_length_ = packet_length - offset;
				break;
			default:
				return make_rpc_lib_error(MQTT_RPC_PACKET_INVALID_VARIABLE_HEADER);
			}
		}
		return MqttError::no_error();
	}

	bool hasMessageType() const
	{
		return message_type_item_ != nullptr;
	}

	uint16_t getMessageType() const
	{
		return get_uint16_from_bigend(message_type_item_->data);
	}

	bool hasMessageID() const
	{
		return message_id_item_ != nullptr;
	}

	uint32_t getMessageID() const
	{
		return get_uint32_from_bigend(message_id_item_->data);
	}

	bool hasClientID() const
	{
		return client_id_item_ != nullptr;
	}

	std::string getClientID() const
	{
		return get_str_from_bigend(client_id_item_->length, client_id_item_->data);
	}

	bool hasMethod() const
	{
		return method_item_ != nullptr;
	}

	std::string getMethod() const
	{
		return get_str_from_bigend(method_item_->length, method_item_->data);
	}

	bool hasPayload() const
	{
		return payload_ != nullptr && payload_length_ != 0;
	}

	const uint8_t *getPayload() const
	{
		return payload_;
	}

	size_t getPayloadLength() const
	{
		return payload_length_;
	}

private:
	MqttError check_packet_length(size_t packet_length)
	{
		if (packet_length < SIZE_FIX_HEADER)
			return make_rpc_lib_error(MQTT_RPC_PACKET_TOO_SHORT);
		else
			return MqttError::no_error();
	}

	MqttError check_fix_header()
	{
		if ((get_uint16_from_bigend(fix_header_->gw_proto_ver) != DEFAULT_PRODUCT_PROTO_VER) 
			|| (get_uint16_from_bigend(fix_header_->product_id) != DEFAULT_PRODUCT_ID)
			|| (get_uint16_from_bigend(fix_header_->product_proto_ver) != DEFAULT_PRODUCT_PROTO_VER)) {
			return make_rpc_lib_error(MQTT_RPC_PACKET_INVALID_FIX_HEADER);
		} else {
			return MqttError::no_error();
		}
	}

	MqttError check_payload_start_item()
	{
		if (get_uint16_from_bigend(payload_start_item_->data) != VALUE_PAYLOAD_START)
			return make_rpc_lib_error(MQTT_RPC_PACKET_INVALID_VARIABLE_HEADER); 
		else
			return MqttError::no_error();
	}

	uint16_t get_item_type(const uint8_t *item)
	{
		return get_uint16_from_bigend(item);
	}

private:
	const MqttRpcFixHeader *fix_header_ = nullptr;
	const MqttRpcMessageTypeItem *message_type_item_ = nullptr;
	const MqttRpcMessageIDItem *message_id_item_ = nullptr;
	const MqttRpcClientIDItem *client_id_item_ = nullptr;
	const MqttRpcMethodItem *method_item_ = nullptr;
	const MqttRpcReturnCodeItem *return_code_item_ = nullptr;
	const MqttRpcPayloadStartItem *payload_start_item_ = nullptr;
	const uint8_t *payload_ = nullptr;
	size_t payload_length_ = 0;
};

}	// namespace mqtt_rpc

#endif
