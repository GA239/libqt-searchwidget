QT       += core widgets sql

TEMPLATE = lib

#*** SynapsCore ***
CONFIG(debug, debug|release) {
    LIBS+= -L../../synapscore/src/debug -lcore
}
CONFIG(release, debug|release) {
    LIBS+= -L../../synapscore/src/release -lcore
}
DEPENDPATH +=  . ../../synapscore/src
INCLUDEPATH +=  . ../../synapscore/src

SOURCES += \
    searchwidget.cpp \
    qtaglabelbutton.cpp \
    tagcompleteritemdelegate.cpp \
    tagcustomcompleter.cpp \
    tageventfilter.cpp \
    flowlayout.cpp


HEADERS += \
    searchwidget.h \
    qtaglabelbutton.h \
    tagcompleteritemdelegate.h \
    tagcustomcompleter.h \
    tageventfilter.h \
    flowlayout.h


DEFINES += SEARCHWIDGET

RESOURCES += \
    resources.qrc
