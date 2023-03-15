#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QLabel>
#include <QMainWindow>
#include<QPushButton>

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

    QTabWidget *songTable;
    QPushButton *addSongButton;
    QPushButton *addSongsButton;
    QPushButton *createPlaylistButton;
};

#endif
