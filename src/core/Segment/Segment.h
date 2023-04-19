#pragma once
#include <utility>

typedef std::pair<double, double> Point;

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


    bool operator==(const Segment other) const {
        return m_point1 == other.m_point1 && m_point2 == other.m_point2;
    }


    /// @brief Static method that finds intersection between two segments
    /// @param seg1
    /// @param seg2
    /// @return nullptr if no intersection | Segment*
    static const Segment *intersection(const Segment &seg1, const Segment &seg2);
};
