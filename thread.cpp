#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <QDebug>
#include <QMutex>

#include "thread.h"     

#define DEVICE "/dev/snd/midiC1D0"                            

Thread::Thread()
    : QThread() {}         

void Thread::run() {        
    qDebug("start...\n");     
    int fd = open((char*)DEVICE, O_RDWR, 0); // 以读写方式打开串口。
    if (fd < 0) {         
        qDebug("Got fd < 0 error here");     
        exit(1);    
    }
    
    qDebug("Read...\n");
    int bytes_read, bytes_write;
    int cnt = 0;
    bool isDifferent = false;
    
    while (stopped) { 
        if (writeMidi) { // write LED Off
            writeMidi = 0;
            
            //mutex.lock();
            bytes_write = write(fd, notedata, sizeof(notedata));
            while (bytes_write < 0) {
                bytes_write = write(fd, notedata, sizeof(notedata));
            }
            //mutex.unlock();
            
            readMidi = 1; 
        }

        if (readMidi) { 
            readMidi = 0;

            //mutex.lock();
            bytes_read = read(fd, &notedata, sizeof(notedata));
            while (bytes_read < 0) 
                bytes_read = read(fd, &notedata, sizeof(notedata));
            //mutex.unlock();
            
            for (int i = 0; i < 6; ++i) {
                if (cnt == 0 || (cnt > 0 && i < 2 && notedata[i] != localBuff[i])) {
                    isDifferent = 1;
                    localBuff[i] = notedata[i];
                }
                if (i == 2 && notedata[i] > 0) {
                    isDifferent = 0;
                    isPlaying = 1;   
                }
            } 
            cnt++;
            if (isPlaying) { // write LED on

                // write Note-ON LED-ON
                //mutex.lock();
                notedata[2] = 127;
                for (int i = 3; i < 6; i++) 
                    notedata[i] = 0;
                bytes_write = write(fd, notedata, sizeof(notedata));
                while (bytes_write < 0) {
                    bytes_write = write(fd, notedata, sizeof(notedata));
                }
                //mutex.unlock();

                for (int i = 0; i < 6; ++i) 
                    qDebug() << "readMidi notedata[" << i << "]: " << notedata[i];
                emit readUpdate();
            }
            isDifferent = 0;
        }
        //sleep(5);
    }
    qDebug("Close...");
    close(fd);     
    quit();
}  
/*
  notedata[ 0 ]:  144 
  notedata[ 1 ]:  55 
  notedata[ 2 ]:  49 
  notedata[ 3 ]:  0 
  notedata[ 4 ]:  0 
  notedata[ 5 ]:  0
  
  notedata[ 0 ]:  144 
  notedata[ 1 ]:  55 
  notedata[ 2 ]:  0 
  notedata[ 3 ]:  144 
  notedata[ 4 ]:  55 
  notedata[ 5 ]:  0 

  notedata[ 0 ]:  144 
  notedata[ 1 ]:  53  //.........
  notedata[ 2 ]:  44   
  notedata[ 3 ]:  144 
  notedata[ 4 ]:  55  //.........
  notedata[ 5 ]:  0 
 */
