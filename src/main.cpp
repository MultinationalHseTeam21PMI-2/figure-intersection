#include "core/Algorithms/Algorithms.h"
#include "core/Segment/Segment.h"
#include "core/Triangle/Triangle.h"
#include "in-out/in_out.h"

int main() {

    std::vector<std::vector<Point>> trianlges_points = input();
    std::vector<Triangle> triangles;
    for (auto triangle: trianlges_points) {
        triangles.push_back(Triangle{triangle[0], triangle[1], triangle[2]});
    }
    std::vector<Segment> intersections;

    std::vector<Segment> fig_intersections = intersection(triangles[0], triangles[1]);
    intersections.insert(std::end(intersections), std::begin(fig_intersections), std::end(fig_intersections));

    output(intersections);


    return 0;
}