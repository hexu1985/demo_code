cmake_minimum_required(VERSION 2.8)

project(my_library)

#include_directories(/root/use_library/)

aux_source_directory(. DIR_SRCS)

add_library(my_library SHARED ${DIR_SRCS})
