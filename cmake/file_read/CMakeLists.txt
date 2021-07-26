project(HELLO)

file(STRINGS main.c THE_VALUE)

message("THE_VALUE: ${THE_VALUE}")

set(EXE_NAME hello.exe)
set(SRC_LIST main.c)
add_executable(${EXE_NAME} ${SRC_LIST})
