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
    searchwidget.cpp \
    flowlayout.cpp \
    tagbutton.cpp \
    lineeditcompleter.cpp \
    searchline.cpp \
    completerpopup.cpp

HEADERS  += tagcompleteritemdelegate.h \
    searchwidget.h \
    flowlayout.h \
    tagbutton.h \
    lineeditcompleter.h \
    searchline.h \
    completerpopup.h
