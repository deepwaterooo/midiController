#include "mainwindow.h"

#include <QObject>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QtGui>
#include <QSplitter>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QSpinBox>
#include <QSlider>
#include <QPalette>
#include <QPushButton>
#include <QLabel>
#include <QTime>
#include <QTimeEdit>
#include <QComboBox>
#include <QPixmap>
#include <QMenuBar>
#include <QPlainTextEdit>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <string>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QSpinBox>
#include <QScrollBar>
#include <QRect>
#include <QRegion>
#include <QPoint>
#include <QPolygon>
#include <QPainter>
#include <QPaintEvent>
#include <QScrollArea>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>
#include <QSound>
//#include <phonon>

#include "mainwindow.h"

/*
  void* threadFunction(void*) {
  int status;            
  while (1) {
  char* fd = (char*)("/dev/snd/midiC1D0");
  status = open(fd, O_RDONLY, 0);
  if (status < 0) {
  printf("Error reading %s\n", MIDI_DEVICE);
  exit(1);
  }
  int bytes_read = read(status, &inbytes, sizeof(inbytes));
  if (bytes_read < 0) {
  qDebug("Error reading %s\n", MIDI_DEVICE);
  exit(1);
  }
  if (inbytes[1] != 0) {            
  for (int i = 0; i < 4; ++i) {            
  qDebug("received MIDI byte: ", inbytes[i]);
  }
  }
  }
  }
*/

void MainWindow::playSurfUSA() {
    QSound::play(":/snd/Surfinusa.wav");
    /*
    mediaObject = new Phonon::MediaObject(this);
    mediaObject->setCurrentSource(Phonon::MediaSource(":/snd/Surfinusa.wav"));
    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::Path path = Phonon::createPath(mediaObject, audioOutput);
    Phonon::SeekSlider *seekSlider = new Phonon::SeekSlider(mediaObject, this);
    mediaObject->play();
    */
}

void MainWindow::readFromDevice() {
    int fd;          
    //fd = open(MIDI_DEVICE, O_RDONLY);
    char* device = (char*)("/dev/snd/midiC1D0");
    fd = open(device, O_RDONLY, 0);
    if (fd == -1) {
        qDebug("Error: cannot open \n");
        exit(1);
    }
    /*
      pthread_t midiInThread;
      int status = pthread_create(&midiInThread, NULL, threadFunction, NULL);
      if (status == -1) {
      printf("Error: unable to create MIDI input thread.\n");
      exit(1);
      }
    */

    int cnt = 0;
    while (cnt < 3) {
        int bytes_read = read(fd, &inbytes, sizeof(inbytes));
        while (bytes_read < 0) {
            qDebug("Error reading %s\n", MIDI_DEVICE);
            bytes_read = read(fd, &inbytes, sizeof(inbytes));
        }
        if (inbytes[1] == 60) {            
            bottomKeys[7]->setStyleSheet("QPushButton{color:red;background-color:rgb(0,0,255)}");
            playSurfUSA();
            idol(3);
            return;
        }
    }
}

void MainWindow::idol(int x) {
    //sleep(x);
    QEventLoop loop;
    QTimer::singleShot(150000, &loop, SLOT(quit()));    //
    loop.exec();
    bottomKeys[7]->setStyleSheet("QPushButton{color:red;background-color:rgb(255,255,255)}");
}

// speciall work on bottomKeys[7] for playing one sequence
// 1. create a thread to read from device, and scanning for the input values;
// 2. if scanned value == 59 (key indexed 7), do the folloring:
//    a, paint the GUI key color to be blue;
//    b, write back to device to light LED on for the key;
//    c, trigger the playing audio file
//    d, when audio file done, light LED off
void MainWindow::oneKeyClicked() {
    readFromDevice();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle(tr("MIDI Command Interface Main Window"));
    
    // for main window layout    
    centralWidget = new QWidget();
    this->setCentralWidget(centralWidget);
    QVBoxLayout *vbox = new QVBoxLayout();   // for overall layout vbox

    // for midi keyboard layout hbox
    QHBoxLayout *hbox = new QHBoxLayout();   // for overall layout vbox
    QLabel* top[15];
    QLabel* bottom[15];
    for (int i = 0; i < 15; ++i) {        
        top[i] = new QLabel;
        topKeys[i] = new QPushButton();
        topKeys[i]->setFixedSize(50, 100);
    }
    topKeys[0]->setFixedSize(20, 100);
    topKeys[14]->setFixedSize(70, 100);
    top[0]->setText(tr(""));
    top[1]->setText(tr("    10"));
    top[2]->setText(tr("    11"));
    top[3]->setText(tr(""));
    top[4]->setText(tr("   12"));
    top[5]->setText(tr("Channel"));
    top[6]->setText(tr("Rotate"));
    top[7]->setText(tr(""));
    top[8]->setText(tr(" CoMA"));
    top[9]->setText(tr("Xpose"));
    top[10]->setText(tr(""));
    top[11]->setText(tr(" Rec"));
    top[12]->setText(tr(" Stop"));
    top[13]->setText(tr("Play"));
    top[14]->setText(tr(""));
    for (int i = 0; i < 15; ++i) {        
        bottom[i] = new QLabel;
        bottomKeys[i] = new QPushButton();
        bottomKeys[i]->setFixedSize(50, 100);
    }
    bottom[0]->setText(tr("     0"));
    bottom[1]->setText(tr("     1"));
    bottom[2]->setText(tr("     2"));
    bottom[3]->setText(tr("     3"));
    bottom[4]->setText(tr("     4"));
    bottom[5]->setText(tr("     5"));
    bottom[6]->setText(tr("     6"));
    bottom[7]->setText(tr("     7"));
    bottom[8]->setText(tr("     8"));
    bottom[9]->setText(tr("     9"));
    bottom[10]->setText(tr("  Notes"));
    bottom[11]->setText(tr("     CC"));
    bottom[12]->setText(tr("  Bend"));
    bottom[13]->setText(tr("  AftTch"));
    bottom[14]->setText(tr("ChnPres"));
    QHBoxLayout *topLabel = new QHBoxLayout();
    QHBoxLayout *topkeys = new QHBoxLayout();
    QHBoxLayout *bottomLabel = new QHBoxLayout();
    QHBoxLayout *bottomkeys = new QHBoxLayout();
    for (int i = 0; i < 15; ++i) {
        top[i]->setAlignment(Qt::AlignJustify);
        top[i]->setFixedWidth(50);
        topKeys[i]->setStyleSheet("QPushButton{color:red;background-color:rgb(255,255,255)}");
        topLabel->addWidget(top[i]);
        topkeys->addWidget(topKeys[i]);
    }
    top[0]->setFixedWidth(20);
    for (int i = 0; i < 15; ++i) {        
        bottom[i]->setAlignment(Qt::AlignJustify);
        bottom[i]->setFixedWidth(50);
        bottomKeys[i]->setStyleSheet("QPushButton{color:red;background-color:rgb(255,255,255)}");
        bottomLabel->addWidget(bottom[i]);
        bottomkeys->addWidget(bottomKeys[i]);
    }
    // setflat for several keys
    topKeys[0]->setFlat(true);
    topKeys[3]->setFlat(true);
    topKeys[7]->setFlat(true);
    topKeys[10]->setFlat(true);
    topKeys[14]->setFlat(true);

    // speciall work on bottomKeys[7] for playing one sequence
    // 1. create a thread to read from device, and scanning for the input values;
    // 2. if scanned value == 59 (key indexed 7), do the folloring:
    //    a, paint the GUI key color to be blue;
    //    b, write back to device to light LED on for the key;
    //    c, trigger the playing audio file
    //    d, when audio file done, light LED off
    connect(bottomKeys[7], SIGNAL(released()), this, SLOT(oneKeyClicked()));



    
    QVBoxLayout *vbox4 = new QVBoxLayout();
    vbox4->addLayout(topLabel);
    vbox4->addLayout(topkeys);
    vbox4->addLayout(bottomkeys);
    vbox4->addLayout(bottomLabel);

    // for leftside circle and other buttons
    QPushButton *topB[3];
    QPushButton *midB[3];
    QPushButton *botB[3];
    QLabel *topT[3];
    QLabel *midT[3];
    QLabel *botT[3];
    // for circles and triangles
    QRect *rect = new QRect(0,0,30,30);
    QRegion *region = new QRegion(*rect, QRegion::Ellipse);
    // for triangle
    //QPainter painter2(this); 
    //painter2.drawPolyline(points, 3);
    /*
      QPainter painter(this);   // this ?
      QPolygon p();
      p.append( QPoint(10,10) );
      p.append(QPoint(14,10));
      p.append(QPoint(12,14));
    */
    for (int i = 0; i < 3; ++i) {        
        topB[i] = new QPushButton();
        midB[i] = new QPushButton();
        botB[i] = new QPushButton();
        topB[i]->setStyleSheet("QPushButton{color:red;background-color:rgb(255,255,255)}");
        midB[i]->setStyleSheet("QPushButton{color:red;background-color:rgb(255,255,255)}");
        botB[i]->setStyleSheet("QPushButton{color:red;background-color:rgb(255,255,255)}");
        topB[i]->setFixedSize(30,30);
        midB[i]->setFixedSize(30,30);
        botB[i]->setFixedSize(30,30);
        topB[i]->setMask(*region);
        midB[i]->setMask(*region);
        botB[i]->setMask(*region);
        topT[i] = new QLabel;
        midT[i] = new QLabel;
        botT[i] = new QLabel;
    }
    topB[0]->setFlat(true); // make invisible
    
    topT[0]->setText("  Shift");
    topT[1]->setText("Togl A");
    topT[2]->setText("Velo B");
    midT[0]->setText("Preset");
    midT[1]->setText("Pres C");
    midT[2]->setText("Tilt D");
    botT[0]->setText("Bend");
    botT[1]->setText("-Oct");
    botT[2]->setText("Oct+");
    
    // for containing these topleft
    QHBoxLayout *hbox0 = new QHBoxLayout(); // for layout propose only
    QHBoxLayout *hbox1 = new QHBoxLayout();
    QHBoxLayout *hbox2 = new QHBoxLayout();
    QHBoxLayout *hbox3 = new QHBoxLayout();
    QHBoxLayout *hbox4 = new QHBoxLayout();
    QHBoxLayout *hbox5 = new QHBoxLayout();
    QHBoxLayout *hbox6 = new QHBoxLayout();
    for (int i = 0; i < 3; ++i) {
        hbox1->addWidget(topB[i]);
        hbox2->addWidget(topT[i]);
        hbox3->addWidget(midB[i]);
        hbox4->addWidget(midT[i]);
        hbox5->addWidget(botB[i]);
        hbox6->addWidget(botT[i]);
    }
    QVBoxLayout *topleft = new QVBoxLayout();
    QPushButton *space = new QPushButton();
    space->setFixedSize(150, 50);
    space->setFlat(true);
    hbox0->addWidget(space);
    topleft->addLayout(hbox0);
    topleft->addLayout(hbox1);
    topleft->addLayout(hbox2);
    topleft->addLayout(hbox3);
    topleft->addLayout(hbox4);
    topleft->addLayout(hbox5);
    topleft->addLayout(hbox6);

    
    //QHBoxLayout *hboxL[33];
    QLabel *label[33];
    QPlainTextEdit *edit[33];
    QPushButton *brow[33];
    for (int i = 0; i < 33; ++i) {
        label[i] = new QLabel;
    }
    label[0]->setText(tr("     0"));
    label[1]->setText(tr("     1"));
    label[2]->setText(tr("     2"));
    label[3]->setText(tr("     3"));
    label[4]->setText(tr("     4"));
    label[5]->setText(tr("     5"));
    label[6]->setText(tr("     6"));
    label[7]->setText(tr("     7"));
    label[8]->setText(tr("     8"));
    label[9]->setText(tr("     9"));
    label[10]->setText(tr("  Notes"));
    label[11]->setText(tr("     CC"));
    label[12]->setText(tr("  Bend"));
    label[13]->setText(tr("  AftTch"));
    label[14]->setText(tr("ChnPres"));
    label[15]->setText(tr("    10"));
    label[16]->setText(tr("    11"));
    label[17]->setText(tr("   12"));
    label[18]->setText(tr("Channel"));
    label[19]->setText(tr("Rotate"));
    label[20]->setText(tr(" CoMA"));
    label[21]->setText(tr("Xpose"));
    label[22]->setText(tr(" Rec"));
    label[23]->setText(tr(" Stop"));
    label[24]->setText(tr("Play"));
    label[25]->setText("Togl A");
    label[26]->setText("Velo B");
    label[27]->setText("Preset");
    label[28]->setText("Pres C");
    label[29]->setText("Tilt D");
    label[30]->setText("Bend");
    label[31]->setText("-Oct");
    label[32]->setText("Oct+");
    
    // final layout set
    QHBoxLayout *hboxMidi = new QHBoxLayout();  // for midi keyboard
    hboxMidi->addLayout(topleft);
    hboxMidi->addLayout(vbox4);
    vbox->addLayout(hboxMidi);   // vbox4 will be updated

    // grid with a vertical scrollbar
    QScrollArea * scrollArea = new QScrollArea();
    QWidget *contentsWidget = new QWidget(scrollArea);
    QGridLayout *grid = new QGridLayout(contentsWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(contentsWidget);
    contentsWidget->setLayout(grid);
    contentsWidget->setMinimumSize(scrollArea->width(), scrollArea->height());
    grid->setHorizontalSpacing(2);
    grid->setVerticalSpacing(2);
    
    for (int i = 0; i < 33; ++i) {
        label[i]->setFixedWidth(100);
        label[i]->setAlignment(Qt::AlignRight);
        edit[i] = new QPlainTextEdit;
        brow[i] = new QPushButton(QIcon(":/images/doc-open"), tr("&Browse"));
        edit[i]->setFont(QFont ("Courier", 10));
        setHeight(edit[i], 2);
        //brow[i]->setFixedSize(80, 25);
        brow[i]->setFixedWidth(80);
        grid->addWidget(label[i], i, 0);
        grid->addWidget(edit[i], i, 1);
        grid->addWidget(brow[i], i, 2);
    }
    // Make the scroll step the same width as the fixed widgets in the grid
    //grid->verticalScrollBar()->setSingleStep(contentsWidget->height() / 33);
    vbox->addWidget(scrollArea);
    centralWidget->setLayout(vbox);
}

void MainWindow::setHeight(QPlainTextEdit *edit, int nRows) { 
    QFontMetrics m (edit -> font()) ;
    int RowHeight = m.lineSpacing() ;
    edit -> setFixedHeight  (nRows * RowHeight) ;
}

MainWindow::~MainWindow() {
}
/*
  void MainWindow::open() {
  QMessageBox::information(this, tr("Information"), tr("Open"));
  }
*/
/*
  openAction = new QAction(QIcon(":/images/doc-open"), tr("&Open..."), this);
  openAction->setShortcuts(QKeySequence::Open);
  openAction->setStatusTip(tr("Open an existing .wav file"));
  connect(openAction, &QAction::triggered, this, &MainWindow::open);

  QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAction);
  QMenu *edit = menuBar()->addMenu(tr("&Edit"));
  QMenu *insert = menuBar()->addMenu(tr("&Insert"));
  QMenu *animate = menuBar()->addMenu(tr("&Practice"));
  QMenu *view = menuBar()->addMenu(tr("&View"));
  QMenu *help = menuBar()->addMenu(tr("&Docus"));
  QMenu *about = menuBar()->addMenu(tr("&Help"));

  openAction2 = new QAction(QIcon(":/images/doc-close"), tr("&Close..."), this);
  openAction3 = new QAction(QIcon(":/images/searchI"), tr("&Search..."), this);
  openAction4 = new QAction(QIcon(":/images/copyI"), tr("&Copy..."), this);
  openAction5 = new QAction(QIcon(":/images/pasteI"), tr("&Paste..."), this);
  openAction2->setShortcuts(QKeySequence::Close);
  openAction2->setStatusTip(tr("Close an existing .wav file"));

  toolBar = addToolBar(tr("&File"));
  toolBar->addAction(openAction);
  toolBar->addAction(openAction2);
  toolBar->addAction(openAction3);
  toolBar->addAction(openAction4);
  toolBar->addAction(openAction5);

  statusBar();
*/

