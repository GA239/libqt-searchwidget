#-------------------------------------------------
#
# Project created by QtCreator 2016-01-07T16:47:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = searchwidget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG(debug, debug|release) {
    LIBS+= -L../../build-searchwidget-desktop/Debug/debug -lsearchwidget
}

CONFIG(release, debug|release) {
    LIBS+= -L../../build-searchwidget-desktop/Release/release -lsearchwidget
}
