#-------------------------------------------------
#
# Project created by QtCreator 2015-10-20T22:04:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QGraphicsViewTest
TEMPLATE = app


SOURCES += main.cpp \
    tagcompleteritemdelegate.cpp \
    searchwidget.cpp \
<<<<<<< HEAD
    flowlayout.cpp \
    mainwindow.cpp \
    tagbutton.cpp \
    lineeditcompleter.cpp \
    searchline.cpp
=======
    tag.cpp \
    custompopup.cpp \
    customlineedit.cpp
>>>>>>> dea7b3eb2d9a3e3caada4c83e5cb1bd327c62c4d

HEADERS  += tagcompleteritemdelegate.h \
    searchwidget.h \
<<<<<<< HEAD
    flowlayout.h \
    mainwindow.h \
    tagbutton.h \
    lineeditcompleter.h \
    searchline.h

FORMS += \
    mainwindow.ui
=======
    tag.h \
    custompopup.h \
    customlineedit.h
>>>>>>> dea7b3eb2d9a3e3caada4c83e5cb1bd327c62c4d
