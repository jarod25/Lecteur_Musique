#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


private:
    void setupUI();

    void setupConnections();

    void importSongs();

    void createPlaylist();

    void addSongsToPlaylist();

    void showPlaylist();

    void readSongs();

    void readPlaylist();

    QTableWidget *songTable;
    QTableWidget *playlistTable;
    QPushButton *ImportSongsButton;
    QPushButton *createPlaylistButton;
};

#endif
