#ifndef MQTT_RPC_MQTT_RPC_CLIENT_INC
#define MQTT_RPC_MQTT_RPC_CLIENT_INC

#include <atomic>
#include <string>
#include "MqttClientBase.hpp"

namespace mqtt_rpc {

class MqttRpcClient: protected MqttClientBase {
public:
	MqttRpcClient(const MqttClientSettings &settings);
	~MqttRpcClient() override;

	MqttError open();
	MqttError close();

	MqttError query(std::string &answer, const std::string &method, const void *payload, size_t len);
	MqttError query(std::string &answer, const std::string &method, const void *payload, size_t len, int time_out_secs);
	MqttError notify(const std::string &method, const void *payload, size_t len);

	static void set_subscribe_topic(MqttClientSettings &settings, const std::string &topic);
	static void set_publish_topic(MqttClientSettings &settings, const std::string &topic);

	static const std::string &get_subscribe_topic(const MqttClientSettings &settings);
	static const std::string &get_publish_topic(const MqttClientSettings &settings);

private:
	std::atomic<uint32_t> last_message_id_;
	std::string subscribe_topic_;
	std::string publish_topic_;
};

}	// namespace mqtt_rpc

#endif
