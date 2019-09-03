#include "MqttRpcClient.hpp"
#include "MqttRpcErrorEnum.hpp"
#include "MqttRpcUnpack.hpp"
#include "mqtt/message.h"

#ifdef DEBUG
#include "dump_functions.hpp"
#include <iostream>
#endif

namespace mqtt_rpc {

namespace {

const static std::string RPC_CLIENT_SUBSCRIBE_TOPIC = "MqttRpcClient.subscribe_topic";

const static std::string RPC_CLIENT_PUBLISH_TOPIC = "MqttRpcClient.publish_topic";

}	// namespace

MqttRpcClient::MqttRpcClient(const MqttClientSettings &settings): 
	MqttClientBase(settings),
	pack_(settings.getClientID())
{
	subscribe_topic_ = get_subscribe_topic(settings);
	publish_topic_ = get_publish_topic(settings);
}

MqttRpcClient::~MqttRpcClient()
{
}

MqttError MqttRpcClient::open()
{
	if (subscribe_topic_.empty())
		return make_rpc_lib_error(MQTT_RPC_CLIENT_SUBSCRIBE_TOPIC_IS_NULL);
	if (publish_topic_.empty())
		return make_rpc_lib_error(MQTT_RPC_CLIENT_PUBLISH_TOPIC_IS_NULL);

	MqttError ret;
	ret = connect();
	if (!ret) {
#ifdef DEBUG
		std::cout << "MqttRpcClient::open error when call connect: " 
				<< ret.getType() << ", " << ret.getCode() << std::endl;
#endif
		return ret;
	}

	ret = subscribe(subscribe_topic_);
	if (!ret) {
#ifdef DEBUG
		std::cout << "MqttRpcClient::open error when call subscribe: " 
				<< ret.getType() << ", " << ret.getCode() << std::endl;
#endif
		return ret;
	}

	return MqttError::no_error();
}

MqttError MqttRpcClient::close()
{
	MqttError ret;
	ret = disconnect();
	if (!ret) {
#ifdef DEBUG
		std::cout << "MqttRpcClient::close error when call disconnect: " 
				<< ret.getType() << ", " << ret.getCode() << std::endl;
#endif
		return ret;
	}

	return MqttError::no_error();
}

MqttError MqttRpcClient::notify(const std::string &method, const void *payload, size_t len)
{
	std::vector<uint8_t> buffer;
	pack_.packNotifyPacket(buffer, method, payload, len);
	auto ret = MqttClientBase::publish(publish_topic_, buffer.data(), buffer.size());
	return ret.first;
}

void MqttRpcClient::set_subscribe_topic(MqttClientSettings &settings, const std::string &topic)
{
	settings.setCustomSetting(RPC_CLIENT_SUBSCRIBE_TOPIC, topic);
}

void MqttRpcClient::set_publish_topic(MqttClientSettings &settings, const std::string &topic)
{
	settings.setCustomSetting(RPC_CLIENT_PUBLISH_TOPIC, topic);
}

const std::string &MqttRpcClient::get_subscribe_topic(const MqttClientSettings &settings)
{
	return settings.getCustomSetting(RPC_CLIENT_SUBSCRIBE_TOPIC);
}

const std::string &MqttRpcClient::get_publish_topic(const MqttClientSettings &settings)
{
	return settings.getCustomSetting(RPC_CLIENT_PUBLISH_TOPIC);
}

class MqttRpcClient::QueryContext {
public:
	QueryContext() {} 

	std::future<MqttError> getFuture()
	{
		return prom_.get_future();
	}

	void setValue(MqttError error)
	{
		prom_.set_value(error);
	}

	void setReplyPacket(std::shared_ptr<std::vector<uint8_t>> reply_packet)
	{
		reply_packet_ = reply_packet;
	}

	std::shared_ptr<std::vector<uint8_t>> getReplyPacket()
	{
		return reply_packet_;
	}

	void setUnpack(std::shared_ptr<MqttRpcUnpack> unpack)
	{
		unpack_ = unpack;
	}

	std::shared_ptr<MqttRpcUnpack> getUnpack()
	{
		return unpack_;
	}

private:
	std::promise<MqttError> prom_;
	std::shared_ptr<std::vector<uint8_t>> reply_packet_;
	std::shared_ptr<MqttRpcUnpack> unpack_;
};

void MqttRpcClient::onMessageArrived(std::shared_ptr<const mqtt::message> msg)
{
	auto task_queue = MqttClientBase::getTaskQueue();
	task_queue->pushTask(&MqttRpcClient::do_onMessageArrived, this, msg);
}

void MqttRpcClient::do_onMessageArrived(std::shared_ptr<const mqtt::message> msg)
{
	// save reply message payload
	const auto &msg_payload_load = msg->get_payload_ref();
	auto msg_payload_load_begin = reinterpret_cast<const uint8_t *>(msg_payload_load.data());
	auto msg_payload_load_end = msg_payload_load_begin + msg_payload_load.size();
	auto reply_packet = std::make_shared<std::vector<uint8_t>>(
			msg_payload_load_begin, msg_payload_load_end); 

	// unpack
	auto unpack = std::make_shared<MqttRpcUnpack>();
	auto ret = unpack->unpack(reply_packet->data(), reply_packet->size());
	if (!ret) {
#ifdef DEBUG
		std::cout << "unpack packet fail!" << std::endl;
#endif
		return;
	}

	// check message type
	if (!unpack->hasMessageType()) {
#ifdef DEBUG
		std::cout << "packet check fail: no message type!" << std::endl;
#endif
		return;
	}

	if (unpack->getMessageType() != MESSAGE_TYPE_REPLY) {
#ifdef DEBUG
		std::cout << "message type error: not reply packet!" << std::endl;
#endif
		return;
	}

	// check message id
	if (!unpack->hasMessageID()) {
#ifdef DEBUG
		std::cout << "packet check fail: no message id!" << std::endl;
#endif
		return;
	}

	auto message_id = unpack->getMessageID();
	auto iter = query_context_map_.find(message_id);
	if (iter == query_context_map_.end()) {	// query is be canceled or invalid message id
#ifdef DEBUG
		std::cout << "not found message id of " << message_id 
			<< " in query_context_map_!" << std::endl;
#endif
		return;	
	}

	// set reply message
	auto query_context = iter->second;
	query_context->setReplyPacket(reply_packet); 
	query_context->setUnpack(unpack);
	query_context->setValue(MqttError::no_error());

	return;
}

class MqttRpcClient::AutoRemoveQueryContext {
public:
	AutoRemoveQueryContext(MqttRpcClient *rpc_client, uint32_t message_id): 
		rpc_client_(rpc_client), message_id_(message_id)
	{}

	~AutoRemoveQueryContext()
	{
#ifdef DEBUG
		std::cout << "remove query context of message id " 
			<< message_id_ << std::endl;
#endif
		rpc_client_->removeQueryContext(message_id_);
	}

private:
	MqttRpcClient *rpc_client_;
	uint32_t message_id_;
};

MqttError MqttRpcClient::query(std::string &answer, const std::string &method, const void *payload, size_t len)
{
	// create packet
	std::vector<uint8_t> buffer;
	auto message_id = pack_.packQueryPacket(buffer, method, payload, len);

	// create query context
	auto query_context = std::make_shared<QueryContext>();
	query_context_map_[message_id] = query_context; 
	AutoRemoveQueryContext auto_remove_query_context(this, message_id);

	// pulish query packet
	auto ret = MqttClientBase::publish(publish_topic_, buffer.data(), buffer.size());
	if (!ret.first) {
#ifdef DEBUG
		std::cout << "MqttRpcClient::query error: fail publish message_id(" 
			<< message_id << "), error("
			<< ret.first.getType() << ", " << ret.first.getCode() 
			<< std::endl;
#endif
		return ret.first;
	}
	MqttClientBase::wait(ret.second);

	// waiting for reply packet
	auto fut = query_context->getFuture();
	fut.get();

	auto unpack = query_context->getUnpack();

	// check and get server return code
	if (!unpack->hasReturnCode()) {
#ifdef DEBUG
		std::cout << "MqttRpcClient::query error: reply header no return code, "
			" which message_id is " << message_id << std::endl;
#endif
		return make_rpc_lib_error(MQTT_RPC_PACKET_REPLY_NO_RETURN_CODE);
	}

	auto server_return_code = unpack->getReturnCode();
	if (server_return_code != 0) {
#ifdef DEBUG
		std::cout << "MqttRpcClient::query error: rpc server return error, "
			" which message_id is " << message_id << std::endl;
#endif
		return make_rpc_server_error(server_return_code);
	}

	// check reply packet payload
	if (!unpack->hasPayload()) {
#ifdef DEBUG
		std::cout << "MqttRpcClient::query error: reply packet no payload, "
			" which message_id is " << message_id << std::endl;
#endif
		return make_rpc_lib_error(MQTT_RPC_PACKET_REPLY_NO_PAYLOAD);
	}

#ifdef DEBUG
	std::cout << "dump reply packet payload: " << std::endl;
	mini_utils::dump(unpack->getPayload(), unpack->getPayloadLength(), nullptr);
#endif

	answer.assign(reinterpret_cast<const char *>(unpack->getPayload()),
				unpack->getPayloadLength());
	return MqttError::no_error();
}

MqttError MqttRpcClient::query(std::string &answer, const std::string &method, const void *payload, size_t len, int time_out_secs)
{
	// todo
	return MqttError::no_error();
}

void MqttRpcClient::removeQueryContext(message_id_type message_id)
{
	auto task_queue = MqttClientBase::getTaskQueue();
	task_queue->pushTask(&MqttRpcClient::do_removeQueryContext, this, message_id);
}

void MqttRpcClient::do_removeQueryContext(message_id_type message_id)
{
	query_context_map_.erase(message_id);
}

}	// namespace mqtt_rpc
