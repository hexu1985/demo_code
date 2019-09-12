CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
 
project(mqtt_rpc_client)

# CMake used to complain without this
#if(COMMAND cmake_policy)
#  cmake_policy(SET CMP0003 NEW)
#endif(COMMAND cmake_policy)

#SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -DDEBUG")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
	set(LIBS_SYSTEM ws2_32)
	set(PAHO_CPP_LIB paho-mqttpp3-static) 
else()
	set(LIBS_SYSTEM c stdc++ pthread)
	set(PAHO_CPP_LIB paho-mqttpp3) 
endif()

# set MQTT_INCLUDE_DIRS
set(MQTT_INCLUDE_DIRS
	${PAHO_C_ROOT_DIR}/include
	${PAHO_CPP_ROOT_DIR}/include
	)
include_directories(${MQTT_INCLUDE_DIRS})

set(MQTT_LINK_DIRS
	${PAHO_C_ROOT_DIR}/lib
	${PAHO_CPP_ROOT_DIR}/lib
	)
link_directories(${MQTT_LINK_DIRS})

IF (PAHO_WITH_SSL)
    add_definitions(-DOPENSSL)
	FIND_LIBRARY(OPENSSL_LIB NAMES ssl libssl ssleay32
		HINTS ${OPENSSL_SEARCH_LIB_PATH})
	FIND_LIBRARY(OPENSSLCRYPTO_LIB NAMES crypto libcrypto libeay32
		HINTS ${OPENSSL_SEARCH_LIB_PATH})
	MESSAGE(STATUS "OpenSSL library found at ${OPENSSL_LIB}")
	MESSAGE(STATUS "OpenSSL Crypto library found at ${OPENSSLCRYPTO_LIB}")
	set(PAHO_CPP_LIB ${PAHO_CPP_LIB} paho-mqtt3as ${OPENSSL_LIB} ${OPENSSLCRYPTO_LIB})
ELSE()
	set(PAHO_CPP_LIB ${PAHO_CPP_LIB} paho-mqtt3a)
ENDIF()

add_subdirectory(src)
add_subdirectory(samples)
