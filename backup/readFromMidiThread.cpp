// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Tue Dec 22 20:12:18 PST 1998
// Last Modified: Tue Dec 22 20:12:23 PST 1998
// Filename:      insimple.c
// Syntax:        C; pthread
// $Smake:        gcc -O3 -Wall -o %b %f -lpthread && strip %b 

#include <stdio.h>
#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "readFromMidiThread.h"

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
