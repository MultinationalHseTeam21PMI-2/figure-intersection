#pragma once

#include <stdexcept>

#include "../Figure/Figure.h"

class Triangle : public Figure {
public:
    Triangle(const Point &point1, const Point &point2, const Point &point3)
        : Figure({Segment{point1, point2}, Segment{point2, point3}, Segment{point3, point1}}){};
};
