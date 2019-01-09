
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)

if (TARGET_OS)
    message(STATUS "var TARGET_OS is ${TARGET_OS}")
else()
    message(WARNING "not defined TARGET_OS var")
endif()

set(EXE_NAME hello.exe)

project(HELLO)

set(SRC_LIST main.c)
add_executable(${EXE_NAME} ${SRC_LIST})
