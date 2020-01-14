cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(examples)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package (glog REQUIRED)

aux_source_directory(. src_files)

foreach (src_file ${src_files})
    string(REGEX MATCH "[^/]+$" src_basename ${src_file})
    string(REPLACE ".cpp" "" exe_file ${src_basename})
    add_executable(${exe_file} ${src_file})
    target_link_libraries(${exe_file} glog::glog)
endforeach()
