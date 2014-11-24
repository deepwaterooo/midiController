#include <QApplication>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <QtGui>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    /*
    // doesn't work here
    // try QGraphicsScene for QPushButton triangle
    QGraphicsScene scene(QRectF(10, 10, 100, 50));
    QGraphicsView view(&scene);
    QGraphicsRectItem *rectItem = new QGraphicsRectItem(&scene);
    rectItem->setPen(QPen(Qt::black));
    rectItem->setBrush(QBrush(Qt::green));
    rectItem->setRect(QRectF(-30,-30,120,80));
    rectItem->setFlags(QGraphicsItem::ItemIsMovable);

    QPushButton *button = new QPushButton("OK");
    QGraphicsProxyWidget *widgetItem = scene.addWidget(button);
    widgetItem->setFlags(QGraphicsItem::ItemIsMovable);

    view.show();
    */
    
    return a.exec();
}
