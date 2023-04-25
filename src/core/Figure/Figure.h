#pragma once

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "../Segment/Segment.h"

class Figure {
private:
    std::vector<Segment> m_segments;
    size_t m_count_vertices;

    bool isCorrectFigure() const;

public:
    Figure() {}

    Figure(std::initializer_list<Segment> segments);

    size_t getCountVertices() const;
    const std::vector<Segment> &getSegments() const;

    bool containsSegment(const Segment &segment) const;
};