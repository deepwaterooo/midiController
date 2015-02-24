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
#include <QSound>
//#include <phonon>

#include "myDoubleSpinBox.h"
#include "renderarea.h"
#include "playThread.h"
#include "db.h"
#include "ReadBuffThread.h"

#define MIDI_DEVICE "/dev/snd/midiC1D0"

class MainWindow : public QMainWindow {
    Q_OBJECT
    QWidget *centralWidget;
 private:
    QMap<int, QPushButton*> map;
    playThread *pthread;
    ReadBuffThread *tRead;
    QString songName;
    unsigned char inbytes[6];
    //int inbytes[6];
    enum { NumGridRows = 12, NumButtons = 6 };
    QPushButton *buttons[NumButtons];
    QGroupBox *horizontalGroupBox;
    QDialogButtonBox *buttonBox;
    QPushButton* topKeys[15];
    QPushButton* bottomKeys[15];
    QList<RenderArea*> renderAreas;
 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setHeight(QPlainTextEdit *edit, int nRows);
    void setColor(QPushButton *pbtn, QColor color);
    void playSong(QString s);
    void idol(int);
    public slots:
        //void oneKeyClicked();
        void readFromDevice();
        void stopPlayingSong();
};

#endif
