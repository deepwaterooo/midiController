#ifndef READBUFFTHREAD_H
#define READBUFFTHREAD_H

#include <QSound>
#include <QString>
#include <QThread>
#include <QMutex>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>
#include "db.h"

#define MIDI_DEVICE "/dev/snd/midiC1D0"

class Dummy : public QObject {
    Q_OBJECT
 public:
    Dummy() {
        buff = new dArr(data, 6);
        lit = false;
    }

    void set(dArr *src) {
        if (this->buff != src)
            *(this->buff) = *src;
    }
    
 public:
    unsigned char data[6] = {0};
    unsigned char prev[3] = {0};    
    dArr *buff;
    bool lit;
    
    public slots:
        void emitSig () {
            qDebug() << " from Dummy: " << QThread::currentThreadId();
            int fd;          
            char* device = (char*)("/dev/snd/midiC1D0");
            int cnt = 0;
            while (cnt < 2) {
                fd = open(device, O_RDWR, 0);   // try to make this file descriptor global so that it will be accessible from both reading & writing threads;
                // in the middle, QMutex for atomic section control to protect data
                
                if (fd == -1) {
                    qDebug("Error: cannot open \n");
                    exit(1);
                }
                int bytes_read = read(fd, &data, sizeof(data));
                while (bytes_read < 0) {
                    qDebug("Error reading %s\n", MIDI_DEVICE);
                    bytes_read = read(fd, &data, sizeof(data));
                }
                qDebug("Dummy inside: \n");
                for (int i = 0; i < 6; ++i)
                    qDebug() << "data[" << i << "]: " << data[i];
                buff->set(data, 6);

                // tested this part using qt 5.3 version just read/write from/to midi LED on/off is not as responsive as expected, need more work here
                // write LED on made it way too slow~~
                for (int i = 0; i < 3; ++i) {
                    if (data[i] != prev[i]) {
                        prev[i] = data[i];
                        lit = true;
                    }
                }
                if (lit) {
                    prev[0] = 0x90;
                    prev[2] = 127;
                    write(fd, prev, sizeof(prev));
                    lit = false;
                }

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
