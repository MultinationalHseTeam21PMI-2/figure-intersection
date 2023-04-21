#include "../../src/core/Segment/Segment.h"
#include <gtest/gtest.h>


TEST(Segment, test_segment_constructor) {
    Point point1 = Point{1, 2};
    Point point2 = Point{1, 2};
    Segment segment{point1, point2};

    ASSERT_EQ(segment.point1(), point1);
    ASSERT_EQ(segment.point1(), point2);
}

TEST(Segment, test_segment_is_point) {
    Point point1 = Point{1, 2};
    Point point2 = Point{1, 2};
    Segment segment{point1, point2};

    ASSERT_TRUE(segment.isPoint());
}


TEST(Segment, test_segment_is_not_point) {
    Point point1 = Point{0, 0};
    Point point2 = Point{1, 1};
    Segment segment{point1, point2};

    ASSERT_FALSE(segment.isPoint());
}

TEST(Segment, test_segments_are_equal) {
    Segment segment1{{0, 0}, {1, 1}};
    Segment segment2{{0, 0}, {1, 1}};

    ASSERT_TRUE(segment1 == segment2);
}

TEST(Segment, test_segments_with_switched_points_are_equal) {
    Segment segment1{{0, 0}, {1, 1}};
    Segment segment2{{1, 1}, {0, 0}};

    ASSERT_TRUE(segment1 == segment2);
}