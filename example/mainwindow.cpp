#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include "../seachwidget/searchwidget.h"
#include <QDir>
#include "../models/basemodel.h"
#include "../models/graphproxymodel.h"

#define unit 20

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //searchwidget init
    SearchWidget *searchWidget = new SearchWidget(ui->searchpanel_widget);
    searchWidget->setGeometry(0,0,ui->searchpanel_widget->width(),ui->searchpanel_widget->height());
    //set styles
    searchWidget->setSearchlineStyle("border: 0px solid #ffffff; color: #333333; padding: 1px 1px 1px 1px;");
    searchWidget->setFrameStyle("#searchFrame {border: 1px solid #bdbdbd;}");
    searchWidget->setTagButtonStyle("border: 1px solid #dae2e8; color: #333333; background: #dae2e8; padding: 0px 2px 0px 2px;");
    //searchWidget->setClosebtnVisible(false);

    //![1] create and open temporary database
    QDir dir = QDir::current();
    dir.mkdir("db");                                                   // create directory for temporary database in Project dir
    DataBase *dataBase = DataBase::instance();
    dataBase->setDataFile(QString("db/test.db"));                       // open temporary database
    BaseModel *baseModel = new BaseModel(this);
    GraphProxyModel *model = new GraphProxyModel(this);
    model->setSourceModel(baseModel);

    searchWidget->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
