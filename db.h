#ifndef DB_H
#define DB_H

#include <QMutex>
#include <QDebug>

class dArr {
 public:
    dArr(unsigned char a[], int n)  {
        for (int i = 0; i < 6; ++i) 
            buff[i] = a[i];
    }

    unsigned char* get() {
        QMutex mutex;
        mutex.lock();
        for (int i = 0; i < 6; ++i)
            qDebug() << "buff[" << i << "]: " << buff[i];
        mutex.unlock();
        return buff;
    }

    void set(unsigned char a[], int n) {
        QMutex mutex;
        mutex.lock();
        for (int i = 0; i < 6; ++i) {
            buff[i] = a[i];
            qDebug() << "dArr buff[" << i << "]" << buff[i];
        }
        mutex.unlock();
    }
 private:
    unsigned char buff[6] = {0};
};

#endif
