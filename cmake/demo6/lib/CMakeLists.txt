set(LIB_SRC hello.c)
add_library(hello SHARED ${LIB_SRC})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

