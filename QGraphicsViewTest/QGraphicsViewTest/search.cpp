#include "search.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPushButton>

Search::Search(QWidget *parent) : QWidget(parent)
{
    dataval = 1;

    this->initScene();
    view = new  QGraphicsViewTest(scene);
    view->setRenderHint(QPainter::Antialiasing,true);

    QPushButton* adderTags = new QPushButton("Add Tag");
    scene->addWidget(adderTags);
    scene->items()[0]->setPos(30,350);
    scene->items()[0]->setScale(3);

    QObject::connect(adderTags,SIGNAL(clicked()),this, SLOT(addTag()));

    QVBoxLayout layout;
    layout.addWidget(view);

    this->setLayout(&layout);
}

void Search::initScene()
{
    QRectF r = this->rect();
    r.setHeight(r.height()-10);
    r.setWidth(r.width()-10);

    scene = new  QGraphicsScene(r);

    currentTagPoint = QPoint(0,0);
    _indent = 7;

    //scene->addPixmap(QPixmap("c:/Users/AG/Downloads/kak_narisovat_sticha.jpg"));
}

void Search::addTag(const QString &data)
{
    MyTagItem* tag = new MyTagItem(currentTagPoint,data);
    scene->addItem(tag);

    int newx = currentTagPoint.x() + tag->getWidth() + _indent;
    currentTagPoint.setX(newx);

    if(newx >= this->size().width() - tag->getWidth())
    {
        currentTagPoint.setY(currentTagPoint.y() + tag->getHeight() + _indent);
        currentTagPoint.setX(0);
    }
}

void Search::addTag()
{
    QString datas = "Tag " + QString::number(dataval, 'i', 0);
    dataval *= 10;
    addTag(datas);
}

Search::~Search()
{
    delete scene;
    delete view;
}

void Search::resizeEvent(QResizeEvent *event)
{
    event->accept();
    view->resize(this->size());

    //непонятно что делать с трясущейся сценой.
    QRect r = view->rect();
    r.setHeight(r.height()-10);
    r.setWidth(r.width()-10);
    scene->setSceneRect(r);

}


