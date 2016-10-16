#include "connectedwindow.h"
#include "ui_connectedwindow.h"

ConnectedWindow::ConnectedWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectedWindow)
{
    ui->setupUi(this);
}

ConnectedWindow::~ConnectedWindow()
{
    delete ui;
}
