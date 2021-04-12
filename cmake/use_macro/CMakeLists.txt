project(HELLO)

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

if (DEFINED ENV{TEST_VALUE})
    message(STATUS "env TEST is $ENV{TEST_VALUE}")
    set(VALUE "$ENV{TEST_VALUE}")
else()
    message(WARNING "not defined TEST_VALUE env")
    set(VALUE "default")
endif()

add_definitions("-DVALUE=\"${VALUE}\"")
add_executable(main main.cpp)
