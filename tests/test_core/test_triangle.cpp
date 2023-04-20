#include <gtest/gtest.h>

#include "../../src/core/Triangle/Triangle.h"

TEST(Triangle, test_triangle_creation_by_3_points) {
    Point p1 = {0, 0};
    Point p2 = {1, 1};
    Point p3 = {1, 0};

    Triangle triangle{p1, p2, p3};

    Segment expected_seg1{p1, p2};
    Segment expected_seg2{p2, p3};
    Segment expected_seg3{p3, p1};

    ASSERT_TRUE(triangle.containsSegment(expected_seg1));
    ASSERT_TRUE(triangle.containsSegment(expected_seg2));
    ASSERT_TRUE(triangle.containsSegment(expected_seg3));
}
