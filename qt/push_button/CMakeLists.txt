cmake_minimum_required(VERSION 3.1.0)

project(push_button VERSION 1.0.0 LANGUAGES CXX)

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

add_executable(push_button_test
  main.cpp
  mywidget.ui
  mywidget.h
  mywidget.cpp
  )

target_link_libraries(push_button_test Qt5::Widgets)
