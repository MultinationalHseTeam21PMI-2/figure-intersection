#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>

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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createTriangles(QGraphicsScene *scene, QGraphicsView *view);
    void createPoints(QGraphicsScene *scene);
    void createAxis(QGraphicsScene *scene);

   private:
    Ui::MainWindow *ui;
};

#endif
