#include "Figure.h"

Figure::Figure(std::initializer_list<Segment> segments) {
    for (auto segment: segments) {
        if (segment.isPoint() || containsSegment(segment)) {
            continue;
        }
        m_segments.push_back(segment);
    }

    // TODO: Check if can't create figure by passed segments
    m_count_vertices = m_segments.size();
}


bool Figure::containsSegment(const Segment &segment) const {
    Segment reversed_segment(segment.point2(), segment.point1());
    auto result1 = std::find(m_segments.begin(), m_segments.end(), segment);
    auto result2 = std::find(m_segments.begin(), m_segments.end(), reversed_segment);

    return result1 != m_segments.end() || result2 != m_segments.end();
}
