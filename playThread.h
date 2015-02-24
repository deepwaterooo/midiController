#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QSound>
#include <QString>
#include <QThread>
#include <QMutex>

class playThread : public QThread {
    Q_OBJECT
 public:
    playThread(QObject *parent = 0)
        : QThread(parent) {
    }
    void setSongName(QString s) {
        songName = s;
        currSnd = new QSound(":/snd/res_wav/" + songName);
    }
    void playStop() {   // problems here
        currSnd->stop();
    }
    ~playThread() {
        delete currSnd;
    }
    
 private:
    QSound *currSnd;
    QString songName;
    bool Stop;
 protected:
    void run() {
        currSnd->play();
        emit done();
    }
 signals:
    void done();
};

#endif
