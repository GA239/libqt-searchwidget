#include <QApplication>

#include "mainwindow.h"
#include <QListView>

/**
 * @brief Application start from this function.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
