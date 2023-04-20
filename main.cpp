#include <iostream>
#include <vector>
#include <string>

struct Point {
    double x;
    double y;
};

std::vector<std::vector<Point>> input() {
    int n;
    std::cout << "Enter the number of shapes: ";
    std::cin >> n;

    std::vector<std::vector<Point>> shapes(n);
    for (int i = 0; i < n; i++) {
        std::cout << "Enter the number of vertices for figure " << i + 1 << ":" << std::endl;
        int num_vertices;
        std::cin >> num_vertices;

        std::vector<Point> vertices(num_vertices);
        std::cout << "Enter the vertex coordinates" << std::endl;

        for (int j = 0; j < num_vertices; j++) {
            std::string input;

            do {
                std::cin >> input;
                try {
                    vertices[j].x = input.empty() ? 0 : std::stod(input);
                    if (vertices[j].x < 0) {
                        std::cerr << "Warning: Negative value entered. Please enter a non-negative value." << std::endl;
                    }
                } catch (...) {
                    std::cerr << "Error: Incorrect value entered. Enter numeric value." << std::endl;
                    return {};
                }
            } while (vertices[j].x < 0);

            do {
                std::cin >> input;
                try {
                    vertices[j].y = input.empty() ? 0 : std::stod(input);
                    if (vertices[j].y < 0) {
                        std::cerr << "Warning: Negative value entered. Please enter a non-negative value." << std::endl;
                    }
                } catch (...) {
                    std::cerr << "Error: Incorrect value entered. Enter numeric value." << std::endl;
                    return {};
                }
            } while (vertices[j].y < 0);
        }
        shapes[i] = vertices;
    }

    return shapes;
}

int main() {
    auto shapes = input();

    return 0;
}
