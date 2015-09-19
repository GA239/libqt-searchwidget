#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T23:15:11
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testSearchwidget
TEMPLATE = app


SOURCES += main.cpp\
        ../models/basemodel.cpp \
        ../models/database.cpp \
        mainwindow.cpp \
        fileicons.cpp \
        ../models/graphproxymodel.cpp


HEADERS  += mainwindow.h\
        ../models/basemodel.h \
        ../models/database.h \
        ../models/graphproxymodel.h

FORMS    += mainwindow.ui

LIBS+=  -L../libqt-searchwidget/build-searchwidget-Desktop/debug -lsearchwidget

INCLUDEPATH += ../libqt-searchwidget/searchwidget
DEPENDPATH +=  ../libqt-searchwidget/searchwidget
