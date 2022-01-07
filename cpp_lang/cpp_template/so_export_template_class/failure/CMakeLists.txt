#project(HELLO)
add_subdirectory(hello)

include_directories(hello)
set(APP_SRC test1.cpp)
add_executable(test1 ${APP_SRC})
target_link_libraries(test1 hello)
