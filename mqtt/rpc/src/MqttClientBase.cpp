#include <cassert>
#include "mqtt/async_client.h"
#include "MqttClientBase.hpp"
#include "MqttRpcErrorEnum.hpp"

#ifdef DEBUG
#include <iostream>
#include "dump_functions.hpp"
#endif

using mini_utils::TaskQueue;

namespace mqtt_rpc {

class MqttClientBase::Callback: public virtual mqtt::callback,
				public virtual mqtt::iaction_listener {
public:
	Callback(MqttClientBase &client): client_(client) {}

private:
	// Re-connection failure
	void on_failure(const mqtt::token& tok) override 
	{
		// todo:
	}

	// (Re)connection success
	// Either this or connected() can be used for callbacks.
	void on_success(const mqtt::token& tok) override 
	{
		// todo:
	}

	// (Re)connection success
	void connected(const std::string& cause) override 
	{
		// todo:
	}

	// Callback for when the connection is lost.
	// This will initiate the attempt to manually reconnect.
	void connection_lost(const std::string &cause) override 
	{
#ifdef DEBUG
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;
#endif
		client_.onConnectionLost();
	}

	// Callback for when a message arrives.
	void message_arrived(mqtt::const_message_ptr msg) override 
	{
#ifdef DEBUG
		std::cout << "Message arrived" << std::endl;
		std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
		std::cout << "\tpayload: " << std::endl;
		auto payload = msg->to_string();
		mini_utils::dump((const uint8_t *) payload.data(), payload.size(), nullptr);
#endif
		client_.onMessageArrived(msg);
	}

	void delivery_complete(mqtt::delivery_token_ptr token) override 
	{
#ifdef DEBUG
		std::cout << "\tDelivery complete for token: "
			<< (token ? token->get_message_id() : -1) << std::endl;
#endif
		client_.onDeliveryComplete(token);
	}	

private:
	MqttClientBase &client_;
};

class MqttClientBase::ConnectListener: public mqtt::iaction_listener {
public:
	ConnectListener(MqttClientBase &client, std::shared_ptr<TaskQueue> &task_queue,
		std::promise<MqttError> &prom): 
		client_(client), task_queue_(task_queue), prom_(prom) 
	{}

	std::promise<MqttError> &getPromise()
	{
		return prom_;
	}

private:
	void on_failure(const mqtt::token& tok) override 
	{
#ifdef	DEBUG
		std::cout << "\t ConnectListener failure for token: "
			<< tok.get_message_id() << std::endl;
#endif
		task_queue_->pushTask(&MqttClientBase::do_connect_complete, &client_, 
				std::ref(prom_), make_paho_lib_error(tok.get_reason_code()));
	}

	void on_success(const mqtt::token& tok) override 
	{
#ifdef	DEBUG
		std::cout << "\t ConnectListener success for token: "
			<< tok.get_message_id() << std::endl;
#endif
		task_queue_->pushTask(&MqttClientBase::do_connect_complete, &client_, 
				std::ref(prom_), MqttError::no_error());
	}

private:
	MqttClientBase &client_;
	std::shared_ptr<TaskQueue> &task_queue_;
	std::promise<MqttError> &prom_;
};

class MqttClientBase::SubscribeListener: public mqtt::iaction_listener {
public:
	SubscribeListener(const std::string &topic, int qos,
		std::promise<MqttError> &prom): topic_(topic), qos_(qos), prom_(prom) 
	{}

	const std::string &getTopic() const
	{
		return topic_;
	}

	int getQos() const
	{
		return qos_;
	}

	std::promise<MqttError> &getPromise()
	{
		return prom_;
	}

private:
	void on_failure(const mqtt::token& tok) override 
	{
#ifdef	DEBUG
		std::cout << "\t SubscribeListener failure for token: "
			<< tok.get_message_id() << std::endl;
#endif
		prom_.set_value(make_paho_lib_error(tok.get_reason_code()));
	}

	void on_success(const mqtt::token& tok) override 
	{
#ifdef	DEBUG
		std::cout << "\t SubscribeListener success for token: "
			<< tok.get_message_id() << std::endl;
#endif
		prom_.set_value(MqttError::no_error());
	}

private:
	const std::string &topic_;
	int qos_;
	std::promise<MqttError> &prom_;
};

MqttClientBase::MqttClientBase(const MqttClientSettings &settings):
	client_settings_(settings), worker_thread_(settings.getClientID()),
	client_handle_(std::make_shared<mqtt::async_client>(settings.getBrokerAddress(), settings.getClientID())),
	callback_(new MqttClientBase::Callback(*this)),
	connect_options_(std::make_shared<mqtt::connect_options>())
{
	worker_thread_.start();
	client_handle_->set_callback(*callback_);
	client_settings_.toConnectOptions(*connect_options_);
}

MqttClientBase::~MqttClientBase()
{
	disconnect();
	worker_thread_.stop();
}

MqttError MqttClientBase::connect()
{
	std::promise<MqttError> prom;
	std::future<MqttError> fut = prom.get_future();
	auto task_queue = getTaskQueue();
	ConnectListener cb(*this, task_queue, prom);
	task_queue->pushTask(&MqttClientBase::do_connect, this, std::ref(cb));
	MqttError ret = fut.get();
	return ret;
}

MqttError MqttClientBase::disconnect()
{
	std::promise<MqttError> prom;
	std::future<MqttError> fut = prom.get_future();
	auto task_queue = getTaskQueue();
	task_queue->pushTask(&MqttClientBase::do_disconnect, this, std::ref(prom));
	MqttError ret = fut.get();
	return ret;
}

MqttError MqttClientBase::subscribe(const std::string &topic)
{
	std::promise<MqttError> prom;
	std::future<MqttError> fut = prom.get_future();
	auto task_queue = getTaskQueue();
	SubscribeListener cb(topic, client_settings_.getQos(), prom);
	task_queue->pushTask(&MqttClientBase::do_subscribe, this, std::ref(cb));
	MqttError ret = fut.get();
	return ret;
}

MqttClientBase::PubRetType MqttClientBase::publish(const std::string &topic, 
		const void *payload, size_t len)
{
	return publish(topic, payload, len, nullptr);
}

MqttClientBase::PubRetType MqttClientBase::publish(const std::string &topic, 
		const void *payload, size_t len, 
		std::shared_ptr<mqtt::iaction_listener> cb)
{
	std::promise<PubRetType> prom;
	std::future<PubRetType> fut = prom.get_future();
	auto task_queue = getTaskQueue();
	mqtt::message_ptr pubmsg = mqtt::make_message(topic, payload, len, getQos(), false);
	task_queue->pushTask(&MqttClientBase::do_publish, this, std::ref(prom), pubmsg, cb);
	PubRetType ret = fut.get();
	return ret;
}

void MqttClientBase::wait(std::shared_ptr<mqtt::delivery_token> token)
{
	return token->wait();
}

bool wait(std::shared_ptr<mqtt::delivery_token> token, int nsecs)
{
	long timeout = (long) nsecs * 1000L;
	return token->wait_for(timeout);
}

void MqttClientBase::onConnectionLost()
{
	auto task_queue = getTaskQueue();
	task_queue->pushTask(&MqttClientBase::do_setStatus, this, MqttClientStatus::disconnected);
}

void MqttClientBase::onMessageArrived(std::shared_ptr<const mqtt::message> msg)
{
}

std::shared_ptr<mqtt::delivery_token> MqttClientBase::publishMessage(
		std::shared_ptr<const mqtt::message> msg,
		std::shared_ptr<mqtt::iaction_listener> cb)
{
	return client_handle_->publish(msg);
}

void MqttClientBase::onDeliveryComplete(std::shared_ptr<mqtt::delivery_token> token)
{
}

void MqttClientBase::do_connect(ConnectListener &cb)
{
	if (client_status_ != MqttClientStatus::disconnected) {
		cb.getPromise().set_value(make_client_status_error(client_status_));
		return;
	}
	client_status_ = MqttClientStatus::connecting;
	client_handle_->connect(*connect_options_, nullptr, cb);
}

void MqttClientBase::do_connect_complete(std::promise<MqttError> &prom, MqttError error)
{
	if (error.isNoError()) {
		client_status_ = MqttClientStatus::connected;
	} else {
		client_status_ = MqttClientStatus::disconnected;
	}
	prom.set_value(error);
}

void MqttClientBase::do_disconnect(std::promise<MqttError> &prom)
{
	if (client_status_ != MqttClientStatus::connected) {
		prom.set_value(make_client_status_error(client_status_));
		return;
	}

	try {
		client_handle_->disconnect()->wait();
		client_status_ = MqttClientStatus::disconnected;
		prom.set_value(MqttError::no_error());
	} catch (const mqtt::exception& e) {
#ifdef DEBUG
		std::cout << "MqttClientBase::do_disconnect error: "
				<< e.what() << std::endl;
#endif
		prom.set_value(make_paho_lib_error(e.get_reason_code()));
	}
}

void MqttClientBase::do_subscribe(SubscribeListener &cb)
{
	if (client_status_ != MqttClientStatus::connected) {
		cb.getPromise().set_value(make_client_status_error(client_status_));
		return;
	}
	client_handle_->subscribe(cb.getTopic(), cb.getQos(), nullptr, cb);
}

void MqttClientBase::do_publish(std::promise<PubRetType> &prom, 
		std::shared_ptr<const mqtt::message> msg,
		std::shared_ptr<mqtt::iaction_listener> cb)
{
	PubRetType ret;
	if (client_status_ != MqttClientStatus::connected) {	// check status
		ret.first = make_client_status_error(client_status_);
		prom.set_value(ret);
		return;
	}

	try {	// call mqtt lib to publish message
		ret.second = publishMessage(msg, cb);
		ret.first = MqttError::no_error();
	} catch (const mqtt::exception& e) {
#ifdef DEBUG
		std::cout << "MqttClientBase::do_publish error: "
				<< e.what() << std::endl;
#endif
		ret.first = make_paho_lib_error(e.get_reason_code());
	}
	prom.set_value(ret);
}

void MqttClientBase::do_setStatus(MqttClientStatus status)
{
	client_status_ = status;
}

std::shared_ptr<TaskQueue> MqttClientBase::getTaskQueue()
{
	return worker_thread_.getTaskQueue();
}

int MqttClientBase::getQos() const
{
	return client_settings_.getQos();
}

const std::string &MqttClientBase::get_topic(std::shared_ptr<const mqtt::message> msg)
{
	return msg->get_topic();
}

std::string MqttClientBase::get_payload(std::shared_ptr<const mqtt::message> msg)
{
	return msg->to_string();
}

MqttError make_client_status_error(const MqttClientStatus &status)
{
	MqttError error;
	switch (status) {
	case MqttClientStatus::disconnected:
		error = make_rpc_lib_error(MQTT_CLIENT_STATUS_IS_DISCONNECTED);
		break;
	case MqttClientStatus::connected:
		error = make_rpc_lib_error(MQTT_CLIENT_STATUS_IS_CONNECTED);
		break;
	case MqttClientStatus::connecting:
		error = make_rpc_lib_error(MQTT_CLIENT_STATUS_IS_CONNECTING);
		break;
	default:
		assert("logical error" && false);
	}
	return error;
}

}	// namespace mqtt_rpc
