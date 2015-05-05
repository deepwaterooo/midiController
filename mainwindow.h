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

#include "myDoubleSpinBox.h"
#include "renderarea.h"
#include "thread.h"

extern int top[10]; // 1 2 4 5 6; 8 9 11 12 13
extern int btm[15]; // 0 ~ 14
extern unsigned char notedata[6];

class MainWindow : public QMainWindow {
    Q_OBJECT
    QWidget *centralWidget;
    //private:
public:
    QMap<int, QPushButton*> map;
    QMap<int, QString> mKeySong;
    
    QString songName;
    unsigned char inbytes[6];
    enum { NumGridRows = 12, NumButtons = 6 };
    QPushButton *buttons[NumButtons];
    QGroupBox *horizontalGroupBox;
    QDialogButtonBox *buttonBox;
    QPushButton* topKeys[15];
    QPushButton* bottomKeys[15];
    QList<RenderArea*> renderAreas;

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
    void idol(int);
 
public slots:
    void readFromDevice();
    
    // Phonon:
    void addFiles();
    void about();
    void stateChanged(Phonon::State newState, Phonon::State oldState);
    void tick(qint64 time);
    void sourceChanged(const Phonon::MediaSource &source);
    void metaStateChanged(Phonon::State newState, Phonon::State oldState);
    void aboutToFinish();
    void tableClicked(int row, int column);
private:
    Thread *yy;
};

#endif
