
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)

project(HELLO)

set(SRC_LIST main.c)
add_executable(hello ${SRC_LIST})
