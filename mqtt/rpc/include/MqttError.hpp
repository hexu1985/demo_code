#ifndef MQTT_RPC_MQTT_ERROR_INC
#define MQTT_RPC_MQTT_ERROR_INC

namespace mqtt_rpc {

class MqttError {
public:
	enum error_type {
		NO_ERROR = 0,
		PAHO_LIB = 1,
		RPC_LIB = 2,
		RPC_SERVER = 3,
	};

	MqttError() = default;
	MqttError(const MqttError &) = default;
	MqttError &operator =(const MqttError &) = default;

	MqttError(int type, int code): type_(type), code_(code)
	{
	}

	int getType() const
	{
		return type_;
	}

	int getCode() const
	{
		return code_;
	}

	static MqttError no_error()
	{
		return MqttError(NO_ERROR, 0); 
	}

	bool isNoError() const 
	{
		return type_ == NO_ERROR;
	}

	explicit operator bool() const
	{
		return isNoError();
	}

private:
	int type_ = NO_ERROR;
	int code_ = 0;
};

inline 
MqttError make_paho_lib_error(int code)
{
	return MqttError(MqttError::PAHO_LIB, code); 
}

inline
MqttError make_rpc_lib_error(int code)
{
	return MqttError(MqttError::RPC_LIB, code); 
}

inline
MqttError make_rpc_server_error(int code)
{
	return MqttError(MqttError::RPC_SERVER, code); 
}

}	// namespace mqtt_rpc

#endif
