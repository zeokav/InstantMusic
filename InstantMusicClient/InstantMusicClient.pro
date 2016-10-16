#-------------------------------------------------
#
# Project created by QtCreator 2016-10-03T09:32:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InstantMusicClient
TEMPLATE = app


SOURCES += main.cpp\
        entrywindow.cpp \
    connectedwindow.cpp

HEADERS  += entrywindow.h \
    connectedwindow.h

FORMS    += entrywindow.ui \
    connectedwindow.ui
