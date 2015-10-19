QT       += core widgets sql

TEMPLATE = lib

#*** graphao modelue ***
DEPENDPATH +=  ../../core/core
INCLUDEPATH +=  ../../core/core
CONFIG(debug, debug|release) {
    LIBS+= -L../../core/core/debug -lcore
}
CONFIG(release, debug|release) {
    LIBS+= -L../../core/core/release -lcore
}

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
