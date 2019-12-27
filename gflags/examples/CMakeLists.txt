cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
PROJECT(examples)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${gflags_INCLUDE_DIRS})

link_directories(${gflags_LIB_DIRS})

file(GLOB src_files ${PROJECT_SOURCE_DIR}/*.cpp)

foreach (src_file ${src_files})
    string(REGEX MATCH "[^/]+$" src_basename ${src_file})
    string(REPLACE ".cpp" "" exe_file ${src_basename})
    add_executable(${exe_file} ${src_file})
    target_link_libraries(${exe_file} gflags pthread)
endforeach()

