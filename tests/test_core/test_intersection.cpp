#include <gtest/gtest.h>

#include "../../src/core/Algorithms/Algorithms.h"
#include "../../src/core/Segment/Segment.h"
#include "../../src/core/Triangle/Triangle.h"
// Intersection for segments

TEST(Segment, test_segment_intersection_is_segment) {
    Point a(-6.67, 3.5), b(4.09, 4.62), c(11.467539, 5.3879223), d(-2.1667461, 3.96874017);
    Segment X(a, b), Y(c, d);
    Segment Intersection_XY = *intersection(X, Y);

    Segment expected_segment(d, b);
    ASSERT_EQ(Intersection_XY, expected_segment);
}

TEST(Segment, test_segment_intersection_is_point) {
    {
        Point a(-6.67, 3.5), b(4.09, 4.62);
        Point E(-5.03, 7.72), F(-2.39, 1.34);
        Segment X(a, b);
        Segment Z(E, F);
        Segment Intersection_XY = *intersection(X, Z);

        ASSERT_TRUE(Intersection_XY.isPoint());
        ASSERT_TRUE(Intersection_XY.point1() == Point(-3.4236192700012, 3.8379132358363));
    }
    {
        Point A(0, 0), B(2, 2), C(0, 0), D(-2, 2);
        Segment first = Segment(A, B), second = Segment(C, D);
        Segment Intersection_XY = *intersection(first, second);

        Segment expected_segment(A, A);
        ASSERT_TRUE(Intersection_XY.isPoint());
        ASSERT_EQ(Intersection_XY, expected_segment);
    }
}

TEST(Segment, test_segment_intersection) {
    Point x_A(1, 3), x_B(1, 7), x_C(1.00001, 4.5), x_D(1, 9);
    Segment first(x_A, x_B), second(x_C, x_D);
    Segment Intersection_XY = *intersection(first, second);

    Segment expected_segment(x_B, x_C);
    ASSERT_EQ(Intersection_XY, expected_segment);
}

TEST(Segment, test_segments_no_intersection_1) {
    {
        Point A(1, 1), B(2, 2), C(3, 3), D(4, 4);
        Segment AB(A, B), CD(C, D);

        std::unique_ptr<Segment> intersection_AB_CD = intersection(AB, CD);
        ASSERT_EQ(intersection_AB_CD.get(), nullptr);
    }
}
TEST(Segment, test_segments_no_intersection_2) {
    {
        Point A(1, 1), B(2, 2), C(-1, 1), D(-2, 2);
        Segment AB = Segment(A, B), CD = Segment(C, D);
        std::unique_ptr<Segment> Intersection_XY = intersection(AB, CD);
        ASSERT_EQ(Intersection_XY.get(), nullptr);
    }
}

// Intersection for triangles/figures
TEST(Triangle, test_triangles_intersection_1) {
    {
        Point A(-6, 6), B(-9, 2), C(-4, 2),
                D(-6, 6), E(-9, 2), F(-4, 2);
        Triangle first(A, B, C), second(D, E, F);
        std::vector<Segment> result = intersection(first, second);
        std::set<Segment> expected_segments{Segment(Point(-6, 6), Point(-9, 2)), Segment(Point(-6, 6), Point(-4, 2)),
                                            Segment(Point(-9, 2), Point(-4, 2))};
        std::set<Segment> actual;
        for (auto x: result) {
            actual.insert(x);
        }

        ASSERT_EQ(actual, expected_segments);
    }
}

TEST(Figure, test_triangle_intersection_2) {
    {
        Point A(-6, 6), B(-9, 2), C(-4, 2),
                D(-5.334, 4.668), E(-3.298, 0.596), F(-10, 5);
        Segment AB(A, B), AC(A, C), BC(B, C),
                DE(D, E), DF(D, F), EF(E, F);
        Figure first{AB, AC, BC}, second{DE, DF, EF};
        auto result = intersection(first, second);
        std::set<Segment> expected_segments{Segment(Point(-6.91465, 4.78047), Point(-6.91465, 4.78047)), Segment(Point(-7.82294, 3.56942), Point(-7.822294, 3.56943)),
                                            Segment(Point(-5.334, 4.668), Point(-4, 2)), Segment(Point(-5.4346, 2), Point(-5.4346, 2))};
        std::set<Segment> actual;
        for (auto x: result) {
            actual.insert(x);
        }
        ASSERT_EQ(actual, expected_segments);
    }
}

TEST(Figure, test_triangle_intersection_3) {
    {
        Point A(0, 1.7), B(0, 7.64), C(0, 3.56),
                D(0, 2.76), E(0, 6), F(3, 6);
        Segment AB(A, B), AC(A, C), BC(B, C),
                DE(D, E), DF(D, F), EF(E, F);
        Figure first{AB, AC, BC}, second{DE, DF, EF};
        auto result = intersection(first, second);
        Segment expected_segment(Point(0, 2.76), Point(0, 6));
        ASSERT_EQ(result[0], expected_segment);
    }
}
