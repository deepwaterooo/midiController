#include <QApplication>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <QtGui>

#include "mainwindow.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    MainWindow w;
    w.show();
    return a.exec();
}
