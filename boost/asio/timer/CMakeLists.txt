project(demo)
cmake_minimum_required(VERSION 3.0)

include_directories(.)

link_directories(.)

add_definitions("")

if(WIN32)
    set(DEP_LIBS boost_thread-mt boost_system-mt pthread wsock32 ws2_32)
else(WIN32)
    set(DEP_LIBS boost_thread boost_system pthread)
endif(WIN32)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -O2 -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -O2")

file(GLOB src_files ${PROJECT_SOURCE_DIR}/*.cpp)

foreach (src_file ${src_files})
    string(REGEX MATCH "[^/]+$" src_basename ${src_file})
    string(REPLACE ".cpp" "" exe_file ${src_basename})
    add_executable(${exe_file} ${src_file})
    target_link_libraries(${exe_file} ${DEP_LIBS})
endforeach()

