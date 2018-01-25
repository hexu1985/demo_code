include_directories(${PROJECT_SOURCE_DIR}/lib)
set(APP_SRC main.c)
add_executable(test ${APP_SRC})
target_link_libraries(test hello)
