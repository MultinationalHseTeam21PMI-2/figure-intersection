#include "in_out.h"


std::vector<std::vector<Point>> input() {
    int n;
    std::cout << "Enter the number of shapes:";
    std::cin >> n;

    if (n <= 0) {
        std::cerr << "Error: the number of shapes must be a positive integer" << std::endl;
        return {};
    }

    std::vector<std::vector<Point>> shapes(n);
    for (size_t i = 0; i < n; i++) {
        std::cout << "Enter the number of vertices for figure " << i + 1 << ":";
        int num_vertices;
        std::cin >> num_vertices;

        if (num_vertices <= 0) {
            std::cerr << "Error: the number of vertices must be a positive integer" << std::endl;
            return {};
        }

        std::vector<Point> vertices(num_vertices);
        std::cout << "Enter the vertex coordinates" << std::endl;

        for (size_t j = 0; j < num_vertices; j++) {
            std::string input;
            double x, y;
            std::cin >> input;
            if (!input.empty()) {
                try {
                    x = std::stod(input);
                } catch (...) {
                    std::cerr << "Error: Incorrect value entered. Enter numeric value."
                    << std::endl;
                    return {};
                }
            } else {
                x = 0;
            }

            std::cin >> input;
            if (!input.empty()) {
                try {
                    y = std::stod(input);
                } catch (...) {
                    std::cerr << "Error: Incorrect value entered. Enter numeric value."
                    << std::endl;
                    return {};
                }
            }
            else {
                y = 0;
            }
            vertices[j] = Point(x, y);
        }
        shapes[i] = vertices;
    }

    return shapes;
}


void output(std::vector<Segment>& segments) {
    if (segments.empty()) {
        std::cout << "No triangle intersections found" << std::endl;
        return;
    }
    for (int i = 0; i < segments.size(); i++) {
        Point point1 = segments[i].point1();
        Point point2 = segments[i].point2();
        if (point1 == point2) {
            std::cout << "Triangle intersection point: (" << point1.x << ", " << point1.y << ")" << std::endl;
        }
        else {
            std::cout << "Triangles intersect on segment: (" << point1.x << ", " << point1.y << ") - (" << point2.x << ", " << point2.y << ")"
            << std::endl;
        }
    }
}