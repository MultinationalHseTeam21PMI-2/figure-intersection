#include <QApplication>

#include "core/Algorithms/Algorithms.h"
#include "core/Segment/Segment.h"
#include "core/Triangle/Triangle.h"
#include "core/ConvexFigure/ConvexFigure.h"

#include "gui/mainwindow.h"
#include "in-out/in_out.h"

int main(int argc, char *argv[])
{
    std::vector<std::vector<Point>> figures_points = input();
    std::vector<Figure> figures;
    for (auto figure_points : figures_points) {
        if (figure_points.size() == 3) {
            figures.push_back(Triangle{figure_points[0], figure_points[1], figure_points[2]});
        } else {
            figures.push_back(ConvexFigure(figure_points));
        }
    }

    std::vector<Point> intersections;
    std::vector<Point> fig_intersections = PolygonialIntersection(figures[0], figures[1]);


    output(fig_intersections);

    QApplication a(argc, argv);

    MainWindow view(figures, fig_intersections);

    view.show();

    return a.exec();
}