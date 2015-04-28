#ifndef READFROMMIDITHREAD_H
#define READFROMMIDITHREAD_H

#include <QSound>
#include <QString>
#include <QThread>
#include <QMutex>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>

extern char* device;
extern int fd;
extern unsigned char notedata[6];

class ReadFromMidiThread : public QObject {
    Q_OBJECT
 public:
    ReadFromMidiThread() {}
    ~ReadFromMidiThread() {}
 public:
    public slots:
     void emitSig ();
 signals:
    void readSig();
};

#endif
