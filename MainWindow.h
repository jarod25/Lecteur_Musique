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

    void playSong();

    void pauseSong();

    void stopSong();

    void showPlaylist();

    void playPlaylist();

    void nextSong();

    void previousSong();

    QTableWidget *songTable;
    QTableWidget *playlistTable;
    QPushButton *ImportSongsButton;
    QPushButton *createPlaylistButton;

    /* Play Button */
    QPushButton *previousButton;
    QPushButton *stopButton;
    QPushButton *playButton;
    QPushButton *nextButton;
};

#endif
