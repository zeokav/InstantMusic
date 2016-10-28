#include "connectedwindow.h"
#include "ui_connectedwindow.h"
#include "entrywindow.h"

ConnectedWindow::ConnectedWindow(server_info serv, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectedWindow)
{
    s_info = serv;
    ui->setupUi(this);
    char address[100];
    strcpy(address, "Connected to address: ");
    strcat(address, inet_ntoa(s_info.serv.sin_addr));
    ui->label->setText(address);
    connect(ui->actionDisconnect, SIGNAL(triggered(bool)), this, SLOT(kill_client()));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(list_music()));
    connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(fetch_music()));
    list_music();
    setup_music_player();
}

ConnectedWindow::~ConnectedWindow()
{
    delete ui;
}

void ConnectedWindow::setup_music_player()
{
    QMediaPlayer *player = new QMediaPlayer;
    QString mediaPath = qApp->applicationDirPath().mid(0, 107).append("/closer.mp3");
    player->setMedia(QUrl::fromLocalFile(mediaPath));
    player->setVolume(50);
    player->play();
}

void ConnectedWindow::fetch_music()
{
    qDebug() << "A song was double clicked";
    QObject *s = sender();
    QObjectList item = s->children();
    for(int i = 0; i<item.size(); i++) {
        qDebug() << item[i]->objectName();
    }
//        // Make request
//        header_block file_head;

//        ::recv(sockfd, (header_block *)&file_head, sizeof(header_block), 0);

//        ui->pushButton->hide();

//        if(!file_head.error_code) {
//            qDebug() << "Header received. File size: " << file_head.filesize;
//            char c[BUFFER_SIZE];
//            int fd = open("./transfers/closer.mp3", O_WRONLY | O_CREAT | O_TRUNC, 0666);
//            int nob;
//            while((nob = ::recv(sockfd, c, BUFFER_SIZE, 0)) > 0) {
//                write(fd, c, nob);
//                if(nob < 2048)
//                    break;
//            }
//            ::close(fd);
//            qDebug() << "File received!";
//        }
//        else {
//             catch_error("HEADER", error_code);
//        }
}

void ConnectedWindow::list_music()
{
    _control ctrl;
    ctrl.command = REQ_LIST;
    ctrl.is_error = 0;
    send(s_info.sockfd, (_control *)&ctrl, sizeof(_control), 0);
    char list_data[BUFFER_SIZE];
    int fd = open("SongList.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    int nob;
    while((nob = ::recv(s_info.sockfd, list_data, BUFFER_SIZE, 0)) > 0) {
        write(fd, list_data, nob);
        if(nob!=BUFFER_SIZE)
            break;
    }

    QString status = "Received: ";
    status.append(QString::number(nob));

    ui->statusbar->showMessage(status);
    ::close(fd);

    QStringList stringList;
    // Assuming listing is in a file, can be modified as needed
    // Cannot find file path

    QFile listing("SongList.txt");
    if(!listing.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "Error", listing.errorString());
    }
    QTextStream textStream(&listing);
    while (true)
    {
        QString line = textStream.readLine();
        if (line.isNull())
            break;
        else
            stringList.append(line); // populate the stringlist
    }

    // Create song model and populate it with stringList
    QStringListModel *model;
    model = new QStringListModel(this);
    model->setStringList(stringList);
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Remove the temporary pipe from the system.
    system("rm SongList.txt");
}

void ConnectedWindow::kill_client()
{
    EntryWindow *ew = new EntryWindow();
    ew->show();
    ew->setWindowTitle("InstantMusic Client");
    this->close();
}
