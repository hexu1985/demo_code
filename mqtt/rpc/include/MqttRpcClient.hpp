#ifndef MQTT_RPC_MQTT_RPC_CLIENT_INC
#define MQTT_RPC_MQTT_RPC_CLIENT_INC

#include <string>
#include "MqttClientBase.hpp"
#include "MqttRpcClientPack.hpp"

// forward declare
namespace mqtt {
class delivery_token;
}	// namespace mqtt

namespace mqtt_rpc {

class MqttRpcClient: protected MqttClientBase {
public:
	MqttRpcClient(const MqttClientSettings &settings);
	~MqttRpcClient() override;

	MqttError open();
	MqttError close();

	MqttError query(std::string &answer, const std::string &method, const void *payload, size_t len);
	MqttError query(std::string &answer, const std::string &method, const void *payload, size_t len, size_t time_out_secs);
	MqttError notify(const std::string &method, const void *payload, size_t len);

	static void set_subscribe_topic(MqttClientSettings &settings, const std::string &topic);
	static void set_publish_topic(MqttClientSettings &settings, const std::string &topic);

	static const std::string &get_subscribe_topic(const MqttClientSettings &settings);
	static const std::string &get_publish_topic(const MqttClientSettings &settings);

	class AutoRemoveQueryContext;
	friend class AutoRemoveQueryContext; 
	class QueryContext;
	typedef uint32_t message_id_type;

private:
	void removeQueryContext(message_id_type message_id);
	void onMessageArrived(std::shared_ptr<const mqtt::message> msg) override;
	void do_removeQueryContext(message_id_type message_id);
	void do_onMessageArrived(std::shared_ptr<const mqtt::message> msg);
	void do_query(std::shared_ptr<QueryContext> query_context);

private:
	std::string subscribe_topic_;
	std::string publish_topic_;
	MqttRpcClientPack pack_;
	std::unordered_map<message_id_type, std::shared_ptr<QueryContext>> query_context_map_;
};

}	// namespace mqtt_rpc

#endif
