cmake_minimum_required(VERSION 3.1.0)

project(qtimer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#qt5_add_resources(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/fileviewer.qrc)

add_executable(qtimer_test
  main.cpp
  mytimer.cpp
  mytimer.h
  TaskQueue.hpp
  WorkerThread.cpp
  WorkerThread.hpp
  #  ${RESOURCES}
  )

target_link_libraries(qtimer_test Qt5::Widgets pthread)
