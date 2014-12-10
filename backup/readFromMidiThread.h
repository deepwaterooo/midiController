#ifndef READFROMMIDITHREAD_H
#define READFROMMIDITHREAD_H

#include <stdio.h>
#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define MIDI_DEVICE "/dev/snd/midiC1D0"

int                         seqfd;          // sequencer file descriptor
pthread_t                   midiInThread;   // thread blocker for midi input
unsigned char inbytes[4];         // bytes from sequencer driver

//void* threadFunction(void* x);
//void readFromDevice();
void* threadFunction(void* x) {
    //unsigned char inbytes[4];         // bytes from sequencer driver
    int status;               // for error checking

    while (1) {
        status = read(seqfd, &inbytes, sizeof(inbytes));
        if (status < 0) {
            printf("Error reading %s\n", MIDI_DEVICE);
            exit(1);
        }
 
        //if (inbytes[0] == SEQ_MIDIPUTC) {
        printf("received MIDI byte: %d\n", inbytes[1]);
        //}
    }
}

void readFromDevice() {
    int status;            // for error checking
    seqfd = open(MIDI_DEVICE, O_RDONLY);
    if (seqfd == -1) {
        printf("Error: cannot open %s\n", MIDI_DEVICE);
        exit(1);
    } 
    status = pthread_create(&midiInThread, NULL, threadFunction, NULL);
    if (status == -1) {
        printf("Error: unable to create MIDI input thread.\n");
        exit(1);
    } 
    while (1) {
    }
}

#endif
