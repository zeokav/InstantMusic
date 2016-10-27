/********************************************************************************
** Form generated from reading UI file 'entrywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTRYWINDOW_H
#define UI_ENTRYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EntryWindow
{
public:
    QAction *actionExit;
    QAction *actionDisconnect;
    QAction *actionAbout_us;
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLineEdit *ip_addr;
    QLabel *label;
    QLineEdit *port_no;
    QLabel *label_2;
    QMenuBar *menuBar;
    QMenu *menuSettings;
    QMenu *menuAbout;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EntryWindow)
    {
        if (EntryWindow->objectName().isEmpty())
            EntryWindow->setObjectName(QStringLiteral("EntryWindow"));
        EntryWindow->resize(545, 265);
        actionExit = new QAction(EntryWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionDisconnect = new QAction(EntryWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionAbout_us = new QAction(EntryWindow);
        actionAbout_us->setObjectName(QStringLiteral("actionAbout_us"));
        centralWidget = new QWidget(EntryWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(150, 160, 261, 31));
        ip_addr = new QLineEdit(centralWidget);
        ip_addr->setObjectName(QStringLiteral("ip_addr"));
        ip_addr->setGeometry(QRect(220, 50, 211, 22));
        ip_addr->setCursor(QCursor(Qt::IBeamCursor));
        ip_addr->setAlignment(Qt::AlignCenter);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 45, 131, 31));
        port_no = new QLineEdit(centralWidget);
        port_no->setObjectName(QStringLiteral("port_no"));
        port_no->setGeometry(QRect(220, 90, 211, 22));
        port_no->setMaxLength(5);
        port_no->setFrame(true);
        port_no->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 90, 131, 20));
        label_2->setAlignment(Qt::AlignCenter);
        EntryWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EntryWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 545, 19));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        EntryWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(EntryWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QPalette palette;
        QBrush brush(QColor(0, 2, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        QBrush brush2(QColor(190, 190, 190, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        QBrush brush3(QColor(239, 235, 231, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        statusBar->setPalette(palette);
        QFont font;
        font.setBold(false);
        font.setItalic(true);
        font.setWeight(50);
        statusBar->setFont(font);
        EntryWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuSettings->addAction(actionExit);
        menuAbout->addAction(actionAbout_us);

        retranslateUi(EntryWindow);

        QMetaObject::connectSlotsByName(EntryWindow);
    } // setupUi

    void retranslateUi(QMainWindow *EntryWindow)
    {
        EntryWindow->setWindowTitle(QApplication::translate("EntryWindow", "EntryWindow", 0));
        actionExit->setText(QApplication::translate("EntryWindow", "Exit", 0));
        actionDisconnect->setText(QApplication::translate("EntryWindow", "Disconnect", 0));
        actionAbout_us->setText(QApplication::translate("EntryWindow", "About us...", 0));
        pushButton->setText(QApplication::translate("EntryWindow", "Connect", 0));
        ip_addr->setInputMask(QApplication::translate("EntryWindow", "000.000.000.000", 0));
        ip_addr->setPlaceholderText(QString());
        label->setText(QApplication::translate("EntryWindow", "Server IP Address", 0));
        port_no->setPlaceholderText(QApplication::translate("EntryWindow", "Process port", 0));
        label_2->setText(QApplication::translate("EntryWindow", "Port", 0));
        menuSettings->setTitle(QApplication::translate("EntryWindow", "Settings", 0));
        menuAbout->setTitle(QApplication::translate("EntryWindow", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class EntryWindow: public Ui_EntryWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTRYWINDOW_H
