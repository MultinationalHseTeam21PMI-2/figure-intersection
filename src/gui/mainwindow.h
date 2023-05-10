#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    createTriangles(QGraphicsScene *scene, QGraphicsView *view);
    createPoints(QGraphicsScene *scene);
    createAxis(QGraphicsScene *scene);
private:
    Ui::MainWindow *ui;
};

#endif