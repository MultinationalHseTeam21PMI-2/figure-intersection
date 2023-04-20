cmake_minimum_required(VERSION 3.24)

set(This TestCore)

set(Sources
    test_figure.cpp
    test_segment.cpp
    test_triangle.cpp
    main.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PRIVATE
    gtest_main gtest
)