#include <QApplication>

#include "mainwindow.h"
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
