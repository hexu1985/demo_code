cmake_minimum_required ( VERSION 3.20 )

project ( testprj )

find_package ( benchmark REQUIRED )

add_executable ( ${PROJECT_NAME}
    main.cpp
)

target_link_libraries( ${PROJECT_NAME} 
    PRIVATE 
        benchmark::benchmark
)

