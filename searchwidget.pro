QT       += core widgets sql

TEMPLATE = lib
# Input
SOURCES += \
    searchwidget.cpp \
    qtaglabelbutton.cpp \
    tagcompleteritemdelegate.cpp \
    tagcustomcompleter.cpp \
    tageventfilter.cpp \
    flowlayout.cpp \
    ../models/basemodel.cpp \
    ../models/database.cpp \
    ../models/docsproxymodel.cpp \
    ../models/graphproxymodel.cpp \
    ../models/singleton.cpp \
    fileicons.cpp

HEADERS += \
    searchwidget.h \
    qtaglabelbutton.h \
    tagcompleteritemdelegate.h \
    tagcustomcompleter.h \
    tageventfilter.h \
    flowlayout.h \
    ../models/basemodel.h \
    ../models/database.h \
    ../models/docsproxymodel.h \
    ../models/graphproxymodel.h \
    ../models/singleton.h \
    fileicons.h

DEFINES += SEARCHWIDGET

RESOURCES += \
    resources.qrc
