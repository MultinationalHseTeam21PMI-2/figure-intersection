#include "../../src/core/Segment/Segment.h"
#include <gtest/gtest.h>


TEST(Segment, test_segment_constructor) {
    Point point1{1, 2};
    Point point2{1, 2};
    Segment segment{point1, point2};

    ASSERT_EQ(segment.point1(), point1);
    ASSERT_EQ(segment.point1(), point2);
}

TEST(Segment, test_segment_is_point) {
    Point point1{1, 2};
    Point point2{1, 2};
    Segment segment{point1, point2};

    ASSERT_TRUE(segment.isPoint());
}


TEST(Segment, test_segment_is_not_point) {
    Point point1{0, 0};
    Point point2{1, 1};
    Segment segment{point1, point2};

    ASSERT_FALSE(segment.isPoint());
}

TEST(Segment, test_segments_are_equal) {
    Segment segment1{Point{0, 0}, Point{1, 1}};
    Segment segment2{Point{0, 0}, Point{1, 1}};

    ASSERT_TRUE(segment1 == segment2);
}

TEST(Segment, test_segments_with_switched_points_are_equal) {
    Segment segment1{Point{0, 0}, Point{1, 1}};
    Segment segment2{Point{1, 1}, Point{0, 0}};

    ASSERT_TRUE(segment1 == segment2);
}


TEST(Segment, test_segment_intersection_is_segment) {
    Point a(-6.67, 3.5), b(4.09, 4.62), c(11.467539, 5.3879223), d(-2.1667461, 3.96874017);
    Segment X(a, b), Y(c, d);
    Segment Intersection_XY = *Segment::intersection(X, Y);

    ASSERT_EQ(Intersection_XY.point1(), d);
    ASSERT_EQ(Intersection_XY.point2(), b);
}

TEST(Segment, test_segment_intersection_is_point) {
    Point a(-6.67, 3.5), b(4.09, 4.62);
    Point E(-5.03, 7.72), F(-2.39, 1.34);
    Segment X(a, b);
    Segment Z(E, F);
    Segment Intersection_XY = *Segment::intersection(X, Z);

    ASSERT_TRUE(Intersection_XY.isPoint());
    ASSERT_TRUE(Intersection_XY.point1() == Point(-3.4236192700012, 3.8379132358363));
}

TEST(Segment, test_segment_intersection) {
    Point x_A(1, 3), x_B(1, 7), x_C(1.00001, 4.5), x_D(1, 9);
    Segment first(x_A, x_B), second(x_C, x_D);
    Segment Intersection_XY = *Segment::intersection(first, second);

    ASSERT_EQ(Intersection_XY.point1(), x_C);
    ASSERT_EQ(Intersection_XY.point2(), x_B);
}

TEST(Segment, test_segments_no_intersection) {
    Point A(1, 1), B(2, 2), C(3, 3), D(4, 4);
    Segment AB(A, B), CD(C, D);

    std::unique_ptr<Segment> intersection = Segment::intersection(AB, CD);
    ASSERT_EQ(intersection.get(), nullptr);
}