#pragma once

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

#include "../Point/Point.h"

/// @brief Class segment realise the segment in 2d space
class Segment {
private:
    Point m_point1;
    Point m_point2;

public:
    Segment() = delete;


    /// @brief Constructor for class segment, sequence of parameters doesn't make sense
    /// @param point1
    /// @param point2
    Segment(const Point &point1, const Point &point2) : m_point1(point1), m_point2(point2){};


    const Point &point1() const { return m_point1; }
    const Point &point2() const { return m_point2; }


    /// @brief Method to check if segment is point
    /// @return true if m_point1 == m_point2
    bool isPoint() const { return m_point1 == m_point2; }

    inline double get_slope() const {
        if (std::abs(m_point1.x - m_point2.x) > PRECISION) {
            return (m_point1.y - m_point2.y) / (m_point1.x - m_point2.x);
        }
        return 0;
    }


    bool operator==(const Segment other) const {
        return (m_point1 == other.m_point1 && m_point2 == other.m_point2) ||
               (m_point1 == other.m_point2 && m_point2 == other.m_point1);
    }

    bool operator<(const Segment& other) const {
        return m_point1.norm() + m_point2.norm() < other.point1().norm() + other.point2().norm();
    }
};
