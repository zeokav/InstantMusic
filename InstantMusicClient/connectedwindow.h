#ifndef CONNECTEDWINDOW_H
#define CONNECTEDWINDOW_H

#include <QMainWindow>

namespace Ui {
class ConnectedWindow;
}

class ConnectedWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnectedWindow(QWidget *parent = 0);
    ~ConnectedWindow();

private slots:
    void fetch_music();

private:
    Ui::ConnectedWindow *ui;

};

#endif // CONNECTEDWINDOW_H
