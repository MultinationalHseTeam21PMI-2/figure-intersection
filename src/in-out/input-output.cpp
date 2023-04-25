#include <iostream>
#include <string>
#include <vector>
#include "../core/Segment/Segment.h"

typedef std::pair<double, double> Point;

std::vector<std::vector<Point>> input() {
    int n;
    std::cout << "Enter the number of shapes:";
    std::cin >> n;

    std::vector<std::vector<Point>> shapes(n);
    for (int i = 0; i < n; i++) {
        std::cout << "Enter the number of vertices for figure " << i + 1 << ":";
        int num_vertices;
        std::cin >> num_vertices;

        std::vector<Point> vertices(num_vertices);
        std::cout << "Enter the vertex coordinates" << std::endl;

        for (int j = 0; j < num_vertices; j++) {
            std::string input;
                std::cin >> input;
                try {
                    vertices[j].first = input.empty() ? 0 : std::stod(input);
                } catch (...) {
                    std::cerr << "Error: Incorrect value entered. Enter numeric value."
                              << std::endl;
                    return {};
                }

                std::cin >> input;
                try {
                    vertices[j].second = input.empty() ? 0 : std::stod(input);
                } catch (...) {
                    std::cerr << "Error: Incorrect value entered. Enter numeric value."
                              << std::endl;
                    return {};
                }
        }
        shapes[i] = vertices;
    }

    return shapes;
}


void output(std::vector<Segment>& segments) {
    for (int i = 0; i < segments.size(); i++) {
        Point point1 = segments[i].point1();
        Point point2 = segments[i].point2();
        if (point1 == point2) {
            std::cout << "Triangle intersection point: (" << point1.first << ", " << point1.second << ")" << std::endl;
        }
        else {
            std::cout << "Triangles intersect on segment: (" << point1.first << ", " << point1.second << ") - (" << point2.first << ", " << point2.second << ")" << std::endl;
        }
    }
}
