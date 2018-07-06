PROJECT(demo)
cmake_minimum_required(VERSION 3.0)

INCLUDE_DIRECTORIES(.)

LINK_DIRECTORIES(.)

add_definitions("")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -O2 -std=c11")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -O2")

FILE(GLOB src_files ${PROJECT_SOURCE_DIR}/*.cpp)

FOREACH (src_file ${src_files})
    STRING(REGEX MATCH "[^/]+$" src_basename ${src_file})
    STRING(REPLACE ".cpp" "" exe_file ${src_basename})
    ADD_EXECUTABLE(${exe_file} ${src_file})
    TARGET_LINK_LIBRARIES(${exe_file} pthread)
ENDFOREACH()

