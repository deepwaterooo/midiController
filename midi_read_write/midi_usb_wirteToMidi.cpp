/*
  10/30/2014:
  this programming connects and write data to midi controller with LED on consistantly
   */

#include <linux/soundcard.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char* device = (char*)("/dev/snd/midiC1D0"); // works key #7 LED on
    unsigned char data[3] = {0x90, 60, 127};

    // step 1: open the OSS device for writing
    int fd = open(device, O_WRONLY, 0); // HERE DOES NOT SEEM RIGHT
    if (fd < 0) {
        printf("Error: cannot open %s\n", device);
        exit(1);
    }

    // step 2: write the MIDI information to the OSS device
    write(fd, data, sizeof(data));

    // step 3: (optional) close the OSS device
    close(fd);

    return 0;
}


