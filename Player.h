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

class QAction;
class QTableWidget;
class QLCDNumber;

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
        //void addFiles();
        void stateChanged(Phonon::State newState, Phonon::State oldState);
        void tick(qint64 time);
        void sourceChanged(const Phonon::MediaSource &source);
        void metaStateChanged(Phonon::State newState, Phonon::State oldState);
        void aboutToFinish();
        void tableClicked(int row, int column);
        void slot_thread() {
            qDebug() << "\n from thread slot_thread:"  << QThread::currentThreadId();
            /*
            unsigned char* tmp = dummy->data; 
            for (int i = 0; i < 6; i++) {
                qDebug() << "tmp[i]: " << tmp[i];
                inbytes[i] = tmp[i];
                qDebug() << "inbytes[i]: " << inbytes[i] << ", ";
            }
            if (inbytes[0] == 144 && inbytes[2] > 0) { // need set to more detail         
                //setColor(map[inbytes[1]], QColor(255, 255, 0));     // cannot do it here
                int index = sources.size();
                qDebug() << "index: " << index;
                if (inbytes[2] > 0) {
                    Phonon::MediaSource source(mKeySong[inbytes[1]]);
                    sources.append(source);
                }
                qDebug() << "sources size: " << sources.size();
                if (!sources.isEmpty()) {
                    metaInformationResolver->setCurrentSource(sources.at(index));
                    //metaInformationResolver->setCurrentSource(sources.at(0));
                    //qDebug() << "sources.at(0): " << metaInformationResolver->currentSource().fileName();  
                    mediaObject->setCurrentSource(metaInformationResolver->currentSource()); // totalTime() in milliseconds
                    mediaObject->play();
                }
                } */ 
        }
        /*
 protected:  // for sub-QThread use only
        void run() {
            qDebug() << "Player thread:" << currentThreadId();
            connect(dummy, SIGNAL(readSig()), this, SLOT(slot_thread()));          
            dummy->emitSig();
            exec();       
        }
        */
 private:
        QMap<int, QString> mKeySong;
};

#endif
