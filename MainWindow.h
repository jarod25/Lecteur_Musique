#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public
    slots:
        void addSongsToPlaylist(QList < int > selectedRows);

private:

    QMap<QString, QMediaPlaylist*> playlists;

    void setupUI();

    void setupConnections();

    void importSongs();

    void createPlaylist();

    void addToPlaylist();

    void playSong();

    void pauseSong();

    void stopSong();

    void showPlaylist();

    void playSongPlaylist();

    void nextSong();

    void previousSong();

    void playPlaylist();

    void pausePlaylist();

    QTableWidget *importedSongTable;
    QTableWidget *playlistSongTable;
    QTableWidget *playlistTable;
    QPushButton *importSongsButton;
    QPushButton *createPlaylistButton;
    QPushButton *playPlaylistButton;
    QPushButton *previousButton;
    QPushButton *stopButton;
    QPushButton *playButton;
    QPushButton *nextButton;
    QPushButton *addSongButton;
    QMediaPlayer *player;
    QMediaPlaylist *importedSong;
    QVBoxLayout *buttonLayout;
    QHBoxLayout *playLayout;
    QVBoxLayout *songLayout;
    QVBoxLayout *playlistLayout;
    QHBoxLayout *tableLayout;
    QHBoxLayout *centralLayout;
    QVBoxLayout *mainLayout;
    QWidget *centralWidget;
};

#endif
