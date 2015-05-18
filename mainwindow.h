#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QPlainTextEdit>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QSocketNotifier>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <QLCDNumber>
#include <QTableWidget>
#include <QMutex>

#include "myDoubleSpinBox.h"
#include "renderarea.h"
#include "thread.h"
#include "config.h"
#include "player.h"

extern int top[10]; // 1 2 4 5 6; 8 9 11 12 13
extern int btm[15]; // 0 ~ 14
extern unsigned char notedata[6];
extern QMap<int, QString> mKeySong;
extern Thread *yy;

class MainWindow : public QMainWindow {
    Q_OBJECT
    QWidget *centralWidget;
public:
    QMap<int, QPushButton*> map;
    QString fileName;
    unsigned char inbytes[6];
    enum { NumGridRows = 12, NumButtons = 6 };
    QPushButton *buttons[NumButtons];
    QGroupBox *horizontalGroupBox;
    QDialogButtonBox *buttonBox;
    QPushButton* topKeys[15];
    QPushButton* bottomKeys[15];
    QList<RenderArea*> renderAreas;
    QPlainTextEdit *edit[33];
    QPushButton *brow[33];

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
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setHeight(QPlainTextEdit *edit, int nRows);
    void setColor(QPushButton *pbtn, QColor color);
 
public slots:
    void readFromDevice();
    void changeBoundedSong(int);
    
    // Phonon:
    void addFiles();
    void stateChanged(Phonon::State newState, Phonon::State oldState);
    void tick(qint64 time);
    void sourceChanged(const Phonon::MediaSource &source);
    void metaStateChanged(Phonon::State newState, Phonon::State oldState);
    void aboutToFinish();
    void tableClicked(int row, int column);
private:
    MyFile file;
    QMutex mutex;
    int keyData;
};

#endif
