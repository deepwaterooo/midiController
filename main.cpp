#include <QApplication>
#include <QtGui>
#include <QObject>
#include "mainwindow.h"

int top[10]; // 1 2 4 5 6; 8 9 11 12 13
int btm[15]; // 0 ~ 14
unsigned char notedata[6] = {0};
QMap<int, QString> mKeySong;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    MainWindow w;
    w.show();
    return a.exec();
}
