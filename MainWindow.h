#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QLabel>
#include <QMainWindow>
#include<QPushButton>
#include <QTableWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


private:
    void setupUI();

    void setupConnections();

    void addSong();

    void addSongs();

    void createPlaylist();

    QTableWidget *songTable;
    QPushButton *addSongButton;
    QPushButton *addSongsButton;
    QPushButton *createPlaylistButton;
};

#endif
