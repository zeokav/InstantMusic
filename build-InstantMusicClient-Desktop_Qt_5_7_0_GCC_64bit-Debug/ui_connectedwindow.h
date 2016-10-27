/********************************************************************************
** Form generated from reading UI file 'connectedwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTEDWINDOW_H
#define UI_CONNECTEDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectedWindow
{
public:
    QAction *actionDisconnect;
    QAction *actionExit;
    QAction *actionAbout_us;
    QWidget *centralwidget;
    QListView *listView;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuSettings;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ConnectedWindow)
    {
        if (ConnectedWindow->objectName().isEmpty())
            ConnectedWindow->setObjectName(QStringLiteral("ConnectedWindow"));
        ConnectedWindow->resize(800, 600);
        actionDisconnect = new QAction(ConnectedWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionExit = new QAction(ConnectedWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout_us = new QAction(ConnectedWindow);
        actionAbout_us->setObjectName(QStringLiteral("actionAbout_us"));
        centralwidget = new QWidget(ConnectedWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        listView = new QListView(centralwidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(520, 120, 256, 411));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 781, 20));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(510, 90, 191, 20));
        QFont font;
        font.setPointSize(12);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(700, 90, 71, 22));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        pushButton->setFont(font1);
        ConnectedWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ConnectedWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 19));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        ConnectedWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ConnectedWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ConnectedWindow->setStatusBar(statusbar);

        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuSettings->addAction(actionDisconnect);
        menuSettings->addAction(actionExit);
        menuAbout->addAction(actionAbout_us);

        retranslateUi(ConnectedWindow);

        QMetaObject::connectSlotsByName(ConnectedWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ConnectedWindow)
    {
        ConnectedWindow->setWindowTitle(QApplication::translate("ConnectedWindow", "MainWindow", 0));
        actionDisconnect->setText(QApplication::translate("ConnectedWindow", "Disconnect", 0));
        actionExit->setText(QApplication::translate("ConnectedWindow", "Exit ", 0));
        actionAbout_us->setText(QApplication::translate("ConnectedWindow", "About us...", 0));
        label->setText(QApplication::translate("ConnectedWindow", "Connected to server:", 0));
        label_2->setText(QApplication::translate("ConnectedWindow", "Server file listing", 0));
        pushButton->setText(QApplication::translate("ConnectedWindow", "Refresh", 0));
        menuSettings->setTitle(QApplication::translate("ConnectedWindow", "Settings", 0));
        menuAbout->setTitle(QApplication::translate("ConnectedWindow", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class ConnectedWindow: public Ui_ConnectedWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTEDWINDOW_H
