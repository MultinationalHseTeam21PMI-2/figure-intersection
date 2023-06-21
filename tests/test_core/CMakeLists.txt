cmake_minimum_required(VERSION 3.20)

set(This TestCore)

set(Sources
    test_figure.cpp
    test_segment.cpp
    test_triangle.cpp
    test_intersection.cpp
    test_in_point.cpp
    test_convexfigure.cpp
    main.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PRIVATE
    gtest_main gtest core
)

include(GoogleTest)
gtest_discover_tests(${This})