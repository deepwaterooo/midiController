#ifndef WRITETOMIDITHREAD_H
#define WRITETOMIDITHREAD_H

#include <QSound>
#include <QString>
#include <QThread>
#include <QMutex>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>
#include "writeToMidiThread.h"

extern char* device;
extern int fd;
extern unsigned char notedata[6];

class WriteToMidiThread : public QObject {
    Q_OBJECT
 public:
    WriteToMidiThread() {
    }
 public:
    public slots:
        void emitSig () {
            qDebug() << " from WritetoMidiThread: " << QThread::currentThreadId();
            int cnt = 0;
            while (cnt < 2) {
                fd = open(device, O_RDWR, 0);   // try to make this file descriptor global so that it will be accessible from both reading & writing threads;
                if (fd == -1) {
                    qDebug("Error: cannot open \n");
                    exit(1);
                }
                int bytes_read = read(fd, &notedata, sizeof(notedata));
                while (bytes_read < 0) {
                    qDebug("Error reading %s\n", device);
                    bytes_read = read(fd, &notedata, sizeof(notedata));
                }
                qDebug("WritetoMidiThread inside: \n");
                for (int i = 0; i < 6; ++i)
                    qDebug() << "notedata[" << i << "]: " << notedata[i];

                // tested this part using qt 5.3 version just read/write from/to midi LED on/off is not as responsive as expected, need more work here
                // write LED on made it way too slow~~
     /*
                for (int i = 0; i < 3; ++i) {
                    if (notedata[i] != prev[i]) {
                        //prev[i] = notedata[i];
                        //lit = true;
                    }
                }
           
                if (lit) {
                    prev[0] = 0x90;
                    prev[2] = 127;
                    write(fd, prev, sizeof(prev));
                    lit = false;
                }
                */
                emit readSig();
                close(fd);      // open & close only once
                sleep(5);
                cnt++;
            } // while
        }

 signals:
    void readSig();
};

#endif
