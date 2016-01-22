#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QSpacerItem>
#include <QListView>
#include <QDebug>
#include <QScrollBar>

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

    scrollArea = new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Button);
    scrollArea->setStyleSheet("border:#ccc 1px;");
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(searchWidget);

    QScrollBar* scrollbar = scrollArea->verticalScrollBar();
    QObject::connect(scrollbar, SIGNAL(rangeChanged(int,int)), this, SLOT(moveScrollBarToBottom(int, int)));

    QVBoxLayout *verLayout = new QVBoxLayout;
    this->ui->centralWidget->setLayout(verLayout);

    QPushButton *getTagButton = new QPushButton(this);
    getTagButton->setText("Get Tags");
    this->ui->centralWidget->layout()->addWidget(getTagButton);
    connect(getTagButton, SIGNAL(clicked()), this, SLOT(showSearchWidgetTags()) );

    this->ui->centralWidget->layout()->addWidget(scrollArea);
    //QSpacerItem *spacer = new QSpacerItem(40, 60,  QSizePolicy::Minimum, QSizePolicy::Expanding);
    //this->ui->centralWidget->layout()->addItem(spacer);


    QListView *listView = new QListView();
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listView->setModel(this->model);
    searchWidget->setSelectionModel(listView->selectionModel());
    this->ui->centralWidget->layout()->addWidget(listView);
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

/**
 * @brief Move scrollbar to bottom of scrollarea.
 */
void MainWindow::moveScrollBarToBottom(int min, int max)
{
    Q_UNUSED(min);
    scrollArea->verticalScrollBar()->setValue(max);
    return;
}
