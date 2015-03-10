#ifndef WRITEBUFFTHREAD_H
#define WRITEBUFFHREAD_H

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

class WriteBuffThread : public QThread {
    Q_OBJECT
 public:
    WriteBuffThread(QObject *parent = 0)
        : QThread(parent) {
        buff = new dArr(data, 6);
        qDebug() << "in WriteBuffThread";
    }

    void set(dArr *src) {
        if (this->buff != src)
            *(this->buff) = *src;
    }
    
    //private:   // comment out for tmp before buff->get() work
    unsigned char data[6] = {0};
    dArr *buff; //(data, 6);
    
 protected:
    void run() {
        int fd;          
        char* device = (char*)("/dev/snd/midiC1D0");
        fd = open(device, O_RDONLY, 0);
        if (fd == -1) {
            qDebug("Error: cannot open \n");
            exit(1);
        }

        while (true) {
            int bytes_read = read(fd, &data, sizeof(data));
            while (bytes_read < 0) {
                qDebug("Error reading %s\n", MIDI_DEVICE);
                bytes_read = read(fd, &data, sizeof(data));
            }
            for (int i = 0; i < 6; ++i)
                qDebug() << "data[" << i << "]: " << data[i];
            buff->set(data, 6);
            emit valueRead();
            sleep(100);
        }
    }
 signals:
    void valueRead();
};

#endif
