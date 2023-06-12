cmake_minimum_required(VERSION 3.24)

set(This TestInOut)

set(Sources
        test_input.cpp
        test_output.cpp
        main.cpp
        )

add_executable(${This} ${Sources})
target_link_libraries(${This} PRIVATE
        gtest_main gtest in-out
        )

include(GoogleTest)
gtest_discover_tests(${This})