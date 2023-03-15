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

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setupUI();
    setupConnections();
}

void MainWindow::setupUI() {
    songTable = new QTableWidget(this);
    addSongButton = new QPushButton(tr("Ajouter une chanson"), this);
    addSongsButton = new QPushButton(tr("Ajouter plusieurs chansons"), this);
    createPlaylistButton = new QPushButton(tr("Créer une playlist"), this);

    setCentralWidget(songTable);
    statusBar();
    songTable->setColumnCount(4);
    songTable->setHorizontalHeaderLabels(QStringList() << "Titre" << "Artiste" << "Album" << "Fichier");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(addSongButton, 0, 0);
    layout->addWidget(addSongsButton, 0, 1);
    layout->addWidget(createPlaylistButton, 0, 2);
    layout->addWidget(songTable, 1, 0, 1, 3);
    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
}

void MainWindow::setupConnections() {
    connect(addSongButton, &QPushButton::clicked, this, &MainWindow::addSong);
    connect(addSongsButton, &QPushButton::clicked, this, &MainWindow::addSongs);
    connect(createPlaylistButton, &QPushButton::clicked, this, &MainWindow::createPlaylist);
}

void MainWindow::addSong() {
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Sélectionnez un fichier audio"), QString(),
                                                          tr("Fichiers audio (*.mp3 *.wav *.ogg)"));

    foreach(QString
    fileName, fileNames) {
        QFileInfo fileInfo(fileName);
        int row = songTable->rowCount();
        songTable->insertRow(row);
        songTable->setItem(row, 0, new QTableWidgetItem(fileInfo.completeBaseName()));
        songTable->setItem(row, 1, new QTableWidgetItem("Artiste inconnu"));
        songTable->setItem(row, 2, new QTableWidgetItem("Album inconnu"));
        songTable->setItem(row, 3, new QTableWidgetItem(fileInfo.absoluteFilePath()));
    }
}

void MainWindow::addSongs() {
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Sélectionnez un ou plusieurs fichiers audio"),
                                                          QString(), tr("Fichiers audio (*.mp3 *.wav *.ogg)"));

    foreach(QString
    fileName, fileNames) {
        QFileInfo fileInfo(fileName);
        int row = songTable->rowCount();
        songTable->insertRow(row);
        songTable->setItem(row, 0, new QTableWidgetItem(fileInfo.completeBaseName()));
        songTable->setItem(row, 1, new QTableWidgetItem("Artiste inconnu"));
        songTable->setItem(row, 2, new QTableWidgetItem("Album inconnu"));
        songTable->setItem(row, 3, new QTableWidgetItem(fileInfo.absoluteFilePath()));
    }
}

void MainWindow::createPlaylist() {
    QString playlistName = QInputDialog::getText(this, tr("Nouvelle playlist"), tr("Nom de la playlist : "));

    if (!playlistName.isEmpty()) {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer la playlist"), QString(),
                                                        tr("Playlist (*.m3u)"));

        if (!fileName.isEmpty()) {
            QFile playlistFile(fileName);
            if (playlistFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream stream(&playlistFile);
                stream << "#EXTM3U\n";
                for (int i = 0; i < songTable->rowCount(); i++) {
                    QString filePath = songTable->item(i, 3)->text();
                    stream << "#EXTINF:0," << songTable->item(i, 0)->text() << "\n";
                    stream << filePath << "\n";
                }
                playlistFile.close();
            }
        }
    }
}


