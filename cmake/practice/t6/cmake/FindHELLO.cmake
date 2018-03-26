find_path(HELLO_INCLUDE_DIR hello.h /usr/include/hello
    /usr/local/include/hello
    /tmp/include/hello)
find_library(HELLO_LIBRARY NAMES hello PATHS /usr/lib
    /usr/local/lib
    /tmp/lib)

if (HELLO_INCLUDE_DIR)
    message(STATUS "Found hello.h: ${HELLO_INCLUDE_DIR}")
else (HELLO_INCLUDE_DIR)
    message(STATUS "Not found hello.h")
endif (HELLO_INCLUDE_DIR)

if (HELLO_LIBRARY)
    message(STATUS "Found hello: ${HELLO_LIBRARY}")
else (HELLO_LIBRARY)
    message(STATUS "Not found hello")
endif (HELLO_LIBRARY)

if (HELLO_INCLUDE_DIR AND HELLO_LIBRARY)
    set(HELLO_FOUND TRUE)
endif (HELLO_INCLUDE_DIR AND HELLO_LIBRARY)

if (HELLO_FOUND)
    if (NOT HELLO_FIND_QUIETLY)
        message(STATUS "Found Hello: ${HELLO_LIBRARY}")
    endif (NOT HELLO_FIND_QUIETLY)
else (HELLO_FOUND)
    if (HELLO_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find hello library")
    endif (HELLO_FIND_REQUIRED)
endif (HELLO_FOUND)
