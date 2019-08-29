## include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(MQTT_RPC_LIB ${PROJECT_BINARY_DIR}/src/libmqtt_rpc.so)

## binary files
add_executable(sample_mqtt_client_pub sample_mqtt_client_pub.cpp)
add_executable(sample_mqtt_client_sub sample_mqtt_client_sub.cpp)
add_executable(sample_mqtt_protocol sample_mqtt_protocol.cpp)

## link binaries
target_link_libraries(sample_mqtt_client_pub ${MQTT_RPC_LIB} ${PAHO_CPP_LIB})
target_link_libraries(sample_mqtt_client_sub ${MQTT_RPC_LIB} ${PAHO_CPP_LIB})

if(PAHO_WITH_SSL)
    ## link SSL binaries
	#    target_link_libraries(sample_mqtt_client_pub ${PAHO_CPP_LIB})

    add_definitions(-DOPENSSL)
endif()

