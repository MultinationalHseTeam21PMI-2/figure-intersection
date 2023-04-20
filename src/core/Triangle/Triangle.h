#pragma once
#include "../Figure/Figure.h"
#include <stdexcept>


class Triangle : public Figure {
public:
    Triangle() {
        Triangle(Point{0, 1}, Point{1, 0}, Point{-1, 0});
    }


    Triangle(const Point &point1, const Point &point2, const Point &point3)
        : Figure({Segment{point1, point2}, Segment{point2, point3}, Segment{point3, point3}}){};
};
