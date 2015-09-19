QT       += core widgets sql

TEMPLATE = lib
DEPENDPATH +=  ../../models
INCLUDEPATH +=  ../../models

# Input
SOURCES += \
    searchwidget.cpp \
    qtaglabelbutton.cpp \
    tagcompleteritemdelegate.cpp \
    tagcustomcompleter.cpp \
    tageventfilter.cpp \
    flowlayout.cpp \
    fileicons.cpp \
    ../../models/graphproxymodel.cpp \
    ../../models/basemodel.cpp \
    ../../models/database.cpp


HEADERS += \
    searchwidget.h \
    qtaglabelbutton.h \
    tagcompleteritemdelegate.h \
    tagcustomcompleter.h \
    tageventfilter.h \
    flowlayout.h \
    fileicons.h \
    ../../models/graphproxymodel.h \
    ../../models/basemodel.h \
    ../../models/database.h

    fileicons.h \


DEFINES += SEARCHWIDGET

RESOURCES += \
    resources.qrc
