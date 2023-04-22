#pragma once
#include <algorithm>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#define PRECISION 0.001
class Point {
public:
    double x, y;
    explicit Point(double a = 0, double b = 0) {
        x = a, y = b;
    }
    double norm() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2)); }
    Point operator+(Point b) { return Point(x + b.x, y + b.y); }
    Point operator-(Point b) { return Point(x - b.x, x - b.y); }
    bool operator==(Point b) const {
        return (std::abs(x - b.x) < PRECISION && std::abs(y - b.y) < PRECISION);
    }
};

inline double norm(Point a) {
    return std::sqrt(std::pow(a.x, 2) + std::pow(a.y, 2));
}


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
        if (std::abs(m_point1.x - m_point2.x) > PRECISION)
            return (m_point1.y - m_point2.y) / (m_point1.x - m_point2.x);
        return 0;
    }


    bool operator==(const Segment other) const {
        return (m_point1 == other.m_point1 && m_point2 == other.m_point2) ||
               (m_point1 == other.m_point2 && m_point2 == other.m_point1);
    }


    /// @brief Static method that finds intersection between two segments
    /// @param seg1
    /// @param seg2
    /// @return nullptr if no intersection | Segment*
    static std::unique_ptr<Segment> intersection(const Segment &a, const Segment &b);
};
