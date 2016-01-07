#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tmp/searchwidget.h"

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
    void clearSearchWidget(void);
    void showSearchWidgetTags(void);

private:
    Ui::MainWindow *ui;
    QStringListModel *model;
    SearchWidget *searchWidget;
    QLabel *label;
};

#endif // MAINWINDOW_H
