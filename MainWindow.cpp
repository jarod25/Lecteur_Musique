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

MainWindow::~MainWindow() {

}

void MainWindow::setupUI() {
    songTable = new QTableWidget(this);
    songTable->setColumnCount(2);
    songTable->setHorizontalHeaderLabels(QStringList() << "Song" << "Artist");
    songTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    songTable->verticalHeader()->setVisible(false);
    songTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    songTable->setSelectionMode(QAbstractItemView::SingleSelection);
    songTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    songTable->setAlternatingRowColors(true);
    songTable->setShowGrid(false);
    songTable->setStyleSheet("QTableView {selection-background-color: #b8d1f3;}");

    addSongButton = new QPushButton("Add Song", this);
    addSongsButton = new QPushButton("Add Songs", this);
    createPlaylistButton = new QPushButton("Create Playlist", this);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(addSongButton);
    buttonLayout->addWidget(addSongsButton);
    buttonLayout->addWidget(createPlaylistButton);
    buttonLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(songTable);
    mainLayout->addLayout(buttonLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::setupConnections() {
    connect(addSongButton, &QPushButton::clicked, this, &MainWindow::addSong);
    connect(addSongsButton, &QPushButton::clicked, this, &MainWindow::addSongs);
    connect(createPlaylistButton, &QPushButton::clicked, this, &MainWindow::createPlaylist);
}

void MainWindow::addSong() {
    QString song = QInputDialog::getText(this, "Add Song", "Song:");
    if (song.isEmpty()) {
        return;
    }

    QString artist = QInputDialog::getText(this, "Add Song", "Artist:");
    if (artist.isEmpty()) {
        return;
    }

    int row = songTable->rowCount();
    songTable->insertRow(row);
    songTable->setItem(row, 0, new QTableWidgetItem(song));
    songTable->setItem(row, 1, new QTableWidgetItem(artist));
}

void MainWindow::addSongs() {
    QStringList files = QFileDialog::getOpenFileNames(this, "Add Songs", "", "MP3 Files (*.mp3)");
    if (files.isEmpty()) {
        return;
    }

    for (const QString &file : files) {
        QFileInfo fileInfo(file);
        int row = songTable->rowCount();
        songTable->insertRow(row);
        songTable->setItem(row, 0, new QTableWidgetItem(fileInfo.baseName()));
        songTable->setItem(row, 1, new QTableWidgetItem("Unknown"));
    }
}

void MainWindow::createPlaylist() {
    QString playlist = QInputDialog::getText(this, "Create Playlist", "Playlist:");
    if (playlist.isEmpty()) {
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Create Playlist", playlist + ".m3u", "M3U Playlist (*.m3u)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "Unable to create playlist file.");
        return;
    }

    QTextStream stream(&file);
    for (int row = 0; row < songTable->rowCount(); ++row) {
        stream << songTable->item(row, 0)->text() << " - " << songTable->item(row, 1)->text() << endl;
    }

    file.close();
}
