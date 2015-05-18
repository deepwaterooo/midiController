#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <QList>
#include <QtCore/QThread>
#include <QMutex>
#include <QLCDNumber>
#include <QTableWidget>

#include "thread.h"

extern Thread* yy;

class Player : public QObject {
    Q_OBJECT
 public:
    void setupActions();
    void setupUi();

    Phonon::SeekSlider *seekSlider;
    Phonon::MediaObject *mediaObject;
    Phonon::MediaObject *metaInformationResolver;
    Phonon::AudioOutput *audioOutput;
    Phonon::VolumeSlider *volumeSlider;
    QList<Phonon::MediaSource> sources;

    QAction *playAction;
    QAction *pauseAction;
    QAction *stopAction;
    QAction *nextAction;
    QAction *previousAction;
    QAction *addFilesAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QLCDNumber *timeLcd;
    QTableWidget *musicTable;

    Player();
    unsigned char inbytes[6];
    QSize sizeHint() const {
        return QSize(500, 300);
    }

public slots:
    void stateChanged(Phonon::State newState, Phonon::State oldState);
    void tick(qint64 time);
    void sourceChanged(const Phonon::MediaSource &source);
    void metaStateChanged(Phonon::State newState, Phonon::State oldState);
    void aboutToFinish();
    void tableClicked(int row, int column);
    void readFromDevice();
    
private:
    QMap<int, QString> mKeySong;
    QMutex mutex;
    int keyData;
};

#endif

/*
  QtDBus: cannot relay signals from parent Phonon::AbstractAudioOutput(0x1836690 "") unless they are emitted in the object's thread QThread(0x7fffb0edbe80 ""). Current thread is QThread(0x137ba00 "").
QtDBus: cannot relay signals from parent QObject(0x1836690 "") unless they are emitted in the object's thread QThread(0x7fffb0edbe80 ""). Current thread is QThread(0x137ba00 "").
QThread: Destroyed while thread is still running

(midiUI:4440): Gtk-CRITICAL **: IA__gtk_widget_get_direction: assertion 'GTK_IS_WIDGET (widget)' failed

(midiUI:4440): Gtk-CRITICAL **: IA__gtk_widget_get_direction: assertion 'GTK_IS_WIDGET (widget)' failed
readMidi notedata[ 0 ]:  144 
readMidi notedata[ 1 ]:  57 
readMidi notedata[ 2 ]:  127 
readMidi notedata[ 3 ]:  0 
readMidi notedata[ 4 ]:  0 
readMidi notedata[ 5 ]:  0 
 */
