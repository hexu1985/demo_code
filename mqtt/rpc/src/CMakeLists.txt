set(MQTT_RPC_SRC_LIST 
	MqttClientSettings.cpp
	WorkerThread.cpp
	MqttClientBase.cpp
	MqttRpcClient.cpp
	)

set(MQTT_RPC_HEADER_LIST
	${PROJECT_SOURCE_DIR}/include/MqttClientSettings.hpp
	)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(mqtt_rpc SHARED ${MQTT_RPC_SRC_LIST})
set_target_properties(mqtt_rpc PROPERTIES VERSION 1.0 SOVERSION 1)

add_library(mqtt_rpc_static STATIC ${MQTT_RPC_SRC_LIST})
set_target_properties(mqtt_rpc_static PROPERTIES OUTPUT_NAME "mqtt_rpc")

get_target_property(OUTPUT_VALUE mqtt_rpc_static OUTPUT_NAME)
message(STATUS "This is the mqtt_rpc_static OUTPUT_NAME: " ${OUTPUT_VALUE})

install(TARGETS mqtt_rpc mqtt_rpc_static
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
install(FILES MQTT_RPC_HEADER_LIST DESTINATION include)
