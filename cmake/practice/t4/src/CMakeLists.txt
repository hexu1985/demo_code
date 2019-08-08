include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(main main.c)
target_link_libraries(main hello)
#target_link_libraries(main libhello.a)
#target_link_libraries(main libhello.so)
