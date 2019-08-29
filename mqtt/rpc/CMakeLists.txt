CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
 
project(MQTT_RPC_CLIENT)

# CMake used to complain without this
#if(COMMAND cmake_policy)
#  cmake_policy(SET CMP0003 NEW)
#endif(COMMAND cmake_policy)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -DDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
	set(LIBS_SYSTEM ws2_32)
elseif(UNIX)
	set(LIBS_SYSTEM c stdc++)
endif()

# set MQTT_INCLUDE_DIRS
set(MQTT_INCLUDE_DIRS
	/usr/local/include
	/home/hexu/git/paho.mqtt.cpp/src
	)

set(PAHO_CPP_LIB paho-mqttpp3 paho-mqtt3as)

include_directories(${MQTT_INCLUDE_DIRS})
add_subdirectory(src)
add_subdirectory(samples)
