#pragma once

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

#include "../Figure/Figure.h"
#include "../Point/Point.h"
#include "../Segment/Segment.h"

/// @brief Method that finds intersection between two segments
/// @param seg1
/// @param seg2
/// @return nullptr if no intersection | Segment*
std::unique_ptr<Segment> intersection(const Segment &a, const Segment &b);

bool containsPoints(const std::vector<Point>& points, const Point& point);
bool isVertexInsidePolygon(const Figure& polygon, const Point& point);
std::vector<Point> findInternalVertices(const Figure& polygon1, const Figure& polygon2);

/// @brief Method that finds intersections between two figures
/// @param figure1
/// @param figure2
/// @return vector of segments
std::vector<Segment> intersection(const Figure &figure1, const Figure &figure2);