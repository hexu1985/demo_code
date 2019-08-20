# CMakeLists.txt
#
# CMake file for the Paho C++ sample applications.
#
#*******************************************************************************
# This is part of the Paho MQTT C++ client library.
#
# Copyright (c) 2016
# 
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v1.0
# and Eclipse Distribution License v1.0 which accompany this distribution.
# 
# The Eclipse Public License is available at
#   http://www.eclipse.org/legal/epl-v10.html
# and the Eclipse Distribution License is available at
#   http://www.eclipse.org/org/documents/edl-v10.php.
# 
# Contributors:
#   Guilherme Maciel Ferreira - initial version
#*******************************************************************************/

## Note: on OS X you should install XCode and the associated command-line tools

## --- Library dependencies ---
# commit id 0874b245be971d7d034d23e4cebf0a8d9f688f2e

# Version 2.4 might work, but it won't find static libraries with odd names
cmake_minimum_required(VERSION 2.6)
 
# CMake used to complain without this
#if(COMMAND cmake_policy)
#  cmake_policy(SET CMP0003 NEW)
#endif(COMMAND cmake_policy)
 
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")
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

set(PAHO_CPP_LIB paho-mqttpp3 paho-mqtt3as)

set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

## include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

## SSL binary files
add_executable(ssl_publish ssl_publish.cpp)
add_executable(ssl_subscribe ssl_subscribe.cpp)

## link SSL binaries
target_link_libraries(ssl_publish ${PAHO_CPP_LIB})
target_link_libraries(ssl_subscribe ${PAHO_CPP_LIB})

set(INSTALL_TARGETS
	${INSTALL_TARGETS}
	ssl_publish
	ssl_subscribe)

add_definitions(-DOPENSSL)

## install binaries
install(TARGETS ${INSTALL_TARGETS} EXPORT PahoMqttCppSamples
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
)

