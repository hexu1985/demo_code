project(HELLO)

if (EXISTS "main.c")
    message("main.c is exists")
else()
    message("main.c is not exists")
endif()

if (EXISTS "no_such.c")
    message("no_such.c is exists")
else()
    message("no_such.c is not exists")
endif()

set(EXE_NAME hello.exe)
set(SRC_LIST main.c)
add_executable(${EXE_NAME} ${SRC_LIST})
