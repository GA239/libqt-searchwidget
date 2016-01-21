#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../src/searchwidget.h"


#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showSearchWidgetTags(void);

private:
    Ui::MainWindow *ui;
    QStringListModel *model;
    SearchWidget *searchWidget;
    QLabel *label;
};

#endif // MAINWINDOW_H
