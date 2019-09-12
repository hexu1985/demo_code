#include "mqtt/connect_options.h"
#include "MqttClientSettings.hpp"

using std::string;

namespace mqtt_rpc {

void MqttClientSettings::setBrokerAddress(const string &address)
{
	broker_address_ = address;
}

void MqttClientSettings::setClientID(const string &id)
{
	client_id_ = id;
}

void MqttClientSettings::setKeepAliveInterval(int interval_seconds)
{
	keep_alive_interval_ = interval_seconds;
}

void MqttClientSettings::setQos(int qos)
{
	qos_ = qos;
}

void MqttClientSettings::setCleanSession(bool clean_session)
{
	clean_session_flag_ = clean_session;
}

void MqttClientSettings::setConnectTimeout(int timeout_seconds)
{
	connect_timeout_ = timeout_seconds;
}

void MqttClientSettings::setUserName(const string &user_name)
{
	user_name_ = user_name;
}

void MqttClientSettings::setPassword(const string &password)
{
	password_ = password;
}

void MqttClientSettings::setCACertificatePath(const string &path)
{
	ca_certificate_path_ = path;
}

void MqttClientSettings::setReconnectTryMaxTimes(int times)
{
	reconnect_try_max_times_ = times;
}

void MqttClientSettings::setSecondsWaitBeforeReconnect(int seconds)
{
	seconds_wait_before_reconnect_ = seconds;
}

const string &MqttClientSettings::getBrokerAddress() const
{
	return broker_address_;
}

const string &MqttClientSettings::getClientID() const
{
	return client_id_;
}

int MqttClientSettings::getKeepAliveInterval() const
{
	return keep_alive_interval_;
}

int MqttClientSettings::getQos() const
{
	return qos_;
}

bool MqttClientSettings::getCleanSession() const
{
	return clean_session_flag_;
}

int MqttClientSettings::getConnectTimeout() const
{
	return connect_timeout_;
}

const string &MqttClientSettings::getUserName() const
{
	return user_name_;
}

const string &MqttClientSettings::getPassword() const
{
	return password_;
}

const string &MqttClientSettings::getCACertificatePath() const
{
	return ca_certificate_path_;
}

int MqttClientSettings::getReconnectTryMaxTimes() const
{
	return reconnect_try_max_times_;
}

int MqttClientSettings::getSecondsWaitBeforeReconnect() const
{
	return seconds_wait_before_reconnect_;
}

mqtt::connect_options &MqttClientSettings::toConnectOptions(mqtt::connect_options &conn_opts)
{
	if (!user_name_.empty() && !password_.empty()) {
		conn_opts.set_user_name(user_name_);
		conn_opts.set_password(password_);
	}

	conn_opts.set_keep_alive_interval(keep_alive_interval_);
	conn_opts.set_connect_timeout(connect_timeout_);
	conn_opts.set_clean_session(clean_session_flag_);

#ifdef OPENSSL
	if (!ca_certificate_path_.empty()) {
		mqtt::ssl_options ssl_opts;
		ssl_opts.set_trust_store(ca_certificate_path_);
		conn_opts.set_ssl(ssl_opts);
	}
#endif

	return conn_opts;
}

void MqttClientSettings::setCustomSetting(const std::string &key, const std::string &value)
{
	custom_settings_[key] = value;
}

bool MqttClientSettings::hasCustomSetting(const std::string &key) const
{
	return custom_settings_.find(key) != custom_settings_.end();
}

const std::string &MqttClientSettings::getCustomSetting(const std::string &key) const
{
	static const std::string null_str;
	auto it = custom_settings_.find(key);
	if (it == custom_settings_.end())
		return null_str;
	else
		return it->second;
}

}	// namespace mqtt_rpc
