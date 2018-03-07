set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
add_executable(hello main.c)

#install(TARGETS myrun mylib mystaticlib
#    RUNTIME DESTINATION bin
#    LIBRARY DESTINATION lib
#    ARCHIVE DESTINATION libstatic
#    )
install(TARGETS hello RUNTIME DESTINATION bin)
