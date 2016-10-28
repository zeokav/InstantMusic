#ifndef CONNECTEDWINDOW_H
#define CONNECTEDWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QStringListModel>
#include <QString>
//#include <QMediaPlayer>
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
    void fetch_music();
    void list_music();
    void kill_client();
//    void setup_music_player();

private:
    Ui::ConnectedWindow *ui;
    server_info s_info;

};

#endif // CONNECTEDWINDOW_H
