#include <QApplication>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <QtGui>
#include <QObject>

#include "mainwindow.h"
#include "dummy.h"
#include "Player.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    MainWindow w;
    w.show();

    qDebug() << "main thread: " << QThread::currentThreadId();
    QThread thread;
    Dummy dummy;
    Player player;

    //QObject::connect(thread, SIGNAL(finished()), player, SLOT(deleteLater()));
    //QObject::connect( mainThreadObj, SIGNAL(setPlayerSource (const MediaSource &)), &player, SLOT(setPlayerSource (const MediaSource &)));
    // and other signals; note that methods that are signals already can be conected witout wrappers:
    //QObject::connect( mainThreadObj, SIGNAL(playerPlay()), &player.mediaObject, SLOT(play()) );

    QObject::connect(&dummy, SIGNAL(readSig()), &player, SLOT(slot_thread()));
    player.moveToThread(&thread);
    thread.start();
    dummy.emitSig();

    return a.exec();
}
