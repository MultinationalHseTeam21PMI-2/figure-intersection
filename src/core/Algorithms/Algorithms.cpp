#include "Algorithms.h"

bool are_equal(const double& a, const double& b, const double& precision = PRECISION) noexcept;

bool lexicographical_comparator(std::pair<Point, bool> a, std::pair<Point, bool> b) noexcept;

std::string determinate_pattern(const std::vector<std::pair<Point, bool>> &marked_points) noexcept;

bool are_intersect(const std::string &intersection_pattern) noexcept;

bool is_between(double a, double b, double mid, double precision = PRECISION) noexcept;

bool is_point_between(const Point &a, const Point &b, const Point &mid, double precision = PRECISION) noexcept;

bool is_belong_to_segment(const Point &point, const Segment &segment, double precision = PRECISION) noexcept;

bool is_segments_on_same_line(const Segment &a, const Segment &b, double precision = PRECISION) noexcept;

double f_line(const Segment &a, const Point &arg) noexcept;


Point solve_linear_system(const Segment &a, const Segment &b);

std::unique_ptr<Segment> intersection(const Segment &a, const Segment &b) {
    if (are_equal(a.get_slope(), b.get_slope())) {
        if (!is_segments_on_same_line(a, b)) return nullptr;

        // Если точка принадлежит первому отрезку, то помечаем значением false, иначе - true.
        std::vector<std::pair<Point, bool>> sorted_segment_points
        {{a.point1(), false}, {a.point2(), false}, {b.point1(), true}, {b.point2(), true}};

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
        if (are_intersect(determinate_pattern(sorted_segment_points))) {
            return std::make_unique<Segment>(sorted_segment_points.at(1).first, sorted_segment_points.at(2).first);
        }
        return nullptr;
    }

    Point result = solve_linear_system(a, b);
    if (is_belong_to_segment(result, a) && is_belong_to_segment(result, b)) {
        return std::make_unique<Segment>(result, result);
    }
    return nullptr;
}

bool is_subset(const Segment &subset, const Segment &set) {
    return is_belong_to_segment(subset.point1(), set) && is_belong_to_segment(subset.point2(), set);
}
std::vector<Segment> intersection(const Figure &figure1, const Figure &figure2) {
    std::vector<Segment> union_of_intersections;
    for (auto seg_a: figure1.getSegments()) {
        for (auto seg_b: figure2.getSegments()) {

            std::unique_ptr<Segment> seg_intersection = intersection(seg_a, seg_b);

            if (seg_intersection == nullptr) {
                continue;
            }

            bool unique_addition = true;
            for (auto added_segments: union_of_intersections) {
                if (is_subset(*seg_intersection, added_segments)) {
                    unique_addition = false;
                    //print_seg(*seg_intersection, added_segments);
                    break;
                }
            }

            if (unique_addition) {
                union_of_intersections.push_back(*seg_intersection);
            }
        }
    }
    return union_of_intersections;
}

bool are_equal(const double& a, const double& b, const double& precision) noexcept {
    if (std::abs(a) < precision / 2.0f && std::abs(b) < precision / 2.0f) return std::signbit(a) == std::signbit(b);
    return std::abs(a - b) < precision;
}

bool lexicographical_comparator(std::pair<Point, bool> a, std::pair<Point, bool> b) noexcept {
    if (are_equal(a.first.x, b.first.x)) {
        return a.first.y < b.first.y;
    }
    return a.first.x < b.first.x;
}
std::string determinate_pattern(const std::vector<std::pair<Point, bool>> &marked_points) noexcept {
    std::string intersection_pattern{};
    for (auto x: marked_points) {
        intersection_pattern.push_back(x.second ? 'Y' : 'X');
    }
    return intersection_pattern;
}
bool are_intersect(const std::string &intersection_pattern) noexcept {
    if (intersection_pattern == "XXYY" || intersection_pattern == "YYXX") {
        return false;
    }
    return true;
}
bool is_between(double a, double b, double mid, double precision) noexcept {
    return std::min(a, b) <= mid + precision && mid <= std::max(a, b) + precision;
}
bool is_point_between(const Point &a, const Point &b, const Point &mid, double precision) noexcept{
    if (is_between(a.x, b.x, mid.x, precision) && is_between(a.y, b.y, mid.y, precision)) {
        return true;
    }
    return false;
}
Point solve_linear_system(const Segment &a, const Segment &b) {
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
bool is_belong_to_segment(const Point &point, const Segment &segment, double precision) noexcept {
    return is_point_between(segment.point1(), segment.point2(), point, precision) &&
            (std::abs(f_line(segment, point)) < precision);
}
double f_line(const Segment &a, const Point &arg) noexcept {
    const double A = a.point2().y - a.point1().y,
                 B = a.point1().x - a.point2().x,
                 C = a.point1().y * a.point2().x - a.point1().x * a.point2().y;
    return A * arg.x + B * arg.y + C;
}
bool is_segments_on_same_line(const Segment &a, const Segment &b, double precision) noexcept {
    return std::abs(f_line(b, a.point1())) < precision;
}

bool containsPoints(const std::vector<Point>& points, const Point& point) {
    return (std::find(points.begin(), points.end(), point) != points.end());
}

bool isVertexInsidePolygon(const Figure& polygon, const Point& point) {
    const std::vector<Segment>& segments = polygon.getSegments();
    int count = 0;

    for (const Segment& segment : segments) {
        const Point& point1 = segment.point1();
        const Point& point2 = segment.point2();

        if ((point1.y <= point.y && point2.y > point.y) || (point2.y <= point.y && point1.y > point.y)) {
            double x = (point.y - point1.y) * (point2.x - point1.x) / (point2.y - point1.y) + point1.x;

            if (x > point.x) {
                count++;
            }
        }
    }

    return (count % 2 == 1);
}

std::vector<Point> findInternalVertices(const Figure& polygon1, const Figure& polygon2) {
    std::vector<Point> internalVertices;
    for (const auto& segment : polygon1.getSegments()) {
        if (isVertexInsidePolygon(polygon2, segment.point1()) && !(containsPoints(internalVertices, segment.point1()))) {
            internalVertices.push_back(segment.point1());
        }
        if (isVertexInsidePolygon(polygon2, segment.point1()) && !(containsPoints(internalVertices, segment.point1()))) {
            internalVertices.push_back(segment.point2());
        }
    }

    for (const auto& segment : polygon2.getSegments()) {
        if (isVertexInsidePolygon(polygon1, segment.point1()) && !(containsPoints(internalVertices, segment.point1()))) {
            internalVertices.push_back(segment.point1());
        }
        if (isVertexInsidePolygon(polygon1, segment.point1()) && !(containsPoints(internalVertices, segment.point1()))) {
            internalVertices.push_back(segment.point2());
        }
    }

    return internalVertices;
}


int orientation(const Point& a, const Point& b, const Point& c, double precision = PRECISION) noexcept {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < -precision) return -1;
    if (v > precision) return +1;
    return 0;
}

bool clockwise(Point a, Point b, Point c, bool include_collinear) {
    auto o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool are_col(Point a, Point b, Point c) { return orientation(a, b, c) == 0; }

void getConvexHull(std::vector<Point>& simplex, bool include_collinear) {

    auto p0 = *min_element(simplex.begin(), simplex.end(), [](Point a, Point b) {
        return std::make_pair(a.y, a.x) < std::make_pair(b.y, b.x);
    });

    sort(simplex.begin(), simplex.end(), [&p0](const Point& a, const Point& b) {
        auto o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });

    int simplex_back = (int)simplex.size() - 1;
    if (include_collinear) {
        auto i = simplex_back;
        while (i >= 0 && are_col(p0, simplex[i], simplex.back())) --i;
        reverse(simplex.begin()+i+1, simplex.end());
    }

    std::vector<Point> simplex_stack;

    for (auto i = 0; i < simplex.size(); ++i) {
        while (simplex_stack.size() > 1 && !clockwise(simplex_stack[simplex_stack.size()-2], simplex_stack.back(),
                                                      simplex[i], include_collinear)) {
            simplex_stack.pop_back();
        }
        simplex_stack.push_back(simplex[i]);
    }
    simplex = simplex_stack;
}
std::vector<Point> PolygonialIntersection(const Figure& a, const Figure& b) {
    std::vector<Segment> edge_intersection_v = intersection(a, b);
    std::vector<Point> inner_intersection_v = findInternalVertices(a, b);
    std::vector<Point> v_to_convexhull(inner_intersection_v);
    for(auto seg : edge_intersection_v) {
        if(std::find(v_to_convexhull.begin(), v_to_convexhull.end(), seg.point1()) == v_to_convexhull.end())
            v_to_convexhull.push_back(seg.point1());
        if(!seg.isPoint() &&
        std::find(v_to_convexhull.begin(), v_to_convexhull.end(), seg.point2()) == v_to_convexhull.end())
            v_to_convexhull.push_back(seg.point2());
    }
    if (v_to_convexhull.empty())
        return std::vector<Point> ();
    getConvexHull(v_to_convexhull, true);

    return v_to_convexhull;
}
