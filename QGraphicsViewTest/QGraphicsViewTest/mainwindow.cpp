#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QSpacerItem>
#include <QListView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->model = new QStringListModel(this);
    this->model->setStringList(QStringList() << "Item1" << "Item2" << "Item3" << "C" << "C++" << "C#" << "C++" << "php" << "qt");
    this->searchWidget = new SearchWidget(this);
    this->searchWidget->setModel(this->model);

    QVBoxLayout *verLayout = new QVBoxLayout;
    this->ui->centralwidget->setLayout(verLayout);
    this->ui->centralwidget->layout()->addWidget(searchWidget);
    //QSpacerItem *spacer = new QSpacerItem(40, 20,  QSizePolicy::Minimum, QSizePolicy::Expanding);
    //this->ui->centralwidget->layout()->addItem(spacer);
    QListView *listView = new QListView();
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView->setModel(this->model);
    searchWidget->setSelectionModel(listView->selectionModel());
    this->ui->centralwidget->layout()->addWidget(listView);
    listView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QPushButton *button = new QPushButton(this);
    button->setText("Clear");
    this->ui->centralwidget->layout()->addWidget(button);
    connect(button, SIGNAL(clicked()), this, SLOT(clearButtonAction()) );
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::clearButtonAction
 */
void MainWindow::clearButtonAction()
{
    this->searchWidget->removeAllTags();
    return;
}
