#include <gtest/gtest.h>

#include "../../src/core/Alghoritms/Alghoritms.h"
#include "../../src/core/Segment/Segment.h"

// Intersection for segments

TEST(Segment, test_segment_intersection_is_segment) {
    Point a(-6.67, 3.5), b(4.09, 4.62), c(11.467539, 5.3879223), d(-2.1667461, 3.96874017);
    Segment X(a, b), Y(c, d);
    Segment Intersection_XY = *intersection(X, Y);

    Segment expected_segment(d, b);
    ASSERT_EQ(Intersection_XY, expected_segment);
}

TEST(Segment, test_segment_intersection_is_point) {
    Point a(-6.67, 3.5), b(4.09, 4.62);
    Point E(-5.03, 7.72), F(-2.39, 1.34);
    Segment X(a, b);
    Segment Z(E, F);
    Segment Intersection_XY = *intersection(X, Z);

    ASSERT_TRUE(Intersection_XY.isPoint());
    ASSERT_TRUE(Intersection_XY.point1() == Point(-3.4236192700012, 3.8379132358363));
}

TEST(Segment, test_segment_intersection) {
    Point x_A(1, 3), x_B(1, 7), x_C(1.00001, 4.5), x_D(1, 9);
    Segment first(x_A, x_B), second(x_C, x_D);
    Segment Intersection_XY = *intersection(first, second);

    Segment expected_segment(x_B, x_C);
    ASSERT_EQ(Intersection_XY, expected_segment);
}

TEST(Segment, test_segments_no_intersection) {
    Point A(1, 1), B(2, 2), C(3, 3), D(4, 4);
    Segment AB(A, B), CD(C, D);

    std::unique_ptr<Segment> intersection_AB_CD = intersection(AB, CD);
    ASSERT_EQ(intersection_AB_CD.get(), nullptr);
}

TEST(Segment, test_segments_no_intersection) {
    Point A(1,1), B(2,2), C(-1,1), D(-2,2);
    Segment AB = Segment(A,B), CD = Segment(C,D);
    std::unique_ptr<Segment> Intersection_XY = intersection(first,second);
    ASSERT_EQ(Intersection_XY, nullptr)
}

TEST(Segment, test_segment_intersection_is_point) {
    Point A(0,0), B(2,2), C(0,0), D(-2,2);
    Segment first = Segment(A,B), second = Segment(C,D);
    std::unique_ptr<Segment> Intersection_XY = intersection(first,second);

    Segment expected_segment(A, A);
    ASSERT_TRUE(Intersection_XY.isPoint())
    ASSERT_EQ(Intersection_XY, expected_segment)        
}

// Intersection for figures
