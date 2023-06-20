#include <QApplication>

#include "core/Algorithms/Algorithms.h"
#include "core/Segment/Segment.h"
#include "core/Triangle/Triangle.h"
#include "gui/mainwindow.h"
#include "in-out/in_out.h"

int main(int argc, char *argv[])
{
    std::vector<std::vector<Point>> trianlges_points = input();
    std::vector<Figure> triangles;
    for (auto triangle : trianlges_points) {
        triangles.push_back(Triangle{triangle[0], triangle[1], triangle[2]});
    }

    std::vector<Point> intersections;
    std::vector<Point> fig_intersections = PolygonialIntersection(triangles[0], triangles[1]);

    output(fig_intersections);

    QApplication a(argc, argv);

    MainWindow view(triangles, fig_intersections);

    view.show();

    return a.exec();
}