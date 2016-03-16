CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(searchwidgetplugin)
TEMPLATE    = lib

HEADERS     = searchwidgetplugin.h
SOURCES     = searchwidgetplugin.cpp
RESOURCES   = icons.qrc

CONFIG(debug, debug|release) {
    LIBS+= -L../build-searchwidget-desktop/debug -lsearchwidget
}

CONFIG(release, debug|release) {
    LIBS+= -L../build-searchwidget-desktop/release -lsearchwidget
}

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target


