project(HELLO)

# NEWLINE_CONSUME如果不指定这个参数, 文件中的\n就被替换成;
file(STRINGS main.c THE_VALUE NEWLINE_CONSUME)

message("THE_VALUE: ${THE_VALUE}")

set(EXE_NAME hello.exe)
set(SRC_LIST main.c)
add_executable(${EXE_NAME} ${SRC_LIST})
