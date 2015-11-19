#include <QApplication>
#include "customraphicsview.h"
#include "search.h"
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Search testWidget;

    QStringListModel model;
    model.setStringList(QStringList()<<"Item1"<<"Item2"<<"Item3"<< "C" << "C++" << "C#" << "php" << "qt");

    testWidget.setModel(&model);

    testWidget.show();

    return a.exec();
}
