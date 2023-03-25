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
#include <QList>


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setupUI();
    resize(1366, 768);
    setWindowTitle("Music Player");
    setupConnections();
}

MainWindow::~MainWindow() {

}

void MainWindow::setupUI() {

    /* Create Instance */
    importedSong = new QMediaPlaylist();
    player = new QMediaPlayer(this);
    importSongsButton = new QPushButton("Importer des chansons", this);
    createPlaylistButton = new QPushButton("Créer une playlist", this);
    previousButton = new QPushButton("Previous Song", this);
    playButton = new QPushButton("Play Song", this);
    nextButton = new QPushButton("Next Song", this);
    stopButton = new QPushButton("Stop Song", this);
    playlistTable = new QTableWidget(this);
    importedSongTable = new QTableWidget(this);
    playlistSongTable = new QTableWidget(this);

    /* Playlist Table */
    playlistTable->setColumnCount(2);
    playlistTable->setHorizontalHeaderLabels(QStringList() << "Playlist" << "Durée");
    playlistTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    playlistTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    playlistTable->setSelectionMode(QAbstractItemView::SingleSelection);
    playlistTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    playlistTable->setAlternatingRowColors(true);
    playlistTable->setShowGrid(false);
    playlistTable->setStyleSheet("QTableView {selection-background-color: #b8d1f3;}");
    playlistTable->setColumnWidth(0, 50);

    /* Imported Songs Table */
    importedSongTable->setColumnCount(4);
    importedSongTable->setHorizontalHeaderLabels(QStringList() << "Titre" << "Artiste" << "Durée");
    importedSongTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    importedSongTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    importedSongTable->setSelectionMode(QAbstractItemView::SingleSelection);
    importedSongTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    importedSongTable->setAlternatingRowColors(true);
    importedSongTable->setShowGrid(false);
    importedSongTable->setStyleSheet("QTableView {selection-background-color: #b8d1f3;}");
    importedSongTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    importedSongTable->setColumnHidden(3, true);

    /* Playlist Songs Table */
    playlistSongTable->setColumnCount(4);
    playlistSongTable->setHorizontalHeaderLabels(QStringList() << "Titre" << "Artiste" << "Durée");
    playlistSongTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    playlistSongTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    playlistSongTable->setSelectionMode(QAbstractItemView::SingleSelection);
    playlistSongTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    playlistSongTable->setAlternatingRowColors(true);
    playlistSongTable->setShowGrid(false);
    playlistSongTable->setStyleSheet("QTableView {selection-background-color: #b8d1f3;}");
    playlistSongTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    playlistSongTable->setColumnHidden(3, true);

    /* Imported Songs Playlist */
    importedSong->setObjectName("Titres importés");
    playlistTable->insertRow(playlistTable->rowCount());
    playlistTable->setItem(0, 0, new QTableWidgetItem("Titres importés"));
    playlistTable->setItem(0, 1, new QTableWidgetItem("0:00"));

    /* Button Layout */
    buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(importSongsButton);
    buttonLayout->addWidget(createPlaylistButton);
    buttonLayout->addStretch();
    buttonLayout->setContentsMargins(0, 25, 0, 0);

    /* Play Layout */
    playLayout = new QHBoxLayout();
    playLayout->addWidget(previousButton);
    playLayout->addWidget(stopButton);
    playLayout->addWidget(playButton);
    playLayout->addWidget(nextButton);


    /* Song Layout */
    QLabel *songLabel = new QLabel("Chansons", this);
    songLayout = new QVBoxLayout();
    songLayout->addWidget(songLabel);
    songLayout->addWidget(importedSongTable);
    songLabel->setStyleSheet("QLabel { font: bold; }");
    songLabel->setAlignment(Qt::AlignHCenter);

    /* Playlist Layout */
    QLabel *playlistLabel = new QLabel("Playlists", this);
    playlistLayout = new QVBoxLayout();
    playlistLayout->addWidget(playlistLabel);
    playlistLayout->addWidget(playlistTable);
    playlistLabel->setStyleSheet("QLabel { font: bold; }");
    playlistLabel->setAlignment(Qt::AlignHCenter);

    /* Table Layout */
    tableLayout = new QHBoxLayout();
    tableLayout->addLayout(playlistLayout);
    tableLayout->addLayout(songLayout);

    /* Central Layout */
    centralLayout = new QHBoxLayout();
    centralLayout->addLayout(tableLayout);
    centralLayout->addLayout(buttonLayout);

    /* Main Layout */
    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(centralLayout);
    mainLayout->addLayout(playLayout);

    /* Central Widget */
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::setupConnections() {
    connect(importSongsButton, &QPushButton::clicked, this, &MainWindow::importSongs);
    connect(createPlaylistButton, &QPushButton::clicked, this, &MainWindow::createPlaylist);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::playSong);
    connect(previousButton, &QPushButton::clicked, this, &MainWindow::previousSong);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::nextSong);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stopSong);
    connect(importedSongTable, &QTableWidget::itemDoubleClicked, this, &MainWindow::playSong);
    connect(playlistTable, &QTableWidget::itemDoubleClicked, this, &MainWindow::showPlaylist);
}

void MainWindow::importSongs() {
    QStringList musicLinks;
    QStringList files = QFileDialog::getOpenFileNames(this, "Ajouter des chansons", "",
                                                      "Fichiers audio (*.mp3 *.wav *.ogg)");
    if (files.isEmpty()) {
        return;
    }
    int totalMinutes = 0;
    int totalSeconds = 0;
    for (const QString &file: files) {
        musicLinks.append(file);

        QFileInfo fileInfo(file);
        int row = importedSongTable->rowCount();

        TagLib::FileRef f(file.toStdString().c_str());
        QString titre = QString::fromStdString(f.tag()->title().toCString(true));
        QString artiste = QString::fromStdString(f.tag()->artist().toCString(true));
        int duree = f.audioProperties()->length();

        int seconds = duree;
        int minutes = seconds / 60;
        int remainingSeconds = seconds % 60;

        char buffer[20];
        std::sprintf(buffer, "%d:%02d", minutes, remainingSeconds);

        importedSongTable->insertRow(row);
        importedSongTable->setItem(row, 0, new QTableWidgetItem(titre));
        importedSongTable->setItem(row, 1, new QTableWidgetItem(artiste));
        importedSongTable->setItem(row, 2, new QTableWidgetItem(QString::fromUtf8(buffer)));
        importedSongTable->setItem(row, 3, new QTableWidgetItem(file));

        importedSong->addMedia(QUrl::fromLocalFile(file));
        totalMinutes += minutes;
        totalSeconds += remainingSeconds;
        totalMinutes += totalSeconds / 60;
        totalSeconds = totalSeconds % 60;
    }
    char buffer[20];
    std::sprintf(buffer, "%d:%02d", totalMinutes, totalSeconds);
    playlistTable->setItem(0, 1, new QTableWidgetItem(QString::fromUtf8(buffer)));
}

void MainWindow::createPlaylist() {
    QString playlistName = QInputDialog::getText(this, "Nom de la playlist", "Entrer le nom de la playlist");
    if (playlistName.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un nom de playlist");
        return;
    }
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->setObjectName(playlistName);
    playlistTable->insertRow(playlistTable->rowCount());
    playlistTable->setItem(playlistTable->rowCount() - 1, 0, new QTableWidgetItem(playlistName));
    playlistTable->setItem(playlistTable->rowCount() - 1, 1, new QTableWidgetItem("0:00"));
}

void MainWindow::addToPlaylist() {
    if (playlistTable->selectedItems().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une playlist");
        return;
    } else {
        QDialog *dialog = new QDialog(this);
        dialog->setWindowTitle("Ajouter des chansons à la liste de lecture");
        dialog->setMinimumSize(600, 400);

        QTableWidget *table = new QTableWidget(dialog);
        table->setRowCount(importedSongTable->rowCount());
        table->setColumnCount(importedSongTable->columnCount() + 1);
        table->setHorizontalHeaderItem(0, new QTableWidgetItem("Titre"));
        table->setHorizontalHeaderItem(1, new QTableWidgetItem("Artiste"));
        table->setHorizontalHeaderItem(2, new QTableWidgetItem("Durée"));
        table->setHorizontalHeaderItem(3, new QTableWidgetItem("Chemin"));
        table->setHorizontalHeaderItem(4, new QTableWidgetItem("Ajouter"));
        table->setColumnHidden(3, true);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        for (int i = 0; i < importedSongTable->rowCount(); i++) {
            for (int j = 0; j < importedSongTable->columnCount(); j++) {
                QTableWidgetItem *item = importedSongTable->item(i, j);
                table->setItem(i, j, new QTableWidgetItem(item->text()));
            }
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setCheckState(Qt::Unchecked);
            table->setItem(i, 4, item);
        }
        QPushButton *button = new QPushButton("Ajouter à la liste de lecture", dialog);
        connect(button, &QPushButton::clicked, [=]() {
            QList<int> selectedRows;
            for (int i = 0; i < table->rowCount(); i++) {
                if (table->item(i, 4)->checkState() == Qt::Checked) {
                    selectedRows.append(i);
                }
            }
            emit addSongsToPlaylist(selectedRows);
            dialog->close();
        });
        QVBoxLayout *layout = new QVBoxLayout(dialog);
        layout->addWidget(table);
        layout->addWidget(button);
        dialog->setLayout(layout);
        dialog->exec();
    }
}

void MainWindow::addSongsToPlaylist(QList<int> selectedRows) {
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->setObjectName(playlistTable->item(playlistTable->currentRow(), 0)->text());
    int totalMinutes = 0;
    int totalSeconds = 0;
    for (int i = 0; i < selectedRows.size(); i++) {
        playlist->addMedia(QUrl::fromLocalFile(importedSongTable->item(selectedRows.at(i), 3)->text()));
        totalMinutes += importedSongTable->item(selectedRows.at(i), 2)->text().split(":").at(0).toInt();
        totalSeconds += importedSongTable->item(selectedRows.at(i), 2)->text().split(":").at(1).toInt();
        totalMinutes += totalSeconds / 60;
        totalSeconds = totalSeconds % 60;
    }
    char buffer[20];
    std::sprintf(buffer, "%d:%02d", totalMinutes, totalSeconds);
    playlistTable->setItem(playlistTable->currentRow(), 1, new QTableWidgetItem(QString::fromUtf8(buffer)));
}

void MainWindow::showPlaylist() {

}

void MainWindow::playSong() {
    if (importedSongTable->currentItem() == nullptr) {
        return;
    }
    if (QMediaPlayer::PausedState == player->state()) {
        player->play();
        player->stateChanged(QMediaPlayer::PlayingState);
        disconnect(playButton, &QPushButton::clicked, this, &MainWindow::playSong);
        connect(playButton, &QPushButton::clicked, this, &MainWindow::pauseSong);
        playButton->setText("Pause Song");
        return;
    } else {
        player->setMedia(QUrl::fromLocalFile(importedSongTable->item(importedSongTable->currentRow(), 3)->text()));
        player->play();
        player->stateChanged(QMediaPlayer::PlayingState);
        disconnect(playButton, &QPushButton::clicked, this, &MainWindow::playSong);
        connect(playButton, &QPushButton::clicked, this, &MainWindow::pauseSong);
        playButton->setText("Pause Song");
    }
}

void MainWindow::pauseSong() {
    player->pause();
    player->stateChanged(QMediaPlayer::PausedState);
    disconnect(playButton, &QPushButton::clicked, this, &MainWindow::pauseSong);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::playSong);
    playButton->setText("Play Song");
}

void MainWindow::stopSong() {
    player->stop();
    player->stateChanged(QMediaPlayer::StoppedState);
    disconnect(playButton, &QPushButton::clicked, this, &MainWindow::pauseSong);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::playSong);
    playButton->setText("Play Song");
}

void MainWindow::playPlaylist() {

}

void MainWindow::previousSong() {

}

void MainWindow::nextSong() {

}