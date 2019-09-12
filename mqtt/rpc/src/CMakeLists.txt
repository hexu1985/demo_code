set(MQTT_RPC_SRC_LIST 
	MqttClientSettings.cpp
	WorkerThread.cpp
	MqttClientBase.cpp
	MqttRpcClient.cpp
	)

set(MQTT_RPC_HEADER_LIST
	${PROJECT_SOURCE_DIR}/include/MqttClientSettings.hpp
    ${PROJECT_SOURCE_DIR}/include/dump_functions.hpp
    ${PROJECT_SOURCE_DIR}/include/MqttClientBase.hpp
    ${PROJECT_SOURCE_DIR}/include/MqttClientSettings.hpp
    ${PROJECT_SOURCE_DIR}/include/MqttError.hpp
    ${PROJECT_SOURCE_DIR}/include/MqttRpcClient.hpp
    ${PROJECT_SOURCE_DIR}/include/MqttRpcClientPack.hpp
    ${PROJECT_SOURCE_DIR}/include/MqttRpcErrorEnum.hpp
    ${PROJECT_SOURCE_DIR}/include/MqttRpcHeader.hpp
    ${PROJECT_SOURCE_DIR}/include/MqttRpcUnpack.hpp
    ${PROJECT_SOURCE_DIR}/include/RandomNumber.hpp
    ${PROJECT_SOURCE_DIR}/include/TaskQueue.hpp
    ${PROJECT_SOURCE_DIR}/include/Timer.hpp
    ${PROJECT_SOURCE_DIR}/include/WorkerThread.hpp
	)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(mqtt_rpc_client STATIC ${MQTT_RPC_SRC_LIST})
set_target_properties(mqtt_rpc_client PROPERTIES VERSION 1.0 SOVERSION 1)

install(TARGETS mqtt_rpc_client 
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
install(FILES ${MQTT_RPC_HEADER_LIST} DESTINATION include)
