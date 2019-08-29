#ifndef MQTT_RPC_MQTT_CLIENT_SETTINGS_INC
#define MQTT_RPC_MQTT_CLIENT_SETTINGS_INC

#include <string>
#include <unordered_map>

namespace mqtt {
class connect_options;	// forward declare
}	// namespace mqtt

namespace mqtt_rpc {

/**
 * @brief mqtt client settings
 */
class MqttClientSettings {
public:
	enum {
		DEFAULT_KEEP_ALIVE_INTERVAL = 30,	// 30 second
		DEFAULT_QOS = 1,
		DEFAULT_CONNECT_TIMEOUT = 30,
	};

private:
	std::string broker_address_;		// broker's host/ip address
	std::string client_id_;				// mqtt client id
	int			keep_alive_interval_ = DEFAULT_KEEP_ALIVE_INTERVAL;	// mqtt client keep alive interval with broker by seconds 
	int			qos_ = DEFAULT_QOS;				// mqtt message Qos
	bool		clean_session_flag_ = true;
	int			connect_timeout_ = DEFAULT_CONNECT_TIMEOUT;	// mqtt client connect timeout by seconds
	std::string user_name_;				// mqtt client user name 
	std::string password_;				// mqtt client password
	std::string ca_certificate_path_;	// the ca certificate file to prove broker

	typedef std::unordered_map<std::string, std::string> CustomSettings;
	CustomSettings custom_settings_;

public:
	/**
	 * @brief construct a MqttClientSettings with default parameter values
	 */
	MqttClientSettings() = default;

	MqttClientSettings(const MqttClientSettings &) = default;

	MqttClientSettings &operator =(const MqttClientSettings &) = default;

	// set settings parameter values
	void setBrokerAddress(const std::string &address);
	void setClientID(const std::string &id);
	void setKeepAliveInterval(int interval_seconds);
	void setQos(int qos);
	void setCleanSession(bool clean_session);
	void setConnectTimeout(int timeout_seconds);
	void setUserName(const std::string &user_name);
	void setPassword(const std::string &password);
	void setCACertificatePath(const std::string &path);

	// get settings parameter values
	const std::string &getBrokerAddress() const;
	const std::string &getClientID() const;
	int getKeepAliveInterval() const;
	int getQos() const;
	bool getCleanSession() const;
	int getConnectTimeout() const;
	const std::string &getUserName() const;
	const std::string &getPassword() const;
	const std::string &getCACertificatePath() const;

	// convert functions
	mqtt::connect_options &toConnectOptions(mqtt::connect_options &conn_opts);

	// for custom settings
	void setCustomSetting(const std::string &key, const std::string &value);
	bool hasCustomSetting(const std::string &key) const;
	const std::string &getCustomSetting(const std::string &key) const;
};

} // namespace mqtt_rpc

#endif
