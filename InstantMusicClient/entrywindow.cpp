#include "entrywindow.h"
#include "ui_entrywindow.h"
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QDebug>
#include "../common.hpp"


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
    qDebug() << "Button clicked";
    int sockfd;
    struct sockaddr_in serv;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_family = AF_INET;
    serv.sin_port = htons(1234);
    //
    ::connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    qDebug() << "Connection established";

    // Make request
     header_block file_head;

     int head_size = ::recv(sockfd, file_head, sizeof(header_block), 0);
    // if(file_head.)

    char c[BUFFER_SIZE];

    int fd = open("./transfers/closer.mp3", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    int nob;
    while((nob = ::recv(sockfd, c, BUFFER_SIZE, 0)) > 0) {
        qDebug() << "Writing..." << nob;
        write(fd, c, nob);
        if(nob < 2048)
            break;
    }
    ::close(fd);
    qDebug() << "File received!";
    ::close(sockfd);

}
