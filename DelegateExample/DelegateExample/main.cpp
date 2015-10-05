//#include "mainwindow.h"
#include <QApplication>
#include <QStringListModel>
#include <QListView>

#include "simpledelegate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringListModel model;
    model.setStringList(QStringList()<<"Item1"<<"Item2"<<"Item3");

    QListView listView;
    listView.setModel(&model);

    listView.setItemDelegate(new SimpleDelegate(&listView));
    listView.show();

    return a.exec();
}
