#include "entrywindow.h"
#include "ui_entrywindow.h"
#include <unistd.h>
#include <fcntl.h>
#include <QDebug>
#define MAX 1000

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

    qDebug() << "Test";
    system("mkdir transfers");

    //Write file to transfers folder in the build directory.

    int fd = ::open("./transfers/newfile.txt", O_CREAT | O_WRONLY, 0666);
    if(fd == -1) {
        qDebug() << "Error opening file";
    }
    else {
        char buff[MAX] = "KDS is a test subject";
        int sz;
        if((sz = write(fd, buff,strlen(buff))) > 0) {
            qDebug() << sz<<" bytes written";
        }

        ::close(fd);
        qDebug() << "written to file";

    }

}
