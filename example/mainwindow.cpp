#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QSpacerItem>
#include <QListView>
#include <QDebug>

/**
 * @brief Default constructor. Create new window and sets tefault values.
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->model = new QStringListModel(this);
    this->model->setStringList(QStringList() << "Item1" << "Item2" << "Item3" << "C" << "C++" << "C#" << "C++" << "php" << "qt");

    this->searchWidget = new SearchWidget(this);
    this->searchWidget->setModel(this->model);

    //QVBoxLayout *verLayout = new QVBoxLayout;
    QHBoxLayout *verLayout = new QHBoxLayout;

    this->ui->centralWidget->setLayout(verLayout);

    QPushButton *getTagButton = new QPushButton(this);
    getTagButton->setText("Get Tags");
    this->ui->centralWidget->layout()->addWidget(getTagButton);
    connect(getTagButton, SIGNAL(clicked()), this, SLOT(showSearchWidgetTags()) );

    QPushButton *getTagButton3 = new QPushButton(this);
    getTagButton3->setText("Get Tags");
    this->ui->centralWidget->layout()->addWidget(getTagButton3);
    connect(getTagButton3, SIGNAL(clicked()), this, SLOT(showSearchWidgetTags()) );


    this->ui->centralWidget->layout()->addWidget(searchWidget);
    //QSpacerItem *spacer = new QSpacerItem(40, 20,  QSizePolicy::Minimum, QSizePolicy::Expanding);
    //this->ui->centralwidget->layout()->addItem(spacer);


    QListView *listView = new QListView();
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView->setModel(this->model);
    searchWidget->setSelectionModel(listView->selectionModel());
    //this->ui->centralWidget->layout()->addWidget(listView);
    listView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    label = new QLabel(this);
    this->ui->centralWidget->layout()->addWidget(label);
}

/**
 * @brief destructor
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Shows tags from search widget
 */
void MainWindow::showSearchWidgetTags(void)
{
    QStringList stringList  = this->searchWidget->unfindedTags();
    QModelIndexList indexList = this->searchWidget->tags();

    QModelIndex index;
    QString text = "finded tags: ";
    for(int i = 0; i < indexList.count(); i++){
        index = indexList.at(i);
        text.append(this->model->data(index, Qt::DisplayRole).toString()).append(QString(", "));
    }
    text.append("\r\nunfinded tags: ");
    for(int i = 0; i < stringList.count(); i++){
        text.append(stringList.at(i)).append(QString(", "));
    }

    this->label->setText(text);
    return;
}
