#include <gtest/gtest.h>
#include "../../src/in-out/in_out.h"



//Test output when shapes do not intersect
TEST(OutputTest, NoIntersection) {
    std::stringstream outputStream;
    std::streambuf* origCout = std::cout.rdbuf(outputStream.rdbuf());

    std::vector<Point> points;

    output(points);

    std::cout.rdbuf(origCout);

    ASSERT_EQ("No shape intersections found\n", outputStream.str());
}



//Test output when shapes intersect by all unique vertices
TEST(OutputTest, IntersectionsOnSegments) {
    std::stringstream outputStream;

    std::streambuf* origCout = std::cout.rdbuf(outputStream.rdbuf());

    std::vector<Point> points = {Point(1.0, 1.0), Point(2.0, 2.0),
                                 Point(3.0, 3.0), Point(4.0, 4.0)};

    output(points);

    std::cout.rdbuf(origCout);

    ASSERT_EQ("Shape intersection point: (1, 1)\n"
              "Shape intersection point: (2, 2)\n"
              "Shape intersection point: (3, 3)\n"
              "Shape intersection point: (4, 4)\n",
              outputStream.str());
}



//Test output when shapes intersect by vertices
TEST(OutputTest, IntersectionOnVertrex) {
    std::stringstream outputStream;

    std::streambuf* origCout = std::cout.rdbuf(outputStream.rdbuf());

    std::vector<Point> points = {Point(1.0, 1.0), Point(1.0, 1.0),
                                     Point(2.0, 1.0), Point(2.0, 1.0)};

    output(points);

    std::cout.rdbuf(origCout);

    ASSERT_EQ("Shape intersection point: (1, 1)\n"
              "Shape intersection point: (2, 1)\n",
              outputStream.str());
}