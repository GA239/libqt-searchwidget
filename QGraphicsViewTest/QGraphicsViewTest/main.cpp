#include <QApplication>
#include "customraphicsview.h"
#include "search.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Search testWidget;
    testWidget.show();

    return a.exec();
}
