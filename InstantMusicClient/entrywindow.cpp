#include "entrywindow.h"
#include "ui_entrywindow.h"
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QApplication>
#include <QDebug>
#include "../common.hpp"
#include "connectedwindow.h"


EntryWindow::EntryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EntryWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(button_handle()));
}

EntryWindow::~EntryWindow()
{
    delete ui;
}

void EntryWindow::button_handle()
{

//    int sockfd;
//    struct sockaddr_in serv;
//    sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    serv.sin_addr.s_addr = inet_addr(ui->ip_addr->text().toStdString().c_str());
//    serv.sin_family = AF_INET;
//    serv.sin_port = htons(ui->port_no->text().toInt());

//    ::connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));
//    qDebug() << "Connection established";
}
