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
        mainwindow.cpp \
    tmp/flowlayout.cpp \
    tmp/lineeditcompleter.cpp \
    tmp/searchline.cpp \
    tmp/searchwidget.cpp \
    tmp/tagbutton.cpp \
    tmp/tagcompleteritemdelegate.cpp

HEADERS  += mainwindow.h \
    tmp/flowlayout.h \
    tmp/lineeditcompleter.h \
    tmp/searchline.h \
    tmp/searchwidget.h \
    tmp/tagbutton.h \
    tmp/tagcompleteritemdelegate.h

FORMS    += mainwindow.ui
