#include "./mainwindow.h"

#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QtWidgets>


#include "../core/Figure/Figure.cpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const std::vector<Figure>& figures, const std::vector<Segment>& intersections, QWidget *parent)
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
    createFigures(scene, view, figures);
    createIntersection(scene, intersections);
    createAxis(scene);

    // Включаем режим перетаскивания
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    setCentralWidget(view);
}

void MainWindow::createFigures(QGraphicsScene *scene, QGraphicsView *view, const std::vector<Figure>& figures)
{
    // толщина линии
    qreal penWidth = 0.01;

    // Выставляем цвет линии
    QPen pen(Qt::black);

    // Устанавливаем толщину линии
    pen.setWidthF(penWidth);

    // Из-за странного определения значений на оси У(Сверху минус бесконечность, а снизу плюс бесконечность, должно быть наоборот)
    int minus = -1;

    // Создаем фигуру
    QPolygonF figure;

    // Создаем переменную масштаб осей
    qreal xyScale = 0;

    // Создаем список цветов
    QList<QColor> colors = {Qt::red, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta, Qt::gray};
    int colorIndex = 0;

    for (auto figur : figures){
        for(auto segment : figur.getSegments()){
            figure << QPointF(segment.point1().x, segment.point1().y * minus);
        }
        QGraphicsPolygonItem *figureItem = new QGraphicsPolygonItem(figure);

        // Устанавливаем толщину линии и цвет закраски для фигуры
        QBrush brush(colors[colorIndex]);
        figureItem->setPen(pen);
        figureItem->setBrush(brush);
        scene->addItem(figureItem);

        // Получаем размеры фигуры
        QRectF bounds = figureItem->boundingRect();
        qreal width = bounds.width();
        qreal height = bounds.height();

        // Рассчитываем новый масштаб осей
        qreal xScale = (view->width() / width);
        qreal yScale = (view->height() / height);
        xyScale = (xScale + yScale) / 4;

        // Настройка области просмотра
        QPointF figureCenter = figureItem->boundingRect().center();
        view->centerOn(figureCenter.x(), figureCenter.y());

        // Очищаем от старой фигуры
        figure.clear();

        // Расчитываем индекс цвета для разнообразия политры фигур
        colorIndex++;
        if (colorIndex >= colors.size()) {
            colorIndex = 0;
        }
    }

    // Устанавливаем новый масштаб осей
    view->scale(xyScale, xyScale);
}

void MainWindow::createIntersection(QGraphicsScene *scene, const std::vector<Segment>& intersections)
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
