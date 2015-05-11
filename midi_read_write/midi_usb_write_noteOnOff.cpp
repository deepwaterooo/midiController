/*
  10/30/2014:
  this programming connects and write data to midi controller with LED on consistantly
  for sleep( int_num ) seconds, and write NOTE-OFF to turn LED off
   */

#include <linux/soundcard.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char* device = (char*)("/dev/snd/midiC1D0"); // works key #7 LED on

    unsigned char devnum = 0;
    unsigned char packet[6] = {SEQ_MIDIPUTC, 0, devnum, 0, 0, 0};
    printf("SEQ_MIDIPUTC: %d\n", SEQ_MIDIPUTC);
    printf("devnum: %d", devnum);
    
    // step 1: open the OSS device for writing
    int fd = open(device, O_WRONLY, 0); // HERE DOES NOT SEEM RIGHT
    if (fd < 0) {
        printf("Error: cannot open %s\n", device);
        exit(1);
    }

    // step 2: write the MIDI note on message as done in the prior example
    // the LED key 3C, 40 which is #60 & #64 NOTES-ON are on constantly
    packet[0] = 0x90;
    //write(fd, packet, sizeof(packet));
    packet[1] = 60;
    //write(fd, packet, sizeof(packet));
    packet[2] = 127;
    /*
    packet[3] = 0x90;
    write(fd, packet, sizeof(packet));
    packet[4] = 0x40;
    write(fd, packet, sizeof(packet));
    packet[5] = 40;
    */
    packet[3] = 0;
    //write(fd, packet, sizeof(packet));
    packet[4] = 0;
    //write(fd, packet, sizeof(packet));
    packet[5] = 0;
    for (int i = 0; i < 6; ++i)
        printf("packet[%d]: %d\n", i, packet[i]);
    write(fd, packet, sizeof(packet));

    // sleep half second
    sleep(20);
    
    // the LED key 3C, 40 which is #60 & #64 NOTES-OFF are on constantly
    packet[0] = 0x80;
    write(fd, packet, sizeof(packet));
    packet[1] = 60;
    write(fd, packet, sizeof(packet));
    packet[2] = 127;
    /*
    packet[3] = 0x80;
    write(fd, packet, sizeof(packet));
    packet[4] = 0x40;
    write(fd, packet, sizeof(packet));
    packet[5] = 40;
    */
    for (int i = 0; i < 6; ++i)
        printf("packet[%d]: %d\n", i, packet[i]);
    write(fd, packet, sizeof(packet));
    
    // step 3: (optional) close the OSS device
    close(fd);

    return 0;
}


