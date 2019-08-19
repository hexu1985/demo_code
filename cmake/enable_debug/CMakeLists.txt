# Version 2.4 might work, but it won't find static libraries with odd names
cmake_minimum_required(VERSION 2.6)
 
# CMake used to complain without this
#if(COMMAND cmake_policy)
#  cmake_policy(SET CMP0003 NEW)
#endif(COMMAND cmake_policy)
 
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

project (Tutorial)
add_executable(Tutorial tutorial.cxx)
