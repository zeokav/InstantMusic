#include "connectedwindow.h"
#include "ui_connectedwindow.h"
#include "entrywindow.h"

ConnectedWindow::ConnectedWindow(server_info serv, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectedWindow)
{
    is_playing = false;
    is_destroyed = true;
    s_info = serv;
    ui->setupUi(this);
    char address[100];
    strcpy(address, "Connected to address: ");
    strcat(address, inet_ntoa(s_info.serv.sin_addr));
    ui->label->setText(address);

    // Actions
    connect(ui->actionDisconnect, SIGNAL(triggered(bool)), this, SLOT(kill_client()));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(list_music()));
    connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(fetch_music(QModelIndex)));
    connect(ui->pauseButton, SIGNAL(clicked(bool)), this, SLOT(change_state()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(stop_music()));
    connect(ui->uploadButton, SIGNAL(clicked(bool)), this, SLOT(open_file_browser()));
    connect(this, SIGNAL(progressChanged(int)), this, SLOT(change_bar(int)));

    ui->playedProgress->setValue(0);
    ui->progressBar->hide();
    list_music();
}

ConnectedWindow::~ConnectedWindow()
{
    delete ui;
}

void ConnectedWindow::open_file_browser()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open File"),"~",tr("Mp3 Files (*.mp3)"));
    qDebug() << "File selected " << file_name;
    // fileName has entire file path, upload this to server, might have to change name

    _control ctrl;
    ctrl.command = FUPLOAD;
    ctrl.is_error = 0;
    ::send(s_info.sockfd, (_control *)&ctrl, sizeof(_control), 0);

    int file_name_starts_at = file_name.lastIndexOf("/");
    QString file_name_to_send = file_name.mid(file_name_starts_at + 1);
    qDebug() << "File name " << file_name_to_send;

    int i;
    char filename[NAME_SIZE];
    for(i = 0; i<file_name_to_send.size(); i++) {
        filename[i] = file_name_to_send.at(i).toLatin1();
    }
    filename[i] = '\0';

    ::send(s_info.sockfd, filename, NAME_SIZE, 0);
    int nob;
    int fd = open(file_name.toStdString().c_str(), O_RDONLY);
    if(fd != -1) {
        char buff[BUFFER_SIZE + 1];
        while((nob = read(fd, buff, BUFFER_SIZE)) > 0) {
            if(nob < BUFFER_SIZE) {
                break;
            }
            ::send(s_info.sockfd, buff, BUFFER_SIZE, 0);
        }
        char flush[10];
        ::send(s_info.sockfd, flush, 10, 0);
        qDebug() << "File sent";
    }
    else {
        qDebug() << "LOL";
    }
}

void ConnectedWindow::change_state()
{
    if(is_playing) {
        player->pause();
        is_playing = false;
        ui->pauseButton->setText("Resume");
        ui->statusbar->showMessage("Paused...");
    }
    else {
        if(is_destroyed) {
            ui->statusbar->showMessage("Music was either stopped or not selected!");
        }
        else if(player) {
            player->play();
            is_playing = true;
            ui->pauseButton->setText("Pause");
            ui->statusbar->showMessage("Playing...");
        }
    }
}

void ConnectedWindow::stop_music()
{
    if(is_destroyed) {
        return;
    }
    if(player) {
        is_destroyed = true;        
        is_playing = false;
        ui->label_3->setText("");
        delete player;
        ui->pauseButton->setText("Pause");
        ui->statusbar->showMessage("Stopped music.");
    }
}

void ConnectedWindow::updatebar() {
    qint64 played = 0;
    qint64 ticker = 0;
    qint64 old = 0;
    int seconds = 0;
    while(!is_destroyed) {
        try {
            played = player->position();
            old = ticker;
            ticker = played / 1000;
            if(old != ticker){
                seconds++;
                emit progressChanged(seconds);
            }
        }
        catch(...) {
            return;
        }

    }
}

void ConnectedWindow::change_bar(int seconds) {
    qDebug() << "Seconds: " << seconds;
    int total = player->duration()/1000;
    float percentage = (float)seconds/total;
    ui->playedProgress->setValue(percentage*100);
    ui->playedProgress->repaint();
    QString str = "Seconds: ";
    ui->statusbar->showMessage(str.append(QString::number(seconds)));
}

void ConnectedWindow::setup_music_player(QString song_name)
{
    player = new QMediaPlayer;
    QString mediaPath = qApp->applicationDirPath().append("/transfers/");
    mediaPath.append(song_name);
    player->setMedia(QUrl::fromLocalFile(mediaPath));
    player->setVolume(50);
    player->play();
    QtConcurrent::run(this, &ConnectedWindow::updatebar);
    is_playing = true;
    is_destroyed = false;

    QString label_text = "Currently playing: ";
    label_text.append(song_name);

    ui->label_3->setText(label_text);
}

int ConnectedWindow::download_song(QString song_name)
{
    // Make request
    char file_name[NAME_SIZE];
    int i;
    for(i = 0; i<song_name.size(); i++) {
        file_name[i] = song_name.at(i).toLatin1();
    }
    file_name[i] = '\0';

    qDebug() << file_name;

    header_block file_head;

    send(s_info.sockfd, file_name, NAME_SIZE, 0);
    ::recv(s_info.sockfd, (header_block *)&file_head, sizeof(header_block), 0);

    if(!file_head.error_code) {
        ui->progressBar->show();
        ui->progressBar->setValue(0);
        qDebug() << "Header received. File size: " << file_head.filesize;
        char c[BUFFER_SIZE];
        system("mkdir transfers");
        QString path = "./transfers/";
        path.append(song_name);
        int fd = open(path.toStdString().c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
        int nob;
        int received = 0;
        int percentage;
        int limit = 10;
        while((nob = ::recv(s_info.sockfd, c, BUFFER_SIZE, 0)) > 0) {
            write(fd, c, nob);
            received += nob;
            percentage = (received/file_head.filesize)*100;
            if(percentage > limit) {
                ui->progressBar->setValue(percentage);
                ui->progressBar->repaint();
            }
            if(received >= file_head.filesize)
                break;
        }
        ui->progressBar->hide();
        ::close(fd);
        qDebug() << "File received!";
        return 1;
    }
    else {
        qDebug() << "Error";
        return -1;
    }
}

void ConnectedWindow::fetch_music(QModelIndex index)
{
    if(!is_destroyed) {
        stop_music();
    }
    QString song_name = index.data().toString();
    QString message(song_name);
    message.prepend("Selected: ");
    ui->statusbar->showMessage(message);

    _control ctrl;
    ctrl.command = REQ_FILE;
    ctrl.is_error = 0;
    send(s_info.sockfd, (_control *)&ctrl, sizeof(_control), 0);
    int is_downloaded = download_song(song_name);
    if(is_downloaded == -1) {
        QMessageBox::information(0, "Error", "Could not open file!");
    }
    else {
        setup_music_player(song_name);
    }

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
        if(nob != BUFFER_SIZE)
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
    ::close(s_info.sockfd);
    EntryWindow *ew = new EntryWindow();
    ew->show();
    ew->setWindowTitle("InstantMusic Client");
    this->close();
}
