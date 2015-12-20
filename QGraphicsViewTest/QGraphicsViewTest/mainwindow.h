#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "searchwidget.h"

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
    void clearButtonAction(void);
    void getTagButtonAction(void);

private:
    Ui::MainWindow *ui;
    QStringListModel *model;
    SearchWidget *searchWidget;
    QLabel *label;
};

#endif // MAINWINDOW_H
