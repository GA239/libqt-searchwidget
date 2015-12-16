#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->model = new QStringListModel(this);
    this->model->setStringList(QStringList() << "Item1" << "Item2" << "Item3" << "C" << "C++" << "C#" << "php" << "qt");
    this->searchWidget = new SearchWidget(this);
    this->searchWidget->setModel(this->model);


    QVBoxLayout *verLayout = new QVBoxLayout;
    this->ui->centralwidget->setLayout(verLayout);
    this->ui->centralwidget->layout()->addWidget(searchWidget);
    QSpacerItem *spacer = new QSpacerItem(40, 20,  QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->ui->centralwidget->layout()->addItem(spacer);
    QPushButton *button = new QPushButton(this);
    this->ui->centralwidget->layout()->addWidget(button);
    //QSpacerItem *item = new QSpacerItem(1,1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    //this->ui->centralwidget->layout()->addWidget((QWidget *)item);
}

MainWindow::~MainWindow()
{
    delete ui;
}
