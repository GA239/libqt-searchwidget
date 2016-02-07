#-------------------------------------------------
#
# Project created by QtCreator 2015-10-20T22:04:14
#
#-------------------------------------------------

QT       += core gui widgets sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = searchwidget
TEMPLATE = lib


SOURCES += tagcompleteritemdelegate.cpp \
    flowlayout.cpp \
    tagbutton.cpp \
    lineeditcompleter.cpp \
    searchline.cpp \
    closebutton.cpp \
    flowwidget.cpp \
    searchwidget.cpp

HEADERS  += tagcompleteritemdelegate.h \
    flowlayout.h \
    tagbutton.h \
    lineeditcompleter.h \
    searchline.h \
    closebutton.h \
    flowwidget.h \
    searchwidget.h
