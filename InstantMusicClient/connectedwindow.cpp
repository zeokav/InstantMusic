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

void ConnectedWindow::fetch_music()
{
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
}
