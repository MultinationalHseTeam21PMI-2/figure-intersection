#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QWheelEvent>
#include <iostream>


#include "../core/Triangle/Triangle.h"

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
    MainWindow(const std::vector<Figure>&, const std::vector<Point>&, QWidget *parent = nullptr);
    ~MainWindow() override;
    void createFigures(QGraphicsScene *scene, QGraphicsView *view, const std::vector<Figure>&);
    void createIntersection(QGraphicsScene *scene, const std::vector<Point>&);
    void createAxis(QGraphicsScene *scene);

   private:
    Ui::MainWindow *ui;
    std::vector<Figure> m_triangles;
    std::vector<Point> m_intersections;
    QGraphicsView *view;
    QGraphicsScene *scene;
};

#endif
