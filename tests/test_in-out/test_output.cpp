#include <gtest/gtest.h>
#include "../../src/in-out/in_out.h"



//Test output when shapes do not intersect
TEST(OutputTest, NoIntersection) {
    std::stringstream outputStream;
    std::streambuf* origCout = std::cout.rdbuf(outputStream.rdbuf());

    std::vector<Segment> segments;

    output(segments);

    std::cout.rdbuf(origCout);

    ASSERT_EQ("No triangle intersections found\n", outputStream.str());
}



//Test output when shapes intersect by segments
TEST(OutputTest, IntersectionsOnSegments) {
    std::stringstream outputStream;

    std::streambuf* origCout = std::cout.rdbuf(outputStream.rdbuf());

    std::vector<Segment> segments = {Segment(Point(1.0, 1.0), Point(2.0, 2.0)),
                                     Segment(Point(3.0, 3.0), Point(4.0, 4.0))};

    output(segments);

    std::cout.rdbuf(origCout);

    ASSERT_EQ("Triangles intersect on segment: (1, 1) - (2, 2)\nTriangles intersect on segment: (3, 3) - (4, 4)\n",
              outputStream.str());
}



//Test output when shapes intersect by vertices
TEST(OutputTest, IntersectionOnVertrex) {
    std::stringstream outputStream;

    std::streambuf* origCout = std::cout.rdbuf(outputStream.rdbuf());

    std::vector<Segment> segments = {Segment(Point(1.0, 1.0), Point(1.0, 1.0)),
                                     Segment(Point(2.0, 1.0), Point(2.0, 1.0))};

    output(segments);

    std::cout.rdbuf(origCout);

    ASSERT_EQ("Triangle intersection point: (1, 1)\nTriangle intersection point: (2, 1)\n",
              outputStream.str());
}