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

class ReadBuffThread : public QThread {
    //class ReadBuffThread : public QObject {
    Q_OBJECT
 public:
    ReadBuffThread(QObject *parent = 0)
        : QThread(parent) {
        //: QObject(parent) {
        buff = new dArr(data, 6);
        lit = false;
        qDebug() << "in ReadBuffThread";
        connect(this, SIGNAL(readValue()), this, SLOT(valueRead()));
        //emit readValue();
    }

    void set(dArr *src) {
        if (this->buff != src)
            *(this->buff) = *src;
    }
    
    //private:   // comment out for tmp before buff->get() work
 public:
    unsigned char data[6] = {0};
    unsigned char prev[3] = {0};    
    dArr *buff; //(data, 6);
    bool lit;

 protected:
    void run() {
        //void readValue();
        //public slots:
        //void valueRead() {
        int fd;          
        char* device = (char*)("/dev/snd/midiC1D0");
        int cnt = 0;
        //while (cnt < 100) {
        fd = open(device, O_RDWR, 0); 
        if (fd == -1) {
            qDebug("Error: cannot open \n");
            exit(1);
        }
        int bytes_read = read(fd, &data, sizeof(data));
        while (bytes_read < 0) {
            qDebug("Error reading %s\n", MIDI_DEVICE);
            bytes_read = read(fd, &data, sizeof(data));
        }
        qDebug("ReadBuffThread inside: \n");
        for (int i = 0; i < 6; ++i)
            qDebug() << "data[" << i << "]: " << data[i];
        buff->set(data, 6);
        /*
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
        */
        emit valueRead();
        close(fd);
        sleep(5);
        //cnt++;
        //}
    }
 signals:
    void valueRead();
};

#endif
