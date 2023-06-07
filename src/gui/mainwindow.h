#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <iostream>
#include "../core/Figure/Figure.h"
#include "../core/Segment/Segment.h"
#include "../core/Triangle/Triangle.h"
#include "../core/Point/Point.h"
#include "../core/Algorithms/Algorithms.h"
QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

   public:
    MainWindow(std::vector<Triangle>&, const std::vector<Segment>&, QWidget *parent = nullptr);
    ~MainWindow();
    void createTriangles(QGraphicsScene *scene, QGraphicsView *view, std::vector<Triangle>&);
    void createPoints(QGraphicsScene *scene, const std::vector<Segment>&);
    void createAxis(QGraphicsScene *scene);

    void draw(const std::vector<Figure>, const std::vector<Segment>);

   private:
    Ui::MainWindow *ui;
    std::vector<Triangle> m_triangles;
    std::vector<Segment> m_intersections;
};

#endif
