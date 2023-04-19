#pragma once
#include "../Figure/Figure.h"

class Triangle : private Figure {
public:
    Triangle() {
        Triangle(Point{0, 1}, Point{1, 0}, {-1, 0});
    }

    Triangle(const Point point1, const Point point2, const Point point3) {
        Segment seg1 = Segment(point1, point2);
        Segment seg2 = Segment(point2, point3);
        Segment seg3 = Segment(point3, point1);

        Figure{seg1, seg2, seg3};
    }
};
