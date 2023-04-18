cmake_minimum_required(VERSION 3.24)
project(figure_intersection)

set(CMAKE_CXX_STANDARD 17)

add_executable(figure_intersection src/main.cpp src/core/Segment/Segment.cpp src/core/Segment/Segment.h src/core/Figure/Figure.cpp src/core/Figure/Figure.h src/core/Triangle/Triangle.cpp src/core/Triangle/Triangle.h)
