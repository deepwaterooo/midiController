#ifndef THREAD_H     
#define THREAD_H     

#include <QThread>     
#include <QMutex>

extern char* device;
extern int fd;
extern unsigned char notedata[6];

class Thread : public QThread {     
    Q_OBJECT     
public:     
    Thread();     
    volatile bool stopped; // stoppedΪ0ʱ���˳��߳�
    volatile bool writeMidi;     
    volatile bool readMidi;
    volatile bool isPlaying;
private:
    unsigned char localBuff[6];
    QMutex mutex;
protected:     
    virtual void run();
signals:
    void readUpdate();
};     

#endif  
