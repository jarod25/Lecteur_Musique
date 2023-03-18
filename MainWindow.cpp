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

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setupUI();
    setupConnections();
}

MainWindow::~MainWindow() {

}

void MainWindow::setupUI() {
    songTable = new QTableWidget(this);
    songTable->setColumnCount(3);
    songTable->setHorizontalHeaderLabels(QStringList() << "Chanson" << "Artiste" << "Durée");
    songTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    songTable->verticalHeader()->setVisible(false);
    songTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    songTable->setSelectionMode(QAbstractItemView::SingleSelection);
    songTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    songTable->setAlternatingRowColors(true);
    songTable->setShowGrid(false);
    songTable->setStyleSheet("QTableView {selection-background-color: #b8d1f3;}");

    ImportSongsButton = new QPushButton("Importer des chansons", this);
    createPlaylistButton = new QPushButton("Créer une playlist", this);

    playlistTable = new QTableWidget(this);
    playlistTable->setColumnCount(2);
    playlistTable->setHorizontalHeaderLabels(QStringList() << "Playlist" << "Durée");
    playlistTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    playlistTable->verticalHeader()->setVisible(false);
    playlistTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    playlistTable->setSelectionMode(QAbstractItemView::SingleSelection);
    playlistTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    playlistTable->setAlternatingRowColors(true);
    playlistTable->setShowGrid(false);
    playlistTable->setStyleSheet("QTableView {selection-background-color: #b8d1f3;}");
    playlistTable->setColumnWidth(0, 100);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(ImportSongsButton);
    buttonLayout->addWidget(createPlaylistButton);
    buttonLayout->addStretch();

    QHBoxLayout *playlistLayout = new QHBoxLayout;
    playlistLayout->addWidget(playlistTable);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(playlistLayout);
    mainLayout->addWidget(songTable);
    mainLayout->addLayout(buttonLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::setupConnections() {
    connect(ImportSongsButton, &QPushButton::clicked, this, &MainWindow::importSongs);
    connect(createPlaylistButton, &QPushButton::clicked, this, &MainWindow::createPlaylist);
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

void MainWindow::readSongs() {

}

void MainWindow::readPlaylist() {

}