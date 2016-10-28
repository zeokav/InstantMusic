#ifndef CONNECTEDWINDOW_H
#define CONNECTEDWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QStringListModel>
#include <QString>
#include <QDir>
#include <QtMultimedia/QMediaPlayer>
#include "../common.hpp"

namespace Ui {
class ConnectedWindow;
}

class ConnectedWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnectedWindow(server_info serv, QWidget *parent = 0);
    ~ConnectedWindow();

private slots:
    void fetch_music(QModelIndex);
    void list_music();
    void kill_client();

private:
    Ui::ConnectedWindow *ui;
    server_info s_info;
    void setup_music_player(QString);
    int download_song(QString);

};

#endif // CONNECTEDWINDOW_H
