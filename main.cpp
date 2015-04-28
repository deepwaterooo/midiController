#include <QApplication>
#include <QtGui>
#include <QObject>

#include "mainwindow.h"
#include "readFromMidiThread.h"
#include "writeToMidiThread.h"

#include "Player.h"

// global data

char* device = (char*)("/dev/snd/midiC1D0");
int fd = open(device, O_RDWR, 0);    // what if read fail, error handling debugging system?
unsigned char notedata[6] = {0};

int top[10]; // 1 2 4 5 6; 8 9 11 12 13
int btm[15]; // 0 ~ 14

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    MainWindow w;
    w.show();

    qDebug() << "main thread: " << QThread::currentThreadId();
    QThread thread;

    ReadFromMidiThread readthread;
    //WriteToMidiThread writethread;
    // QMutex, QReadWriteLock ? think about it
    
    Player player;

    QObject::connect(&readthread, SIGNAL(readSig()), &player, SLOT(slot_thread()));
    player.moveToThread(&thread);
    thread.start();

    readthread.emitSig();

    close(fd); // could this implements open() & close() once ?
    return a.exec();
}
