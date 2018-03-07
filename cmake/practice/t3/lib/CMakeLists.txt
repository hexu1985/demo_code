set(LIBHELLO_SRC hello.c)

add_library(hello SHARED ${LIBHELLO_SRC})
set_target_properties(hello PROPERTIES VERSION 1.2 SOVERSION 1)

add_library(hello_static STATIC ${LIBHELLO_SRC})
set_target_properties(hello_static PROPERTIES OUTPUT_NAME "hello")

get_target_property(OUTPUT_VALUE hello_static OUTPUT_NAME)
message(STATUS "This is the hello_static OUTPUT_NAME: " ${OUTPUT_VALUE})

install(TARGETS hello hello_static
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
install(FILES hello.h DESTINATION include/hello)
