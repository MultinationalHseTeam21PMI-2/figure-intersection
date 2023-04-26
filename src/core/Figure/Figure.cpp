#include "Figure.h"

#include <set>

bool Figure::isCorrectFigure() const {
    if (m_segments.size() == 1) {
        return true;
    }

    std::vector<Point> all_points;
    std::set<Point> points;

    for (auto segment: m_segments) {
        all_points.push_back(segment.point1());
        all_points.push_back(segment.point2());
        points.insert(segment.point1());
        points.insert(segment.point2());
    }

    for (auto point: points) {
        const int count = std::count(all_points.begin(), all_points.end(), point);
        if (count != 2) {
            return false;
        }
    }

    return true;
}


size_t Figure::getCountVertices() const {
    return m_count_vertices;
}


const std::vector<Segment> &Figure::getSegments() const {
    return m_segments;
}


Figure::Figure(std::initializer_list<Segment> segments) {
    for (auto segment: segments) {
        if (segment.isPoint() || containsSegment(segment)) {
            continue;
        }

        m_segments.push_back(segment);
    }

    if (!isCorrectFigure())
        throw std::runtime_error("Can't create figure by passed segments");

    if (m_segments.size() == 1) {
        m_count_vertices = 2;
    } else {
        m_count_vertices = m_segments.size();
    }
}


bool Figure::containsSegment(const Segment &segment) const {
    Segment reversed_segment(segment.point2(), segment.point1());
    auto result1 = std::find(m_segments.begin(), m_segments.end(), segment);
    auto result2 = std::find(m_segments.begin(), m_segments.end(), reversed_segment);

    return result1 != m_segments.end() || result2 != m_segments.end();
}
