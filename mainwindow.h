#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QPlainTextEdit>
//#include <QSound>
//#include <phonon>

//#include "space.h"

#define MIDI_DEVICE "/dev/snd/midiC1D0"
/*
int fd; 
pthread_t midiInThread;
unsigned char inbytes[4];        
*/
//pthread_t midiInThread;
//int fd; 
//extern int inbytes[4];


static const QPointF points[3] = {
    QPointF(10.0, 80.0),
    QPointF(20.0, 10.0),
    QPointF(80.0, 30.0)
};

// for thread implementation
//extern unsigned char inbytes[4];
//void* threadFunction(void* x);

class MainWindow : public QMainWindow {
    Q_OBJECT
    QWidget *centralWidget;
 private:
    //MediaObject *mediaObject;
        unsigned char inbytes[4];
        //void open();
        enum { NumGridRows = 12, NumButtons = 6 };
        QPushButton *buttons[NumButtons];
        QGroupBox *horizontalGroupBox;
        QDialogButtonBox *buttonBox;
        QPushButton* topKeys[15];
        QPushButton* bottomKeys[15];
 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setHeight(QPlainTextEdit *edit, int nRows);
    void readFromDevice();
    void playSurfUSA();
    void idol(int);
    public slots:
        void oneKeyClicked();
};

#endif
