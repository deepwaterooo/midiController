#include <QApplication>
#include <QtGui>
#include <QObject>
#include <linux/soundcard.h>
#include "mainwindow.h"
#include "thread.h"

int top[10]; // 1 2 4 5 6; 8 9 11 12 13
int btm[15]; // 0 ~ 14
//unsigned char notedata[6] = {SEQ_MIDIPUTC, 0, 0, 0, 0, 0};
QMap<int, QString> mKeySong;
Thread *yy;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    MainWindow w;
    w.show();

    // yy
    // player

    qDebug() << "main thread: " << QThread::currentThreadId();
    QThread thread;

    yy = new Thread;
    Player player;

    QObject::connect(yy, SIGNAL(readUpdate()), &player, SLOT(readFromDevice()));
    player.moveToThread(&thread);
    thread.start();
    
    return a.exec();
}
