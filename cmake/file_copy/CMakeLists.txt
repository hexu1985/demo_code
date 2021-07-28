cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(HELLO)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output/bin)
file(COPY ${CMAKE_SOURCE_DIR}/script/linux/ DESTINATION ${EXECUTABLE_OUTPUT_PATH}/script)

set(EXE_NAME hello.exe)
set(SRC_LIST main.c)
add_executable(${EXE_NAME} ${SRC_LIST})
