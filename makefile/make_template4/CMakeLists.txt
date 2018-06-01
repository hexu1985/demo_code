include_directories(${PROJECT_SOURCE_DIR})

set(TEST1_SRC test1.c)
add_executable(test1 ${TEST1_SRC})
target_link_libraries(test1 pthread)

set(TEST2_SRC test2.c)
add_executable(test2 ${TEST2_SRC})
target_link_libraries(test2 pthread)

set(TEST3_SRC test3.c)
add_executable(test3 ${TEST3_SRC})
target_link_libraries(test3 pthread)
