#pragma once

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "../Segment/Segment.h"

class Figure {
public:
    std::vector<Segment> m_segments;
    size_t m_count_vertices;

public:
    Figure() {}

    Figure(std::initializer_list<Segment> segments);

    size_t getCountVertices() const { return m_count_vertices; }
    const std::vector<Segment> &getSegments() const { return m_segments; }

    bool containsSegment(const Segment &segment) const;

    /// @brief Method intersection finds intersections between two figures
    /// @param figure1
    /// @param figure2
    /// @return vector of segments
    static std::vector<Segment> &intersection(const Figure figure1, const Figure figure2);
};