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
#include <QObject>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QSpinBox>
#include <QScrollBar>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
//MainWindow::MainWindow()

    setWindowTitle(tr("MIDI Command Interface Main Window"));

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

    // for main window layout    
    centralWidget = new QWidget();
    this->setCentralWidget(centralWidget);
    QVBoxLayout *vbox = new QVBoxLayout();   // for overall layout vbox

    // for midi keyboard layout hbox
    QHBoxLayout *hbox = new QHBoxLayout();   // for overall layout vbox
    QLabel* top[13];
    QLabel* bottom[15];
    for (int i = 0; i < 13; ++i) {        
        top[i] = new QLabel;
        /*
          top[i]->setStyleSheet("background-color: black;"
          "qproperty-alignment: AlignCenter;"
          "qproperty-wordWrap: false;");
        */
        topKeys[i] = new QPushButton();
        topKeys[i]->setFixedSize(50, 100);
    }
    top[0]->setText(tr("  10"));
    top[1]->setText(tr("  11"));
    top[2]->setText(tr(""));
    top[3]->setText(tr("  12"));
    top[4]->setText(tr("Channel"));
    top[5]->setText(tr("Rotate"));
    top[6]->setText(tr(""));
    top[7]->setText(tr(" CoMA"));
    top[8]->setText(tr("Xpose"));
    top[9]->setText(tr(""));
    top[10]->setText(tr(" Rec"));
    top[11]->setText(tr(" Stop"));
    top[12]->setText(tr("Play"));
    
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
    for (int i = 0; i < 13; ++i) {
        top[i]->setAlignment(Qt::AlignJustify);
        top[i]->setFixedWidth(50);
        topKeys[i]->setStyleSheet("QPushButton{color:red;background-color:rgb(255,255,255)}");
        topLabel->addWidget(top[i]);
        topkeys->addWidget(topKeys[i]);
    }
    for (int i = 0; i < 15; ++i) {        
        bottom[i]->setAlignment(Qt::AlignJustify);
        bottom[i]->setFixedWidth(50);
        bottomKeys[i]->setStyleSheet("QPushButton{color:red;background-color:rgb(255,255,255)}");
        bottomLabel->addWidget(bottom[i]);
        bottomkeys->addWidget(bottomKeys[i]);
    }
    // setflat for several keys
    topKeys[2]->setFlat(true);
    topKeys[6]->setFlat(true);
    topKeys[9]->setFlat(true);
    // topLabel add one vertial
    QVBoxLayout *topright = new QVBoxLayout();
    QLabel* trLabel[4];
    for (int i = 0; i < 4; ++i) {
        trLabel[i] = new QLabel;
    }
    trLabel[0]->setText(tr("QuNexus"));
    trLabel[1]->setText(tr("MIDI Expander")); // "MIDI Expander"
    trLabel[2]->setText(tr("Pedal In"));
    trLabel[3]->setText(tr("CV 1-2 In"));
    for (int i = 0; i < 4; ++i) {
        trLabel[i]->setAlignment(Qt::AlignRight);
        topright->addWidget(trLabel[i], Qt::AlignRight);
    }
    
    QVBoxLayout *vboxF3 = new QVBoxLayout();
    QVBoxLayout *vbox4 = new QVBoxLayout();
    //QGridLayout *vbox4 = new QGridLayout();   // need grid layout eventually
    vbox4->addLayout(topLabel);
    vbox4->addLayout(topkeys);
    QHBoxLayout *first = new QHBoxLayout();
    first->addLayout(vbox4);
    first->addLayout(topright);
    vboxF3->addLayout(first);
    vboxF3->addLayout(bottomkeys);
    vboxF3->addLayout(bottomLabel);

    // textbox
    QPlainTextEdit *text = new QPlainTextEdit();
    text->insertPlainText("| Keys     | Commands            |\n| 10        |                     |\n| 11        |                     |\n| 12       |                     |\n| Channel |                     |\n| Rotate  |                     |\n| CoMA    |                     |\n| Xpose   |                     |\n| Rec     |                     |\n| Stop    |                     |\n| Play    |                     |\n| 0       | Call Me Maybe       |\n| 1       | Shake It Off        |\n| 2       | All About That Bass |\n");
    QScrollBar *v = text->verticalScrollBar();
    v->setValue(0);
    //v->setValue(v->maxValue());
    vboxF3->addWidget(text);

    
    // final layout set    
    vbox->addLayout(vboxF3);   // vbox4 will be updated 
    centralWidget->setLayout(vbox);
}

void MainWindow::setHeight(QPlainTextEdit *edit, int nRows) { 
    QFontMetrics m (edit -> font()) ;
    int RowHeight = m.lineSpacing() ;
    edit -> setFixedHeight  (nRows * RowHeight) ;
}

MainWindow::~MainWindow() {
}

void MainWindow::open() {
    QMessageBox::information(this, tr("Information"), tr("Open"));
}
