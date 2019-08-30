#ifndef MQTT_RPC_MQTT_CLIENT_BASE_INC
#define MQTT_RPC_MQTT_CLIENT_BASE_INC

#include <memory>
#include <string>
#include <future>
#include <chrono>
#include "WorkerThread.hpp" 
#include "MqttError.hpp"
#include "MqttClientSettings.hpp"

// forward declare
namespace mqtt {
class async_client;
class connect_options;
class message;
class delivery_token;
class iaction_listener;
}	// namespace mqtt

namespace mqtt_rpc {

enum class MqttClientStatus {
	disconnected = 0,
	connected = 1,
	connecting = 2,
};

MqttError make_client_status_error(const MqttClientStatus &status);

class MqttClientBase {
public:
	MqttClientBase(const MqttClientSettings &settings);
	virtual ~MqttClientBase();

	MqttError connect();
	MqttError disconnect();

	MqttError subscribe(const std::string &topic);

	typedef std::pair<MqttError, std::shared_ptr<mqtt::delivery_token>> PubRetType;
	PubRetType publish(const std::string &topic, const void *payload, size_t len);
	PubRetType publish(const std::string &topic, const void *payload, size_t len, std::shared_ptr<mqtt::iaction_listener> cb);
	void wait(std::shared_ptr<mqtt::delivery_token> token);
	bool wait(std::shared_ptr<mqtt::delivery_token> token, int nsecs);

	MqttClientStatus getStatus();

	// this function will run on worker thread
	void onConnectFailure();
	void onConnectSuccess();

protected:
	class ConnectListener;
	class SubscribeListener;
	class PublishListener;

	void onConnectionLost();
	virtual void onMessageArrived(std::shared_ptr<const mqtt::message> msg);
	virtual std::shared_ptr<mqtt::delivery_token> publishMessage(
			std::shared_ptr<const mqtt::message> msg, 
			std::shared_ptr<mqtt::iaction_listener> cb);
	virtual void onDeliveryComplete(std::shared_ptr<mqtt::delivery_token> token);

	// do_ functions will run on worker thread
	void do_connect(ConnectListener &cb);
	void do_connect_complete(std::promise<MqttError> &prom, MqttError error);
	void do_disconnect(std::promise<MqttError> &prom);
	void do_subscribe(SubscribeListener &cb);
	void do_publish(std::promise<PubRetType> &prom, 
			std::shared_ptr<const mqtt::message> msg,
			std::shared_ptr<mqtt::iaction_listener> cb
			);
	void do_setStatus(MqttClientStatus status);
	void do_getStatus();
	void do_reconnect();

	std::shared_ptr<mini_utils::TaskQueue> getTaskQueue();
	int getQos() const;

	static const std::string &get_topic(std::shared_ptr<const mqtt::message> msg);
	static std::string get_payload(std::shared_ptr<const mqtt::message> msg);

private:
	MqttClientBase(const MqttClientBase &) = delete;
	MqttClientBase &operator =(const MqttClientBase &) = delete;

	static std::shared_ptr<mqtt::async_client> create_async_client(
			const MqttClientSettings &settings);

private:
	class Callback;

	MqttClientStatus client_status_ = MqttClientStatus::disconnected;
	MqttClientSettings client_settings_;
	mini_utils::WorkerThread worker_thread_;
	std::shared_ptr<mqtt::async_client> client_handle_;
	std::shared_ptr<Callback> callback_;
	std::shared_ptr<mqtt::connect_options> connect_options_;
};

}	// namespace mqtt_rpc

#endif
