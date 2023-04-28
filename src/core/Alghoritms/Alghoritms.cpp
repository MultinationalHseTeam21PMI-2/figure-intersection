#include <iostream>
#include "Alghoritms.h"

bool are_equal(double a, double b, double precision = PRECISION);

bool lexicographical_comparator(std::pair<Point, bool> a, std::pair<Point, bool> b);

std::string determinate_pattern(const std::vector<std::pair<Point, bool>>& marked_points);

bool are_intersect(const std::string& intersection_pattern);

bool is_between(double a, double b, double mid, double precision = PRECISION);

bool is_point_between(const Point& a, const Point& b, const Point& mid, double precision = PRECISION);

bool is_belong_to_segment(const Point& point, const Segment& segment, double precision = PRECISION);

Point solve_linear_system(const Segment& a, const Segment& b);

double distance_to_origin(const Segment& a);

std::unique_ptr<Segment> intersection(const Segment &a, const Segment &b) {
    if (are_equal(a.get_slope(),b.get_slope()) && are_equal(distance_to_origin(a),distance_to_origin(b))) {

        // Если точка принадлежит первому отрезку, то помечаем значением false, иначе - true.
        std::vector<std::pair<Point, bool>> sorted_segment_points{{a.point1(), false}, {a.point2(), false},
                                                                  {b.point1(), true}, {b.point2(), true}};

        // Сортируем по точкам отрезков, причём точки сравниваются лексикографически.
        //      Это необходимо, чтобы однозначно определить порядок точек на общей прямой отрезков
        sort(sorted_segment_points.begin(), sorted_segment_points.end(), lexicographical_comparator);

        // Для наглядности используется строка, характеризующая взаиморасположение отрезков на одной прямой:
        //  1. Отмечаем точки, принадлежащие первому отрезку 'X', а второму - 'Y'.
        //  2. Если отрезки не пересекаются, то строка будет равна "XXYY" или "YYXX" с точностью до порядка аргументов функции.
        //  3. Иначе пересечением будет являться отрезок из двух внутренних точек на общей прямой
        //      Например, все случаи пересечения исчерпываются следующими ситуациями с точностью до переобозначения:
        //          конфигурация "YXXY" - случай, когда первый отрезок вложен во второй;
        //          конфигурация "XYXY - случай, когда первый и второй отрезок имеют общую линейную часть;
        //      В обоих конфигурация серединные точки выступают в качестве отрезка, совпадающего с пересечением.
        if(are_intersect(determinate_pattern(sorted_segment_points))) {
            return std::make_unique<Segment>(sorted_segment_points.at(1).first, sorted_segment_points.at(2).first);
        }
        return nullptr;
    }

    Point result = solve_linear_system(a, b);
    if(is_belong_to_segment(result, a) && is_belong_to_segment(result, b)) {
        return std::make_unique<Segment>(result, result);
    }
    return nullptr;
}

bool is_subset(const Segment& subset, const Segment& set) {
    return is_belong_to_segment(subset.point1(), set) && is_belong_to_segment(subset.point2(), set);
}

std::vector<Segment> intersection(const Figure &figure1, const Figure &figure2){
    auto union_of_intersections = new std::vector<Segment>;
    for(auto seg_a : figure1.getSegments()) {
        for(auto seg_b : figure2.getSegments()) {
            if(intersection(seg_a,seg_b) != nullptr) {
                bool unique_addition = true;
                for(auto added_segments : *union_of_intersections){
                    if(is_subset(*intersection(seg_a,seg_b),added_segments)) {
                        unique_addition = false;
                        break;
                    }
                }
                if(unique_addition) {
                    union_of_intersections->push_back(*intersection(seg_a,seg_b));
                }
            }
        }
    }

    return *union_of_intersections;
}

bool are_equal(double a, double b, double precision) {
    if(std::abs(a) < precision/2.0f && std::abs(b) < precision/2.0f) return std::signbit(a) == std::signbit(b);
    return std::abs(a - b) < precision;
}
bool lexicographical_comparator(std::pair<Point, bool> a, std::pair<Point, bool> b) {
    if (are_equal(a.first.x, b.first.x)) {
        return a.first.y < b.first.y;
    }
    return a.first.x < b.first.x;
}
std::string determinate_pattern(const std::vector<std::pair<Point, bool>>& marked_points) {
    std::string intersection_pattern{};
    for (auto x : marked_points) {
        intersection_pattern.push_back(x.second ? 'Y' : 'X');
    }
    return intersection_pattern;
}
bool are_intersect(const std::string& intersection_pattern) {
    if (intersection_pattern == "XXYY" || intersection_pattern == "YYXX") {
        return false;
    }
    return true;
}
bool is_between(double a, double b, double mid, double precision) {
    return std::min(a,b) <= mid + precision &&  mid <= std::max(a, b) + precision;
}
bool is_point_between(const Point& a, const Point& b, const Point& mid, double precision) {
    if( is_between(a.x, b.x, mid.x, precision) && is_between(a.y, b.y, mid.y, precision) ) {
        return true;
    }
    return false;
}
Point solve_linear_system(const Segment& a, const Segment& b) {
    // Вычисляем коэффициенты уравнений Ax + By + C = 0 прямых, на которых лежат отрезки
    const double A1 = a.point2().y - a.point1().y, A2 = b.point2().y - b.point1().y;
    const double B1 = a.point1().x - a.point2().x, B2 = b.point1().x - b.point2().x;
    const double C1 = a.point1().y * a.point2().x - a.point1().x * a.point2().y,
            C2 = b.point1().y * b.point2().x - b.point1().x * b.point2().y;

    // Решаем линейную систему, составленную из найденных коэффициентов, методом Крамера,
    // что имеет смысл в силу того, что детерминант матрицы коэффициентов 'далёк' от 0 с заданной точностью.
    const double RESULT_X = -(C1 * B2 - C2 * B1) / (A1 * B2 - A2 * B1);
    const double RESULT_Y = -(A1 * C2 - A2 * C1) / (A1 * B2 - A2 * B1);

    return Point(RESULT_X, RESULT_Y);
}
bool is_belong_to_segment(const Point& point, const Segment& segment, double precision) {
    return is_point_between(segment.point1(), segment.point2(), point, precision);
}
double distance_to_origin(const Segment& a) {
    const double A = a.point2().y - a.point1().y,
            B = a.point1().x - a.point2().x,
            C = a.point1().y * a.point2().x - a.point1().x * a.point2().y;

    return (C)/std::sqrt(std::pow(A,2) + std::pow(B,2));
}