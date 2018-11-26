
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)

if (DEFINED ENV{TARGET_OS})
    message(STATUS "env TARGET_OS is $ENV{TARGET_OS}")
else()
    message(WARNING "not defined TARGET_OS env")
endif()

set(EXE_NAME hello.exe)

project(HELLO)

set(SRC_LIST main.c)
add_executable(${EXE_NAME} ${SRC_LIST})
