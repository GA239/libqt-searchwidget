#include <QApplication>
#include "qgraphicsviewtest.h"
#include "search.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Search testWidget;
    testWidget.show();

    return a.exec();
}
