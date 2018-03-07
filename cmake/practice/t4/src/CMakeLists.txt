include_directories(/tmp/t3/usr/include/hello)
link_directories(/tmp/t3/usr/lib)

add_executable(main main.c)
target_link_libraries(main hello)
#target_link_libraries(main libhello.a)
#target_link_libraries(main libhello.so)
