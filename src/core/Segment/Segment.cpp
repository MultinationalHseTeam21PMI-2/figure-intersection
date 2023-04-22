
#include "Segment.h"

std::unique_ptr<Segment> Segment::intersection(const Segment &a, const Segment &b) {
    if (std::abs(a.get_slope() - b.get_slope()) < PRECISION) {
        std::vector<std::pair<Point, bool>> line_for_sort{{a.point1(), 0}, {a.point2(), 0}, {b.point1(), 1}, {b.point2(), 1}};

        sort(line_for_sort.begin(), line_for_sort.end(), [](std::pair<Point, bool> a, std::pair<Point, bool> b) {
            if (std::abs(a.first.x - b.first.x) < PRECISION)
                return a.first.y < b.first.y;
            return a.first.x < b.first.x;
        });

        /*for(auto check : line_for_sort) {
            std::cout << "!" << check.first.y << '\n';
        }*/

        std::string pattern{};
        for (auto x: line_for_sort) {
            if (x.second)
                pattern.push_back('Y');
            else
                pattern.push_back('X');
        }

        /*std::cout << line_for_sort[1].first.y << " " << line_for_sort[2].first.y << '\n';*/

        if (pattern == "XXYY" || pattern == "YYXX")
            return nullptr;
        return std::make_unique<Segment>(line_for_sort[1].first, line_for_sort[2].first);
    }
    //Находим уравнения прямых
    double A1 = a.point2().y - a.point1().y, A2 = b.point2().y - b.point1().y;
    double B1 = a.point1().x - a.point2().x, B2 = b.point1().x - b.point2().x;
    double C1 = a.point1().y * a.point2().x - a.point1().x * a.point2().y, C2 = b.point1().y * b.point2().x - b.point1().x * b.point2().y;

    //Координаты точки пересечения
    double RESULT_X = -(C1 * B2 - C2 * B1) / (A1 * B2 - A2 * B1);
    double RESULT_Y = -(A1 * C2 - A2 * C1) / (A1 * B2 - A2 * B1);

    Point Result(RESULT_X, RESULT_Y);

    return std::make_unique<Segment>(Result, Result);
}
