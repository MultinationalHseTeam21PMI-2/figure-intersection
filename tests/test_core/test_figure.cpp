#include <gtest/gtest.h>

#include "../../src/core/Figure/Figure.h"

TEST(Figure, test_figure_constructor_with_3_segments) {
    Point p1{0, 0};
    Point p2{1, 1};
    Point p3{1, 0};

    Segment seg1 = {p1, p2};
    Segment seg2 = {p2, p3};
    Segment seg3 = {p3, p1};

    Figure figure{seg1, seg2, seg3};

    std::vector<Segment> expected_vector{seg1, seg2, seg3};
    ASSERT_EQ(figure.getSegments(), expected_vector);
}

TEST(Figure, test_figure_constructor_with_3_equal_segments) {
    Point p1{0, 0};
    Point p2{1, 1};

    Segment seg1 = {p1, p2};
    Segment seg2 = {p1, p2};
    Segment seg3 = {p1, p2};

    Figure figure{seg1, seg2, seg3};
    std::vector<Segment> expected_vector{seg1};
    ASSERT_EQ(figure.getSegments(), expected_vector);
}

TEST(Figure, test_figure_constructor_with_1_segment) {
    Point p1{0, 0};
    Point p2{1, 1};

    Segment seg1 = {p1, p2};

    Figure figure{seg1};
    std::vector<Segment> expected_vector{seg1};
    ASSERT_EQ(figure.getSegments(), expected_vector);
}

TEST(Figure, test_figure_constructor_with_point) {
    Point p1{0, 0};

    Segment seg1 = {p1};

    Figure figure{seg1};
    std::vector<Segment> expected_vector{seg1};
    ASSERT_EQ(figure.getSegments(), expected_vector);
}

TEST(Figure, test_figure_segments_are_not_connected_expects_error) {
    Segment seg1 = {Point{0, 0}, Point{1, 1}};
    Segment seg2 = {Point{2, 2}, Point{3, 3}};
    Segment seg3 = {Point{4, 4}, Point{5, 5}};

    std::initializer_list<Segment> list{seg1, seg2, seg3};
    try {
        Figure test(list);
        FAIL();
    } catch (std::runtime_error const &err) {
        EXPECT_EQ(err.what(), std::string("Can't create figure by passed segments"));
    } catch (...) {
        FAIL();
    }
}



TEST(Figure, test_figure_constructor_points_throw_error) {
    Segment seg1 = {Point{0, 0}};
    Segment seg2 = {Point{2, 2}};
    Segment seg3 = {Point{4, 4}};

    std::initializer_list<Segment> list{seg1, seg2, seg3};
    try {
        Figure test(list);
        FAIL();
    } catch (std::runtime_error const &err) {
        EXPECT_EQ(err.what(), std::string("Can't create figure by passed segments"));
    } catch (...) {
        FAIL();
    }
}