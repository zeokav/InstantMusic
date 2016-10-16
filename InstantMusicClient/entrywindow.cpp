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

    int sockfd;
    struct sockaddr_in serv;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_addr.s_addr = inet_addr(ui->ip_addr->text());
    serv.sin_family = AF_INET;
    serv.sin_port = htons(ui->port_no->text());
//    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
//    serv.sin_family = AF_INET;
//    serv.sin_port = htons(1234);

//    ::connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));
//    qDebug() << "Connection established";

//    // Make request
//    header_block file_head;

//    ::recv(sockfd, (header_block *)&file_head, sizeof(header_block), 0);

//    ui->pushButton->hide();

//    if(!file_head.error_code) {
//        qDebug() << "Header received. File size: " << file_head.filesize;
//        char c[BUFFER_SIZE];
//        int fd = open("./transfers/closer.mp3", O_WRONLY | O_CREAT | O_TRUNC, 0666);
//        int nob;
//        while((nob = ::recv(sockfd, c, BUFFER_SIZE, 0)) > 0) {
//            write(fd, c, nob);
//            if(nob < 2048)
//                break;
//        }
//        ::close(fd);
//        qDebug() << "File received!";
//    }
//    else {
//         catch_error("HEADER", error_code);
//    }

//    ::close(sockfd);

}
