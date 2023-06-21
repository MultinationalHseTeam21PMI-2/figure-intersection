#pragma once

#include <algorithm>
#include <cmath>
#include <memory>
#include <stdexcept>

constexpr double PRECISION = 0.001;

class Point {
public:
    double x, y;
    explicit Point(double a = 0, double b = 0) : x(a), y(b) {}

    double norm() const {
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }

    bool operator<(const Point &b) const {
        return norm() < b.norm();
    }

    Point operator+(const Point &b) {
        return Point(x + b.x, y + b.y);
    }

    Point operator-(const Point &b) {
        return Point(x - b.x, x - b.y);
    }

    bool operator==(const Point &b) const {
        return (std::abs(x - b.x) < PRECISION && std::abs(y - b.y) < PRECISION);
    }
};

inline double norm(Point &a) {
    return std::sqrt(std::pow(a.x, 2) + std::pow(a.y, 2));
}
