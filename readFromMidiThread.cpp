#include "readFromMidiThread.h"

void ReadFromMidiThread::emitSig () {
    qDebug() << " from ReadFromMidiThread: " << QThread::currentThreadId();
    int cnt = 0;
    while (cnt < 2) {
        if (fd == -1) {
            qDebug("Error: cannot open \n");
            exit(1);
        }
        int bytes_read = read(fd, &notedata, sizeof(notedata));
        while (bytes_read < 0) {
            qDebug("Error reading %s\n", device);
            bytes_read = read(fd, &notedata, sizeof(notedata));
        }
        qDebug("ReadFromMidiThread inside: \n");
        for (int i = 0; i < 6; ++i)
            qDebug() << "notedata[" << i << "]: " << notedata[i];
        emit readSig();
        //close(fd);     
        sleep(5);
        cnt++;
    } 
}
