#ifndef READBUFFTHREAD_H
#define READBUFFTHREAD_H

#include <QSound>
#include <QString>
#include <QThread>
#include <QMutex>
#include <stdlib.h>
//#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>

#include "db.h"

#define MIDI_DEVICE "/dev/snd/midiC1D0"

class ReadBuffThread : public QThread {
    Q_OBJECT
 public:
    ReadBuffThread(QObject *parent = 0)
        : QThread(parent) {
        buff = new dArr(data, 6);
        qDebug() << "in ReadBuffThread";
    }

    void set(dArr *src) {
        if (this->buff != src)
            *(this->buff) = *src;
    }
    
 private:   // comment out for tmp before buff->get() work
    unsigned char data[6];
    dArr *buff; //(data, 6);
    
 protected:
    void run() {
        while (true) {
            int fd;          
            char* device = (char*)("/dev/snd/midiC1D0");
            fd = open(device, O_RDONLY, 0);
            if (fd == -1) {
                qDebug("Error: cannot open \n");
                exit(1);
            }

            int bytes_read = read(fd, &data, sizeof(data));
            while (bytes_read < 0) {
                qDebug("Error reading %s\n", MIDI_DEVICE);
                bytes_read = read(fd, &data, sizeof(data));
            }
            for (int i = 0; i < 6; ++i)
                qDebug() << "data[" << i << "]: " << data[i];

            buff->set(data, 6);
            //msleep(10);
            /*
              playSong("Surfinusa.wav");
              //qDebug() << "inbytes[1]]: " << inbytes[1];
              setColor(map[inbytes[1]], QColor(255, 255, 0));
              idol(3);  
              setColor(map[inbytes[1]], QColor(255, 255, 255));
            */
        }
    }
 signals:
    void done();
};

#endif
