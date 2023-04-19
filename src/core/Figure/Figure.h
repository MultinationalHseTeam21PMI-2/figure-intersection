#pragma once
#include "../Segment/Segment.h"
#include <algorithm>
#include <vector>


class Figure {
public:
    std::vector<Segment> m_segments;
    size_t m_count_vertices;

public:
    Figure() {
    }

    Figure(std::initializer_list<Segment> segments) {
        for (auto segment: segments) {
            if (segment.isPoint()) { continue; }
            if (containsSegment(segment)) { continue; }
            m_segments.push_back(segment);
        }

        // TODO: Check if can't create figure by passed segments
        m_count_vertices = m_segments.size();
    }


    bool containsSegment(const Segment segment) const {
        auto result = std::find(m_segments.begin(), m_segments.end(), segment);
        return result != m_segments.end();
    }


    /// @brief Method intersection finds intersections between two figures
    /// @param figure1
    /// @param figure2
    /// @return vector of segments
    static std::vector<Segment> &intersection(const Figure figure1, const Figure figure2);
};