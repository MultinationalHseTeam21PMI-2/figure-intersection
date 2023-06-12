#include <gtest/gtest.h>
#include "../../src/core/Alghoritms/Alghoritms.h"



//Test to verify that the point lies on the inlet of the triangle
TEST(ContainsPointsTest, PointInPolygon) {
   Figure polygon = { Segment(Point(3.0, 6.0), Point(-1, 2)),
                      Segment(Point(-1, 2), Point(0, 10)),
                      Segment(Point(0, 10), Point(3.0, 6.0))
   };
   Point point(1, 7.0);

   bool result = isVertexInsidePolygon(polygon, point);

   ASSERT_TRUE(result);
}



//Check that the coordinate is not one of the vertices of the triangle
TEST(ContainsPointsTest, PointNotInPolygon) {
   std::vector<Point> points = { Point(3.0, 4.0), Point(5.0, 6.0), Point(1.0, 2.0) };
   Point point(7.0, 8.0);

   bool result = containsPoints(points, point);

   ASSERT_FALSE(result);
}



//Test to verify that the point does not lie on the inlet of the triangle
TEST(IsVertexInsidePolygonTest, VertexNotInsidePolygon) {
   Figure polygon({ Segment(Point(0.0, 0.0), Point(1.0, 0.0)),
                             Segment(Point(1.0, 0.0), Point(1.0, 1.0)),
                             Segment(Point(1.0, 1.0), Point(0.0, 1.0)),
                             Segment(Point(0.0, 1.0), Point(0.0, 0.0))
   });
   Point vertex(2, 2);

   bool result = isVertexInsidePolygon(polygon, vertex);

   ASSERT_FALSE(result);
}



//Test to find the vertices that lie within the second figure
TEST(FindInternalVerticesTest, InternalVertices) {
   Figure polygon1({
                     Segment(Point(2.0, 2.0), Point(4.0, 2.0)),
                     Segment(Point(4.0, 2.0), Point(6, 4.0)),
                     Segment(Point(6.0, 4.0), Point(4.0, 6.0)),
                     Segment(Point(4.0, 6.0), Point(2.0, 6.0)),
                     Segment(Point(2.0, 6.0), Point(0.0, 4.0)),
                     Segment(Point(0.0, 4.0), Point(2.0, 2.0))
   });


   Figure polygon2({
                     Segment(Point(2.0, 4.0), Point(4.0, 4.0)),
                     Segment(Point(4.0, 4.0), Point(6, 6.0)),
                     Segment(Point(6.0, 6.0), Point(4.0, 8.0)),
                     Segment(Point(4.0, 8.0), Point(2.0, 8.0)),
                     Segment(Point(2.0, 8.0), Point(0.0, 6.0)),
                     Segment(Point(0.0, 6.0), Point(2.0, 4.0))
   });


   std::vector<Point> expected = { Point(2.0, 4.0), Point(4.0, 4.0),
                                   Point(2.0, 6.0), Point(4.0, 6.0)
   };
   std::sort(expected.begin(), expected.end());


   std::vector<Point> result = findInternalVertices(polygon1, polygon2);
   std::sort(result.begin(), result.end());

   ASSERT_EQ(expected, result);
}



//Test to check that two pieces do not intersect
TEST(FindInternalVerticesTest, NoInternalVertices) {
   Figure polygon1({
                     Segment(Point(2.0, 2.0), Point(4.0, 2.0)),
                     Segment(Point(4.0, 2.0), Point(6, 4.0)),
                     Segment(Point(6.0, 4.0), Point(4.0, 6.0)),
                     Segment(Point(4.0, 6.0), Point(2.0, 6.0)),
                     Segment(Point(2.0, 6.0), Point(0.0, 4.0)),
                     Segment(Point(0.0, 4.0), Point(2.0, 2.0))
   });


   Figure polygon2({
                     Segment(Point(8.0, 4.0), Point(10.0, 4.0)),
                     Segment(Point(10.0, 4.0), Point(12, 6.0)),
                     Segment(Point(12.0, 6.0), Point(10.0, 8.0)),
                     Segment(Point(10.0, 8.0), Point(8.0, 8.0)),
                     Segment(Point(8.0, 8.0), Point(6.0, 6.0)),
                     Segment(Point(6.0, 6.0), Point(8.0, 4.0))
   });

   std::vector<Point> result = findInternalVertices(polygon1, polygon2);
   std::sort(result.begin(), result.end());

   ASSERT_EQ(0, result.size());
}



//Test whether one shape lies inside another shape
TEST(FindInternalVerticesTest, FigureInside) {
   Figure polygon1({
                     Segment(Point(2.0, 2.0), Point(4.0, 2.0)),
                     Segment(Point(4.0, 2.0), Point(6, 4.0)),
                     Segment(Point(6.0, 4.0), Point(4.0, 6.0)),
                     Segment(Point(4.0, 6.0), Point(2.0, 6.0)),
                     Segment(Point(2.0, 6.0), Point(0.0, 4.0)),
                     Segment(Point(0.0, 4.0), Point(2.0, 2.0))
   });


   Figure polygon2({
                     Segment(Point(2.0, 3.0), Point(4.0, 3.0)),
                     Segment(Point(4.0, 3.0), Point(4, 5.0)),
                     Segment(Point(4, 5.0), Point(2, 5)),
                     Segment(Point(2, 5), Point(2.0, 3.0))
   });


   std::vector<Point> expected = { Point(2.0, 3.0), Point(4.0, 3.0),
                                   Point(4.0, 5.0), Point(2.0, 5.0)
   };
   std::sort(expected.begin(), expected.end());

   std::vector<Point> result = findInternalVertices(polygon1, polygon2);
   std::sort(result.begin(), result.end());

   ASSERT_EQ(expected, result);
}