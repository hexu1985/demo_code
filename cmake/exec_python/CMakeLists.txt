cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(HELLO)

find_package(PythonInterp REQUIRED)
execute_process(
    COMMAND
    ${PYTHON_EXECUTABLE} "process_json.py"
    RESULT_VARIABLE _status
    OUTPUT_VARIABLE _output
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

message(STATUS "RESULT_VARIABLE is: ${_status}")
message(STATUS "OUTPUT_VARIABLE is: ${_hello_world}")

if (${_status} EQUAL "0")
    message(STATUS "process_json.py success")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test.cmake)
    message("item_list: ${item_list}")
endif()

set(EXE_NAME hello.exe)
set(SRC_LIST main.c)
add_executable(${EXE_NAME} ${SRC_LIST})
