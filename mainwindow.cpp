#include <QGraphicsProxyWidget>
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
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>
#include <QSound>
#include <QGraphicsScene>
#include <QSocketNotifier>
#include <phonon> 
#include <QThread>

#include "mainwindow.h"
#include "db.h"
//#include "Player.h"

void MainWindow::setColor(QPushButton *pbtn, QColor color) {
    int r,g,b;
    color.getRgb(&r, &g, &b);
    QString temp = "QPushButton{color:red;background-color:rgb(";
    QString tempr = QString::number(r);
    QString tempg = QString::number(g);
    QString tempb = QString::number(b);
    temp = temp + tempr + "," + tempg + "," + tempb + ")}";
    pbtn->setStyleSheet(temp); 
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
    top[12]->setText(tr("Stop"));
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

    
    // ----------------------------------------------------------------------------------------------------------
    // ------ for Phonon ------ 
    // ----------------------------------------------------------------------------------------------------------
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    metaInformationResolver = new Phonon::MediaObject(this);
    mediaObject->setTickInterval(1000);
    
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(stateChanged(Phonon::State,Phonon::State)));
    connect(metaInformationResolver, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(metaStateChanged(Phonon::State,Phonon::State)));
    connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)), this, SLOT(sourceChanged(Phonon::MediaSource)));
    connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));
    
    Phonon::createPath(mediaObject, audioOutput);

    // setupActions
    playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
    playAction->setShortcut(tr("Ctrl+P"));
    playAction->setDisabled(true);
    pauseAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
    pauseAction->setShortcut(tr("Ctrl+A"));
    pauseAction->setDisabled(true);
    stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
    stopAction->setShortcut(tr("Ctrl+S"));
    stopAction->setDisabled(true);
    nextAction = new QAction(style()->standardIcon(QStyle::SP_MediaSkipForward), tr("Next"), this);
    nextAction->setShortcut(tr("Ctrl+N"));
    previousAction = new QAction(style()->standardIcon(QStyle::SP_MediaSkipBackward), tr("Previous"), this);
    previousAction->setShortcut(tr("Ctrl+R"));
    nextAction->setDisabled(true);
    previousAction->setDisabled(true);
    addFilesAction = new QAction(tr("Add &Files"), this);
    addFilesAction->setShortcut(tr("Ctrl+F"));
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setShortcut(tr("Ctrl+Q"));
    
    connect(playAction, SIGNAL(triggered()), mediaObject, SLOT(play()));
    connect(pauseAction, SIGNAL(triggered()), mediaObject, SLOT(pause()) );
    connect(stopAction, SIGNAL(triggered()), mediaObject, SLOT(stop()));
    connect(addFilesAction, SIGNAL(triggered()), this, SLOT(addFiles()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    
    // setupMenus
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(addFilesAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    QMenu *aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
    aboutMenu->addAction(aboutQtAction);

    // setupUi
    QToolBar *bar = new QToolBar;
    bar->addAction(playAction);
    bar->addAction(pauseAction);
    bar->addAction(stopAction);
    bar->addAction(previousAction);
    bar->addAction(nextAction);
    seekSlider = new Phonon::SeekSlider(this);
    seekSlider->setMediaObject(mediaObject);
    volumeSlider = new Phonon::VolumeSlider(this);
    volumeSlider->setAudioOutput(audioOutput);
    volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    QLabel *volumeLabel = new QLabel;
    volumeLabel->setPixmap(QPixmap("images/volume.png"));
    QPalette palette;
    palette.setBrush(QPalette::Light, Qt::darkGray);
    timeLcd = new QLCDNumber;
    timeLcd->setPalette(palette);

    // musicTable
    QStringList headers;
    headers << tr("Title") << tr("Artist") << tr("Album") << tr("Year");
    musicTable = new QTableWidget(0, 4);
    musicTable->horizontalHeader()->setStretchLastSection(true);
    musicTable->setHorizontalHeaderLabels(headers);
    musicTable->setSelectionMode(QAbstractItemView::SingleSelection);
    musicTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(musicTable, SIGNAL(cellPressed(int,int)), this, SLOT(tableClicked(int,int)));

    QHBoxLayout *playbackLayout = new QHBoxLayout;
    playbackLayout->addWidget(seekSlider);
    playbackLayout->addWidget(timeLcd);
    playbackLayout->addWidget(volumeLabel);
    playbackLayout->addWidget(volumeSlider);
    playbackLayout->addWidget(bar);
    timeLcd->display("00:00");

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
    QPainterPath roundRectPath;
    roundRectPath.moveTo(80.0, 35.0);
    roundRectPath.arcTo(70.0, 30.0, 10.0, 10.0, 0.0, 90.0);
    roundRectPath.lineTo(25.0, 30.0);
    roundRectPath.arcTo(20.0, 30.0, 10.0, 10.0, 90.0, 90.0);
    roundRectPath.lineTo(20.0, 65.0);
    roundRectPath.arcTo(20.0, 60.0, 10.0, 10.0, 180.0, 90.0);
    roundRectPath.lineTo(75.0, 70.0);
    roundRectPath.arcTo(70.0, 60.0, 10.0, 10.0, 270.0, 90.0);
    roundRectPath.closeSubpath();
    QPainterPath rectPath;
    QRect boundingRect(2, 0, 60, 60);
    rectPath.moveTo(6.0, 15);
    rectPath.lineTo(58.0, 15);
    rectPath.arcTo(boundingRect, 30, -60);
    rectPath.lineTo(6.0, 45);
    rectPath.arcTo(boundingRect, 210, -60);
    QPainterPath triLftPath;
    triLftPath.moveTo(41, 15);
    triLftPath.lineTo(15, 30);
    triLftPath.lineTo(41, 45);
    triLftPath.closeSubpath();
    QPainterPath triRitPath;
    triRitPath.moveTo(5, 15);
    triRitPath.lineTo(31, 30);
    triRitPath.lineTo(5, 45);
    triRitPath.closeSubpath();
    renderAreas.push_back(new RenderArea(rectPath));
    renderAreas.push_back(new RenderArea(triLftPath));
    renderAreas.push_back(new RenderArea(triRitPath));
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
        topT[i] = new QLabel;
        midT[i] = new QLabel;
        botT[i] = new QLabel;
    }
    topB[0]->setFlat(true); 
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
        hbox6->addWidget(botT[i]);
    }
    int i = 0;
    for(QList<RenderArea*>::iterator it = renderAreas.begin(); it != renderAreas.end(); it++, i++) {
        (*it)->setFillGradient(QColor(255, 255, 255), QColor(255, 255, 255));
        hbox5->addWidget(*it, Qt::AlignCenter);        
    }
    hbox5->setSpacing(0);
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
    
    QLabel *label[33];
    QPlainTextEdit *edit[33];
    QPushButton *brow[33];
    for (int i = 0; i < 33; ++i) label[i] = new QLabel;
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

    QHBoxLayout *hbox02 = new QHBoxLayout();
    vbox->addWidget(musicTable);  // for test propose only
    vbox->addLayout(playbackLayout);
    
    // grid with a vertical scrollbar
    QScrollArea * scrollArea = new QScrollArea();
    QWidget *contentsWidget = new QWidget(scrollArea);
    QGridLayout *grid = new QGridLayout(contentsWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(contentsWidget);
    contentsWidget->setLayout(grid);
    contentsWidget->setMinimumSize(scrollArea->width(), scrollArea->height());
    grid->setHorizontalSpacing(2);
    grid->setVerticalSpacing(1);
    
    for (int i = 0; i < 33; ++i) {
        label[i]->setFixedWidth(100);
        label[i]->setAlignment(Qt::AlignRight);
        edit[i] = new QPlainTextEdit;
        brow[i] = new QPushButton(QIcon(":/images/doc-open"), tr("&Browse"));
        edit[i]->setFont(QFont ("Courier", 8));
        setHeight(edit[i], 2);
        brow[i]->setFixedWidth(80);
        grid->addWidget(label[i], i, 0);
        grid->addWidget(edit[i], i, 1);
        grid->addWidget(brow[i], i, 2);
    }
    edit[7]->setFont(QFont ("Courier", 10));
    setHeight(edit[7], 2);
    edit[7]->insertPlainText("Surfinusa.wav");
    // Make the scroll step the same width as the fixed widgets in the grid
    //grid->verticalScrollBar()->setSingleStep(contentsWidget->height() / 33);
    vbox->addWidget(scrollArea);
    centralWidget->setLayout(vbox);

    map[48] = bottomKeys[0];
    map[50] = bottomKeys[1];
    map[52] = bottomKeys[2];
    map[53] = bottomKeys[3];
    map[55] = bottomKeys[4];
    map[57] = bottomKeys[5];
    map[59] = bottomKeys[6];
    map[60] = bottomKeys[7];
    map[62] = bottomKeys[8];
    map[64] = bottomKeys[9];
    map[65] = bottomKeys[10];
    map[67] = bottomKeys[11];
    map[69] = bottomKeys[12];
    map[71] = bottomKeys[13];
    map[72] = bottomKeys[14];
    map[49] = topKeys[1];
    map[51] = topKeys[2];
    map[54] = topKeys[4];
    map[56] = topKeys[5];
    map[58] = topKeys[6];
    map[61] = topKeys[8];
    map[63] = topKeys[9];
    map[66] = topKeys[11];
    map[68] = topKeys[12];
    map[70] = topKeys[13];
    mKeySong[55] = QString("TheHeavyclip.wav");      // 4 5 6 7 8 9
    mKeySong[57] = QString("Surfin' U.S.A..wav");
    mKeySong[59] = QString("05 Grand Experiment.wav");
    mKeySong[60] = QString("Pharrell_Walliams_-_Happy.wav");
    mKeySong[62] = QString("Karnintro.wav");
    mKeySong[64] = QString("Karn Evil 9_1st Impression-Part 2 copy.wav");

    // not a GOOD one, but a start
    // I am NOT quite sure why this doesn't work, but it seems it could be feasible if I separate the whole phonon player stuff into a separate QObject descendant, and then moveToThread(...) ...., try this method!
    for (int i = 0; i < 6; i++) inbytes[i] = 0;
    dArr *buff = new dArr(inbytes, 6);  // copied to buff->buff

    // this step proves that the playAction not responsive is caused by thread instead of any Phonon step (it removed all thread part, and is responding as expected.)
    //connect(topKeys[13], SIGNAL(clicked()), this, SLOT(addFiles()));   

    /*
    Dummy dummy;
    Player player;
    Qthread thread;
    player.moveToThread(thread);
    connect(dummy, SIGNAL(readUpdate()), player, SLOT(play())); // problem here

    qDebug() << "main thread: " << QThread::currentThreadId();
    Player* player = new Player(this);
    player->start();
    */
    
    // for rectangle "Bend" key connection
    QList<RenderArea*>::iterator it = renderAreas.begin();
}

void MainWindow::readFromDevice() {
    /*
    unsigned char* tmp = tRead->data; 
    for (int i = 0; i < 6; i++) {
        qDebug() << "tmp[i]: " << tmp[i];
        inbytes[i] = tmp[i];
        qDebug() << "inbytes[i]: " << inbytes[i] << ", ";
    }
    if (inbytes[0] == 144) { // need set to more detail         
        setColor(map[inbytes[1]], QColor(255, 255, 0));
        int index = sources.size();
        if (inbytes[2] > 0) {
            Phonon::MediaSource source(mKeySong[inbytes[1]]);
            sources.append(source);
        }
        qDebug() << "sources size: " << sources.size();
        //addFiles(); this step is successful.
        if (!sources.isEmpty()) {
            metaInformationResolver->setCurrentSource(sources.at(index));
            //qDebug() << "sources.at(0): " << metaInformationResolver->currentSource().fileName();  
            mediaObject->setCurrentSource(metaInformationResolver->currentSource()); // totalTime() in milliseconds
        }
        // try light LED on: correspond to stateChange
        
        qDebug() << "got here before paint color";
        idol(1);  // need to change this one to sth else
        setColor(map[inbytes[1]], QColor(255, 255, 255));
    }
*/
}
/*
void MainWindow::stopPlayingSong() {
    pthread->playStop();
    setColor(map[inbytes[1]], QColor(255, 255, 255));
}

void MainWindow::playSong(QString s) {
    if (pthread == NULL) {
        pthread = new playThread(this);   // maybe need to be global
    } else {   // if could NOT do the 3rd operation is because of this, I may check thread pause/quit maybe
        pthread->quit();
        pthread = new playThread(this);   // maybe need to be global
    }
    pthread->setSongName(s);
    //connect(pthread, &playThread::finished, pthread, &playThread::deleteLater);   // still causing crash, but why?
    pthread->start();
}
*/
void MainWindow::idol(int x) {
    QEventLoop loop;
    QTimer::singleShot(15000, &loop, SLOT(quit()));// need change method here 
    loop.exec();
    bottomKeys[7]->setStyleSheet("QPushButton{color:red;background-color:rgb(255,255,255)}");
}

void MainWindow::setHeight(QPlainTextEdit *edit, int nRows) { 
    QFontMetrics m (edit -> font()) ;
    int RowHeight = m.lineSpacing() ;
    edit->setFixedHeight(nRows * RowHeight) ;
}

void MainWindow::addFiles() {
    // add filter, supports .wav, .mp3 & .wma file types
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Music Files"), QDesktopServices::storageLocation(QDesktopServices::MusicLocation));
    //QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Music Files"), "../", "music(*.mp3 *.wma *.wav)");
    if (files.isEmpty()) return;
    int index = sources.size();
    foreach (QString string, files) {
        Phonon::MediaSource source(string);
        sources.append(source);
    }
    if (!sources.isEmpty()) {
        metaInformationResolver->setCurrentSource(sources.at(index));
        //metaInformationResolver->setCurrentSource(sources.at(0));
        mediaObject->setCurrentSource(metaInformationResolver->currentSource());
    }
}

void MainWindow::stateChanged(Phonon::State newState, Phonon::State /* oldState */) {
    switch (newState) {
    case Phonon::ErrorState:
        if (mediaObject->errorType() == Phonon::FatalError) 
            QMessageBox::warning(this, tr("Fatal Error"), mediaObject->errorString());
        else 
            QMessageBox::warning(this, tr("Error"), mediaObject->errorString());
        break;
    case Phonon::PlayingState:
        playAction->setEnabled(false);
        pauseAction->setEnabled(true);
        stopAction->setEnabled(true);
        break;
    case Phonon::StoppedState:
        stopAction->setEnabled(false);
        playAction->setEnabled(true);
        pauseAction->setEnabled(false);
        timeLcd->display("00:00");
        break;
    case Phonon::PausedState:
        pauseAction->setEnabled(false);
        stopAction->setEnabled(true);
        playAction->setEnabled(true);
        break;
    case Phonon::BufferingState: // LoadingState
        break;
    default:
        ;
    }
}

void MainWindow::tick(qint64 time) {
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
    timeLcd->display(displayTime.toString("mm:ss"));
}

void MainWindow::tableClicked(int row, int /* column */) {
    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;
    mediaObject->stop();
    mediaObject->clearQueue();
    if (row >= sources.size()) return;
    qDebug() << "sources size TableClicked: " << sources.size();
    mediaObject->setCurrentSource(sources[row]);
    if (wasPlaying) {        
            qDebug() << "got here for playing....";
            mediaObject->play();
    } else    
        mediaObject->stop();
}

void MainWindow::sourceChanged(const Phonon::MediaSource &source) {
    musicTable->selectRow(sources.indexOf(source));
    timeLcd->display("00:00");
}

void MainWindow::metaStateChanged(Phonon::State newState, Phonon::State /* oldState */) {
    if (newState == Phonon::ErrorState) {
        QMessageBox::warning(this, tr("Error opening files"), metaInformationResolver->errorString());
        while (!sources.isEmpty() &&
               !(sources.takeLast() == metaInformationResolver->currentSource())) {}  /* loop */;
        return;
    }
    if (newState != Phonon::StoppedState && newState != Phonon::PausedState)
        return;
    if (metaInformationResolver->currentSource().type() == Phonon::MediaSource::Invalid)
        return;
    QMap<QString, QString> metaData = metaInformationResolver->metaData();
    QString title = metaData.value("TITLE");
    if (title == "")
        title = metaInformationResolver->currentSource().fileName();

    QTableWidgetItem *titleItem = new QTableWidgetItem(title);
    titleItem->setFlags(titleItem->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem *artistItem = new QTableWidgetItem(metaData.value("ARTIST"));
    artistItem->setFlags(artistItem->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem *albumItem = new QTableWidgetItem(metaData.value("ALBUM"));
    albumItem->setFlags(albumItem->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem *yearItem = new QTableWidgetItem(metaData.value("DATE"));
    yearItem->setFlags(yearItem->flags() ^ Qt::ItemIsEditable);

    int currentRow = musicTable->rowCount();
    musicTable->insertRow(currentRow);
    musicTable->setItem(currentRow, 0, titleItem);
    musicTable->setItem(currentRow, 1, artistItem);
    musicTable->setItem(currentRow, 2, albumItem);
    musicTable->setItem(currentRow, 3, yearItem);
    if (musicTable->selectedItems().isEmpty()) {
        musicTable->selectRow(0);
        mediaObject->setCurrentSource(metaInformationResolver->currentSource());
    }
    Phonon::MediaSource source = metaInformationResolver->currentSource();
    int index = sources.indexOf(metaInformationResolver->currentSource()) + 1;
    if (sources.size() > index) {
        metaInformationResolver->setCurrentSource(sources.at(index));
    } else {    
        musicTable->resizeColumnsToContents();
        if (musicTable->columnWidth(0) > 200)
            musicTable->setColumnWidth(0, 200);
    }
}

void MainWindow::aboutToFinish() {
    int index = sources.indexOf(mediaObject->currentSource()) + 1;
    if (sources.size() > index) {
        mediaObject->enqueue(sources.at(index));
    }
}

void MainWindow::about() {
    QMessageBox::information(this, tr("About Music Player"), tr("The Music Player example shows how to use Phonon - the multimedia"
                                                                " framework that comes with Qt - to create a simple music player."));
}

MainWindow::~MainWindow() {
}
