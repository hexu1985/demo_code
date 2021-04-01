cmake_minimum_required(VERSION 2.8)

project(use_libray)

add_subdirectory(my_library)
include_directories(my_library)
#link_directories(/root/my_library/cmake)

aux_source_directory(. DIR_SRCS)

add_executable(use_library ${DIR_SRCS})
target_link_libraries(use_library  my_library)
