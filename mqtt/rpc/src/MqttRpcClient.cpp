#include "MqttRpcClient.hpp"
#include "MqttRpcErrorEnum.hpp"

#ifdef DEBUG
#include <iostream>
#endif

namespace mqtt_rpc {

namespace {

const static std::string RPC_CLIENT_SUBSCRIBE_TOPIC = "MqttRpcClient.subscribe_topic";

const static std::string RPC_CLIENT_PUBLISH_TOPIC = "MqttRpcClient.publish_topic";

}	// namespace

MqttRpcClient::MqttRpcClient(const MqttClientSettings &settings): MqttClientBase(settings)
{
	subscribe_topic_ = get_subscribe_topic(settings);
	publish_topic_ = get_publish_topic(settings);
	last_message_id_ = 0;
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

}	// namespace mqtt_rpc
