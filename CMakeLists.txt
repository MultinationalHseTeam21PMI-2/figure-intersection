cmake_minimum_required(VERSION 3.24)
project(figure_intersection)

set(CMAKE_CXX_STANDARD 17)

enable_testing()
add_subdirectory(googletest)
add_subdirectory(tests)
add_subdirectory(src/core)
add_subdirectory(src/in-out)

add_executable(figure_intersection
    src/main.cpp
)
target_link_libraries(figure_intersection core in-out)