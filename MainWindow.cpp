#include "MainWindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <iostream>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <cstdio>
#include <QMediaPlaylist>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setupUI();
    resize(1366, 768);
    setupConnections();
}

MainWindow::~MainWindow() {

}

void MainWindow::setupUI() {
    /* Playlist Table */
    playlistTable = new QTableWidget(this);
    playlistTable->setColumnCount(2);
    playlistTable->setHorizontalHeaderLabels(QStringList() << "Playlist" << "Durée");
    playlistTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    playlistTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    playlistTable->setSelectionMode(QAbstractItemView::SingleSelection);
    playlistTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    playlistTable->setAlternatingRowColors(true);
    playlistTable->setShowGrid(false);
    playlistTable->setStyleSheet("QTableView {selection-background-color: #b8d1f3;}");

    /* Song Table */
    songTable = new QTableWidget(this);
    songTable->setColumnCount(3);
    songTable->setHorizontalHeaderLabels(QStringList() << "Titre" << "Artiste" << "Durée");
    songTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    songTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    songTable->setSelectionMode(QAbstractItemView::SingleSelection);
    songTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    songTable->setAlternatingRowColors(true);
    songTable->setShowGrid(false);
    songTable->setStyleSheet("QTableView {selection-background-color: #b8d1f3;}");

    /* Create Instance */
    ImportSongsButton = new QPushButton("Importer des chansons", this);
    createPlaylistButton = new QPushButton("Créer une playlist", this);
    previousButton = new QPushButton("Previous Song", this);
    playButton = new QPushButton("Play Song", this);
    nextButton = new QPushButton("Next Song", this);

    /* Button Layout */
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(ImportSongsButton);
    buttonLayout->addWidget(createPlaylistButton);
    buttonLayout->addStretch();

    /* Play Layout */
    QHBoxLayout *playLayout = new QHBoxLayout;
    playLayout->addWidget(previousButton);
    playLayout->addWidget(playButton);
    playLayout->addWidget(nextButton);

    /* Table Layout */
    QHBoxLayout *tableLayout = new QHBoxLayout;
    tableLayout->addWidget(playlistTable);
    tableLayout->addWidget(songTable);

    /* Table Layout */
    QHBoxLayout *CentralLayout = new QHBoxLayout;
    CentralLayout->addLayout(tableLayout);
    CentralLayout->addLayout(buttonLayout);

    /* Bottom Layout */
    QVBoxLayout *bottomLayout = new QVBoxLayout;
    bottomLayout->addLayout(playLayout);

    /* Main Layout */
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(CentralLayout);
    mainLayout->addLayout(bottomLayout);

    /* Central Widget */
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::setupConnections() {
    connect(ImportSongsButton, &QPushButton::clicked, this, &MainWindow::importSongs);
    connect(createPlaylistButton, &QPushButton::clicked, this, &MainWindow::createPlaylist);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::playSong);
    connect(previousButton, &QPushButton::clicked, this, &MainWindow::previousSong);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::nextSong);
}

void MainWindow::importSongs() {
    QStringList files = QFileDialog::getOpenFileNames(this, "Ajouter des chansons", "",
                                                      "Fichiers audio (*.mp3 *.wav *.ogg)");
    if (files.isEmpty()) {
        return;
    }

    for (const QString &file: files) {
        QFileInfo fileInfo(file);
        int row = songTable->rowCount();

        TagLib::FileRef f(file.toStdString().c_str());
        QString titre = QString::fromStdString(f.tag()->title().toCString(true));
        QString artiste = QString::fromStdString(f.tag()->artist().toCString(true));
        int duree = f.audioProperties()->length();

        int seconds = duree;
        int minutes = seconds / 60;
        int remainingSeconds = seconds % 60;

        char buffer[20];
        std::sprintf(buffer, "%d:%02d", minutes, remainingSeconds);

        songTable->insertRow(row);
        songTable->setItem(row, 0, new QTableWidgetItem(titre));
        songTable->setItem(row, 1, new QTableWidgetItem(artiste));
        songTable->setItem(row, 2, new QTableWidgetItem(QString::fromUtf8(buffer)));
    }
}

void MainWindow::createPlaylist() {
    QString playlistName = QInputDialog::getText(this, "Nom de la playlist", "Entrer le nom de la playlist");
    if (playlistName.isEmpty()) {
        return;
    }
    playlistTable->insertRow(playlistTable->rowCount());
    playlistTable->setItem(playlistTable->rowCount() - 1, 0, new QTableWidgetItem(playlistName));
    playlistTable->setItem(playlistTable->rowCount() - 1, 1, new QTableWidgetItem("0"));
}

void MainWindow::addSongsToPlaylist() {

}

void MainWindow::showPlaylist() {

}

void MainWindow::playSong() {
    if (songTable->currentItem() == nullptr) {
        return;
    }
    QMediaPlayer *player = new QMediaPlayer(this);
    QString songPath = songTable->currentItem()->text();
    player->setMedia(QUrl::fromLocalFile(songPath));
    player->play();
    playButton->setText("Pause");
    connect(playButton, &QPushButton::clicked, this, &MainWindow::pauseSong);
}

void MainWindow::pauseSong() {
    if (songTable->currentItem() == nullptr) {
        return;
    }
    QMediaPlayer *player = new QMediaPlayer(this);
    player->stop();
    playButton->setText("Play");
    disconnect(playButton, &QPushButton::clicked, this, &MainWindow::pauseSong);
}

void MainWindow::playPlaylist() {

}

void MainWindow::previousSong() {

}

void MainWindow::nextSong() {

}