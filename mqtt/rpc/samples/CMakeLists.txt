## include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(MQTT_RPC_LIB ${PROJECT_BINARY_DIR}/src/libmqtt_rpc.so)

## binary files
add_executable(sample_mqtt_client_pub sample_mqtt_client_pub.cpp)
add_executable(sample_mqtt_client_sub sample_mqtt_client_sub.cpp)
add_executable(sample_mqtt_rpc_header sample_mqtt_rpc_header.cpp)
add_executable(sample_mqtt_rpc_client_pack sample_mqtt_rpc_client_pack.cpp)
add_executable(sample_mqtt_rpc_client_notify sample_mqtt_rpc_client_notify.cpp)
add_executable(sample_mqtt_rpc_server_notify_stub sample_mqtt_rpc_server_notify_stub.cpp)
add_executable(sample_mqtt_rpc_client_query sample_mqtt_rpc_client_query.cpp)
add_executable(sample_mqtt_rpc_server_query_stub sample_mqtt_rpc_server_query_stub.cpp)

## link binaries
target_link_libraries(sample_mqtt_client_pub ${MQTT_RPC_LIB} ${PAHO_CPP_LIB})
target_link_libraries(sample_mqtt_client_sub ${MQTT_RPC_LIB} ${PAHO_CPP_LIB})
target_link_libraries(sample_mqtt_rpc_client_notify ${MQTT_RPC_LIB} ${PAHO_CPP_LIB})
target_link_libraries(sample_mqtt_rpc_server_notify_stub ${MQTT_RPC_LIB} ${PAHO_CPP_LIB})
target_link_libraries(sample_mqtt_rpc_client_query ${MQTT_RPC_LIB} ${PAHO_CPP_LIB})
target_link_libraries(sample_mqtt_rpc_server_query_stub ${MQTT_RPC_LIB} ${PAHO_CPP_LIB} pthread)

if(PAHO_WITH_SSL)
    ## link SSL binaries
	#    target_link_libraries(sample_mqtt_client_pub ${PAHO_CPP_LIB})

    add_definitions(-DOPENSSL)
endif()

