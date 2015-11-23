#include <QApplication>
#include "customraphicsview.h"
#include "searchwidget.h"
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SearchWidget testWidget;

    QStringListModel model;
    model.setStringList(QStringList()<<"Item1"<<"Item2"<<"Item3"<< "C" << "C++" << "C#" << "php" << "qt");

    testWidget.setModel(&model);

    testWidget.show();

    return a.exec();
}
