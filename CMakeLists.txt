cmake_minimum_required(VERSION 3.24)
project(figure_intersection)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

enable_testing()
add_subdirectory(googletest)
add_subdirectory(tests)
add_subdirectory(src/core)
add_subdirectory(src/in-out)
add_subdirectory(src/gui)

add_executable(figure_intersection src/main.cpp)

target_link_libraries(figure_intersection core in-out gui Qt6::Core Qt6::Widgets)