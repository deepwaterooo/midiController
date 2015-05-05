#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <QDebug>

#include "thread.h"     

#define DEVICE "/dev/snd/midiC1D0"                            
//char* device = (char*)("/dev/snd/midiC1D0");

Thread::Thread() {}         

void Thread::run() {        
    qDebug("start...\n");     
    int fd = open((char*)DEVICE, O_RDWR, 0); // �Զ�д��ʽ�򿪴��ڡ�
    if (fd < 0) {         
        qDebug("Got fd < 0 error here");     
        exit(1);    
    }
    
    qDebug("Read...\n");
    int bytes_read; 

    while (stopped) { // stopped Ϊ 0 ʱ���˳��߳�     
        //if (isPlaying | writeMidi) { // write == 1, write note on
        if (writeMidi) { // write == 1, write note on
            writeMidi = 0;
            for (int i = 3; i < 6; i++) 
                notedata[i] = 0;
            write(fd, notedata, sizeof(notedata));
            emit readUpdate();
            readMidi = 0;    // I added here
        }
        if (readMidi) { // read == 1, read into notedata
            readMidi = 0;
            bytes_read = read(fd, &notedata, sizeof(notedata));
            while (bytes_read < 0) {
                qDebug("Error reading %s\n", DEVICE);
                bytes_read = read(fd, &notedata, sizeof(notedata));
            }
            for (int i = 0; i < 6; ++i) {
                qDebug() << "notedata[" << i << "]: " << notedata[i];
                if (notedata[i] != localBuff[i]) {
                    // this isPlaying should be tricker
                    //isPlaying = 1;
                    writeMidi = 1;
                    localBuff[i] = notedata[i];
                }
                /*
                if (isPlaying) {
                    for (int i = 3; i < 6; i++) 
                        notedata[i] = 0;
                    write(fd, notedata, sizeof(notedata));

                    emit readUpdate();
                }
                */
            }
        }
    }
    qDebug("Close...");
    close(fd);     
    //sleep(5);
    quit();
}  
