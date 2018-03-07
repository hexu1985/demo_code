project(HELLO)
message(STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})
message(STATUS "PROJECT_SOURCE_DIR: "${PROJECT_SOURCE_DIR})
add_subdirectory(src bin)

install(FILES COPYRIGHT README DESTINATION share/doc/cmake/t2)
install(PROGRAMS runhello.sh DESTINATION bin)
install(DIRECTORY doc/ DESTINATION share/doc/cmake/t2)
