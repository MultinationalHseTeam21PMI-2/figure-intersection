#include "./mainwindow.h"

#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QtWidgets>

#include "ui_mainwindow.h"

MainWindow::MainWindow(std::vector<Triangle>& figures, const std::vector<Segment>& intersections, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_triangles(figures), m_intersections(intersections)
{
    ui->setupUi(this);
    // Создаем графическую сцену и устанавливаем ее в QGraphicsView
    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(this);
    view->setScene(scene);

    // Устанавливаем размеры QGraphicsView и сцены
    view->setFixedSize(800, 800);

    // // Вызываем функции
    createTriangles(scene, view, figures);
    createPoints(scene, intersections);
    createAxis(scene);

    // Включаем режим перетаскивания
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    setCentralWidget(view);
}

void MainWindow::createTriangles(QGraphicsScene *scene, QGraphicsView *view,  std::vector<Triangle>& figures)
{

    for (int i = 0; i < figures.size(); i++){
        for(int j = 0; j < figures[i].getSegments().size(); j++){
            //std::cout << figures[i].getSegments()[j].point1().x <<", "<< figures[i].getSegments()[j].point1().y;
            }
    }

    //std::cout << figures[0].getSegments().size();
    // Устанавливаем цвет чернил на черный
    QPen pen(Qt::black);

    // Вычисляем толщину линии на основе размера фигуры
    qreal penWidth = 0.01;

    // Устанавливаем толщину линии
    pen.setWidthF(penWidth);

    // Устанавливаем цвет заливки на красный
    QBrush brush1(Qt::red);
    QBrush brush2(Qt::blue);

    // Из-за странного определения значений на оси У(Сверху минус бесконечность, а снизу плюс бесконечность, должно быть наоборот)
    int minus = -1;

    std::vector<QPointF> pointsVector;
    /*
        for (auto Figure : Figures_for_drawing){
            for(auto segment : Figure.getSegments()){
                QPointF point(segment.point1.x, segment.point1.y * minus);
                pointsVector.push_back(point);
            }
        }
    */
    // Создаем первый треугольник
    QPolygonF triangle1;
    triangle1 << QPointF(-5, 6 * minus) << QPointF(-6.09, 3.8 * minus) << QPointF(-2.57, 3.76 * minus);
    QGraphicsPolygonItem *triangle1Item = new QGraphicsPolygonItem(triangle1);

    // Создаем второй треугольник
    QPolygonF triangle2;
    triangle2 << QPointF(-4.49, 4.68 * minus) << QPointF(-2.21, 6.7 * minus) << QPointF(-1.05, 5.16 * minus);
    QGraphicsPolygonItem *triangle2Item = new QGraphicsPolygonItem(triangle2);

    // Получаем размеры фигуры
    QRectF bounds = triangle1Item->boundingRect().united(triangle2Item->boundingRect());
    qreal width = bounds.width();
    qreal height = bounds.height();

    // Рассчитываем новый масштаб осей
    qreal xScale = (view->width() / width);
    qreal yScale = (view->height() / height);
    qreal xyScale = (xScale + yScale) / 2 - 75;

    // Устанавливаем новый масштаб осей
    view->scale(xyScale, xyScale);

    // настройка области просмотра
    QPointF triangleCenter = triangle1Item->boundingRect().center();
    view->centerOn(triangleCenter.x(), triangleCenter.y());

    // Устанавливаем толщину линии и цвет закраски для первого треугольника
    triangle1Item->setPen(pen);
    triangle1Item->setBrush(brush1);
    scene->addItem(triangle1Item);

    // Устанавливаем толщину линии и цвет закраски для второго треугольника
    triangle2Item->setPen(pen);
    triangle2Item->setBrush(brush2);
    scene->addItem(triangle2Item);
}

void MainWindow::createPoints(QGraphicsScene *scene, const std::vector<Segment>& intersections)
{
    // Из-за странного определения значений на оси У(Сверху минус бесконечность, а снизу плюс бесконечность, должно быть наоборот)
    int minus = -1;

    for (int i = 0; i < intersections.size(); i++) {
        QPointF point1(intersections[i].point1().x, intersections[i].point1().y * minus);
        QPointF point2(intersections[i].point2().x, intersections[i].point2().y * minus);
        if (point1 == point2) {
            // Одна точка
            QGraphicsEllipseItem *pointItem = new QGraphicsEllipseItem(point1.x() - 0.125, point1.y() - 0.125, 0.25, 0.25);
            pointItem->setPen(Qt::NoPen);
            pointItem->setBrush(Qt::green);
            scene->addItem(pointItem);
        }
        else {
            // Сегмент
            QGraphicsLineItem *lineItem = new QGraphicsLineItem(point1.x(), point1.y(), point2.x(), point2.y());
            lineItem->setPen(QPen(Qt::green, 0.1));
            scene->addItem(lineItem);
        }
    }

    /*
    for (int i = 0; i < 3; i++) {
        // Создаем точки пересечения
        QPointF point1(0 + i, (4 + i) * minus);
        QPointF point2(0 + i, (4 + i) * minus);

        if (point1 == point2) {
            // Одна точка
            QGraphicsEllipseItem *pointItem = new QGraphicsEllipseItem(point1.x() - 0.125, point1.y() - 0.125, 0.25, 0.25);
            pointItem->setPen(Qt::NoPen);
            pointItem->setBrush(Qt::green);
            scene->addItem(pointItem);
        } else {
            // Сегмент
            QGraphicsLineItem *lineItem = new QGraphicsLineItem(point1.x(), point1.y(), point2.x(), point2.y());
            lineItem->setPen(QPen(Qt::green, 0.1));
            scene->addItem(lineItem);
        }
    }
     */
}

void MainWindow::createAxis(QGraphicsScene *scene)
{
    // Устанавливаем цвет чернил на черный
    QPen pen(Qt::black);

    // Вычисляем толщину линии на основе размера фигуры
    qreal penWidth = 0.01;

    // Устанавливаем толщину линии
    pen.setWidthF(penWidth);

    // Рисуем оси координат
    QGraphicsLineItem *xAxis = scene->addLine(-100, 0, 100, 0, pen);  // Ось X
    QGraphicsLineItem *yAxis = scene->addLine(0, -100, 0, 100, pen);  // Ось Y

    // Создаем толщину шрифта
    QFont font;
    font.setPointSize(1);

    int minus = -1;
    // Добавляем разметку на осях с шагом в 4 значения
    for (int i = -100; i <= 100; i += 4) {
        if (i != 0) {
            QGraphicsLineItem *tick = scene->addLine(i, -1, i, 1, pen);           // Разметка на оси X
            QGraphicsTextItem *label = scene->addText(QString::number(i), font);  // Надпись на оси X
            label->setPos(i - label->boundingRect().width() / 1.91, -3.1);
        }
        if (i != 0) {
            QGraphicsLineItem *tick = scene->addLine(-1, i, 1, i, pen);                   // Разметка на оси Y
            QGraphicsTextItem *label = scene->addText(QString::number(i * minus), font);  // Надпись на оси Y
            label->setPos(3 - label->boundingRect().width(), i - label->boundingRect().height() / 2.1);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw(const std::vector<Figure> figures, const std::vector<Segment> intersections)
{

}