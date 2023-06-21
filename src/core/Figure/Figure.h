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

protected:
    void ConstructFigure(std::vector<Segment> &segment);
public:
    Figure() {}

    Figure(std::initializer_list<Segment> segments);
    Figure(std::vector<Segment> &segments);

    size_t getCountVertices() const;
    const std::vector<Segment> getSegments() const;

    bool containsSegment(const Segment &segment) const;
};