#include <gtest/gtest.h>

#include "../../src/core/ConvexFigure/ConvexFigure.h"

TEST(ConvexFigure, test_figure_constructor_with_3_segments) {
    Point p1{0, 0};
    Point p2{0, 1};
    Point p3{1, 1};
    Point p4{1, 0};


    ConvexFigure figure{p1, p2, p3, p4};

    std::vector<Segment> segments{Segment(p1, p2), Segment(p2, p3), Segment(p3,p4), Segment(p4, p1)};
    ASSERT_EQ(figure.getSegments(), segments);
}
