#ifndef THREAD_H     
#define THREAD_H     

#include <QThread>     
#include <QMutex>

extern char* device;
extern int fd;
//extern unsigned char notedata[6] = {SEQ_MIDIPUTC, 0, 0, 0, 0, 0};;

class Thread : public QThread {     
    Q_OBJECT     
public:     
    Thread();     
    unsigned char notedata[6];
    volatile bool stopped; 
    volatile bool writeMidi;     
    volatile bool readMidi;
    volatile bool isPlaying;
private:
    unsigned char localBuff[6];
    //QMutex mutex;
protected:     
    virtual void run();
signals:
    void readUpdate();
};     

#endif  
