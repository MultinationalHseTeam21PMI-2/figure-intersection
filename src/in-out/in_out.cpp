#include "in_out.h"


double validVertices(const std::string& prom) {
    std::string input;
    std::cout << prom;
    std::cin >> input;

    if (!input.empty()) {
        size_t pos;
        try {
            double vertex = std::stod(input, &pos);
            if (pos < input.size()) {
                throw std::invalid_argument("Non-numeric value entered.");
            }
            return vertex;
        } catch (...) {
            throw std::invalid_argument("Non-numeric value entered.");
        }
    } else {
        return 0.0;
    }
}



int validNumber(const std::string& prom) {
    int number;
    std::string input;
    std::cout << prom;
    std::cin >> input;

    try {
        number = std::stoi(input);
        if (number <= 0) {
            throw std::invalid_argument("The number must be positive integer.");
        }
    } catch (...) {
        throw std::invalid_argument("Incorrect value entered. Enter a numeric value.");
    }

    return number;
}


std::vector<std::vector<Point>> input() {
    int n;
    std::cout << "Enter the number of shapes:";

    try {
        n = validNumber("");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return {};
    }

    std::vector<std::vector<Point>> shapes(n);
    for (size_t i = 0; i < n; i++) {
        std::cout << "Enter the number of vertices for figure " << i + 1 << ":";
        int num_vertices;

        try {
            num_vertices = validNumber("");
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return {};
        }

        std::vector<Point> vertices(num_vertices);
        std::cout << "Enter the vertex coordinates" << std::endl;

        for (size_t j = 0; j < num_vertices; j++) {
            double x, y;

            try {
                x = validVertices("Enter the x-coordinate: ");
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return {};
            }

            try {
                y = validVertices("Enter the y-coordinate: ");
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return {};
            }

            vertices[j] = Point(x, y);
        }
        shapes[i] = vertices;
    }

    return shapes;
}


void output(std::vector<Point>& intersectPoints) {
    if (intersectPoints.empty()) {
        std::cout << "No shape intersections found" << std::endl;
        return;
    }
    for (int i = 0; i < intersectPoints.size(); i++) {
        Point point1 = intersectPoints[i];
        std::cout << "Shape intersection point: (" << point1.x << ", " << point1.y << ")" << std::endl;
    }
}