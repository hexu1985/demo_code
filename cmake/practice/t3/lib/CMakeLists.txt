
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(LIBHELLO_SRC hello.c)

add_library(hello SHARED ${LIBHELLO_SRC})
set_target_properties(hello PROPERTIES VERSION 1.2 SOVERSION 1)
if(WIN32)
    set_target_properties(hello PROPERTIES LINKER_LANGUAGE C)
endif()
#set_target_properties(hello PROPERTIES LINK_FLAGS "${LINK_FLAGS} -static-libstdc++")

add_library(hello_static STATIC ${LIBHELLO_SRC})
#set_target_properties(hello_static PROPERTIES OUTPUT_NAME "hello")
#set_target_properties(hello_static PROPERTIES STATIC_LIBRARY_FLAGS "${LINK_FLAGS} -static-libstdc++")

get_target_property(OUTPUT_VALUE hello_static OUTPUT_NAME)
message(STATUS "This is the hello_static OUTPUT_NAME: " ${OUTPUT_VALUE})

install(TARGETS hello hello_static
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
install(FILES hello.h DESTINATION include/hello)
