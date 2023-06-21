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
    int n = 2;
    std::cout << "You need to enter data for 2 figures"
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
        std::cout << "Enter the coordinates of all the vertices for the given figure." << std::endl
                    <<"(Input supports format: 1) simultaneous input of x y)" << std::endl
                    << "2) subdivision, at first 'x' and then 'y'" << std::endl;

        for (size_t j = 0; j < num_vertices; j++) {
            double x, y;

            try {
                x = validVertices("");
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return {};
            }

            try {
                y = validVertices("");
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

    std::set<Point> uniquePoints;

    for (const Point& point : intersectPoints) {
        uniquePoints.insert(point);
    }

    for (const Point& point : uniquePoints) {
        std::cout << "Shape intersection point: (" << point.x << ", " << point.y << ")" << std::endl;
    }
}