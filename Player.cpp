#include <QtGui>
#include <QFileDialog>

#include "Player.h"

Player::Player()
    : QObject() {
    
    //moveToThread(this);
    // QObject::moveToThread: Cannot move objects with a parent
    // QObject: Cannot create children for a parent that is in a different thread. (Parent is Player(0x272c680), parent's thread is Player(0x272c680), current thread is QThread(0x2072a00)
    // dummy = new Dummy(this);
    
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    metaInformationResolver = new Phonon::MediaObject(this);

    mediaObject->setTickInterval(1000);
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(stateChanged(Phonon::State,Phonon::State)));
    connect(metaInformationResolver, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(metaStateChanged(Phonon::State,Phonon::State)));
    connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)),
            this, SLOT(sourceChanged(Phonon::MediaSource)));
    connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));

    Phonon::createPath(mediaObject, audioOutput);

    setupActions();
    setupUi();
    timeLcd->display("00:00");

    mKeySong[55] = QString("TheHeavyclip.wav");      // 4 5 6 7 8 9
    mKeySong[57] = QString("Surfin' U.S.A..wav");
    mKeySong[59] = QString("05 Grand Experiment.wav");
    mKeySong[60] = QString("Pharrell_Walliams_-_Happy.wav");
    mKeySong[62] = QString("Karnintro.wav");
    mKeySong[64] = QString("Karn Evil 9_1st Impression-Part 2 copy.wav");
}
/*
void Player::addFiles() {
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Music Files"), QDesktopServices::storageLocation(QDesktopServices::MusicLocation));
    if (files.isEmpty()) return;        
    int index = sources.size();
    foreach (QString string, files) {
        Phonon::MediaSource source(string);
        sources.append(source);
    }
    if (!sources.isEmpty())
        metaInformationResolver->setCurrentSource(sources.at(index));
}
*/
void Player::stateChanged(Phonon::State newState, Phonon::State /* oldState */) {
    switch (newState) {  
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
    case Phonon::BufferingState:
        break;
    default:
        ;
    }
}

void Player::tick(qint64 time) {
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);
    timeLcd->display(displayTime.toString("mm:ss"));
}

void Player::tableClicked(int row, int /* column */) {
    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;
    mediaObject->stop();
    mediaObject->clearQueue();
    if (row >= sources.size()) return;
    mediaObject->setCurrentSource(sources[row]);
    if (wasPlaying)
        mediaObject->play();
    else
        mediaObject->stop();
}

void Player::sourceChanged(const Phonon::MediaSource &source) {
    musicTable->selectRow(sources.indexOf(source));
    timeLcd->display("00:00");
}

void Player::metaStateChanged(Phonon::State newState, Phonon::State /* oldState */) {
    if (newState == Phonon::ErrorState) {
        while (!sources.isEmpty() && !(sources.takeLast() == metaInformationResolver->currentSource())) {}  /* loop */;
        return;
    }
    if (newState != Phonon::StoppedState && newState != Phonon::PausedState) return;
    if (metaInformationResolver->currentSource().type() == Phonon::MediaSource::Invalid) return;
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
        if (musicTable->columnWidth(0) > 300)
            musicTable->setColumnWidth(0, 300);
    }
}

void Player::aboutToFinish() {
    int index = sources.indexOf(mediaObject->currentSource()) + 1;
    if (sources.size() > index) {
        mediaObject->enqueue(sources.at(index));
    }
}

void Player::setupActions() {
    //playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
    playAction = new QAction(this);
    playAction->setShortcut(tr("Crl+P"));
    playAction->setDisabled(true);
    //pauseAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
    pauseAction = new QAction(this);
    pauseAction->setShortcut(tr("Ctrl+A"));
    pauseAction->setDisabled(true);
    //stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
    stopAction = new QAction(this);
    stopAction->setShortcut(tr("Ctrl+S"));
    stopAction->setDisabled(true);
    //nextAction = new QAction(style()->standardIcon(QStyle::SP_MediaSkipForward), tr("Next"), this);
    nextAction = new QAction(this);
    nextAction->setShortcut(tr("Ctrl+N"));
    //previousAction = new QAction(style()->standardIcon(QStyle::SP_MediaSkipBackward), tr("Previous"), this);
    previousAction = new QAction(this);
    previousAction->setShortcut(tr("Ctrl+R"));
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
    //connect(addFilesAction, SIGNAL(triggered()), this, SLOT(addFiles()));
    //connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    //connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void Player::setupUi() {
    QToolBar *bar = new QToolBar;

    bar->addAction(playAction);
    bar->addAction(pauseAction);
    bar->addAction(stopAction);

    //seekSlider = new Phonon::SeekSlider(this);
    seekSlider = new Phonon::SeekSlider();
    seekSlider->setMediaObject(mediaObject);

    //volumeSlider = new Phonon::VolumeSlider(this);
    volumeSlider = new Phonon::VolumeSlider();
    volumeSlider->setAudioOutput(audioOutput);
    volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QLabel *volumeLabel = new QLabel;
    volumeLabel->setPixmap(QPixmap("images/volume.png"));

    QPalette palette;
    palette.setBrush(QPalette::Light, Qt::darkGray);

    timeLcd = new QLCDNumber;
    timeLcd->setPalette(palette);

    QStringList headers;
    headers << tr("Title") << tr("Artist") << tr("Album") << tr("Year");

    musicTable = new QTableWidget(0, 4);
    musicTable->setHorizontalHeaderLabels(headers);
    musicTable->setSelectionMode(QAbstractItemView::SingleSelection);
    musicTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(musicTable, SIGNAL(cellPressed(int,int)), this, SLOT(tableClicked(int,int)));

    QHBoxLayout *seekerLayout = new QHBoxLayout;
    seekerLayout->addWidget(seekSlider);
    seekerLayout->addWidget(timeLcd);

    QHBoxLayout *playbackLayout = new QHBoxLayout;
    playbackLayout->addWidget(bar);
    playbackLayout->addStretch();
    playbackLayout->addWidget(volumeLabel);
    playbackLayout->addWidget(volumeSlider);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(musicTable);
    mainLayout->addLayout(seekerLayout);
    mainLayout->addLayout(playbackLayout);
}
