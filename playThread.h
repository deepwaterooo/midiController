#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QSound>
#include <QString>
#include <QThread>
#include <QMutex>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <QPalette>
#include <QLCDNumber>

class playThread : public QThread {
    Q_OBJECT
 public:
    playThread(QObject *parent = 0)
        : QThread(parent) {
        audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
        mediaObject = new Phonon::MediaObject(this);
        /*
        metaInformationResolver = new Phonon::MediaObject(this);
        mediaObject->setTickInterval(1000);
        connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
        connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(stateChanged(Phonon::State,Phonon::State)));
        connect(metaInformationResolver, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(metaStateChanged(Phonon::State,Phonon::State)));
        connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)), this, SLOT(sourceChanged(Phonon::MediaSource)));
        connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));
*/
        Phonon::createPath(mediaObject, audioOutput);
    }
    void setSongName(QString s) {
        songName = s;
        mediaObject->setCurrentSource(Phonon::MediaSource("/home/jenny/480/qt/midiUI/res_wav/" + songName));
    }
    void playStop() { 
        mediaObject->stop();
    }
    void playPause() {    
        mediaObject->pause();
    }
    ~playThread() {
        delete mediaObject;
    }
    
 private:
    QString songName;
    Phonon::SeekSlider *seekSlider;
    Phonon::MediaObject *mediaObject;
    Phonon::MediaObject *metaInformationResolver;
    Phonon::AudioOutput *audioOutput;
    Phonon::VolumeSlider *volumeSlider;
    QList<Phonon::MediaSource> sources;
    QLCDNumber *timeLcd;

 protected:
    void run() {
        mediaObject->play();
        emit done();   // I suspect if I should emit finish signal here
    }
    
    void tick(qint64 time) {
        //QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
        //timeLcd->display(displayTime.toString("mm:ss"));
    }

 signals:
    void done();
};

#endif
