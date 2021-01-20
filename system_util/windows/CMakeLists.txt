cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(examples)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /utf-8 /MT")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /utf-8 /MT")
endif()

FILE(GLOB src_files ${PROJECT_SOURCE_DIR}/*.cpp)

FOREACH (src_file ${src_files})
    GET_FILENAME_COMPONENT(exe_file ${src_file} NAME_WE)
    ADD_EXECUTABLE(${exe_file} ${src_file})
ENDFOREACH()
