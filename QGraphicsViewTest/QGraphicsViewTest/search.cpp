#include "search.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPushButton>

Search::Search(QWidget *parent) : QWidget(parent)
{
    this->initScene();
    _view = new  QGraphicsViewTest(_scene);
    _view->setRenderHint(QPainter::Antialiasing,true);

    QVBoxLayout layout;
    layout.addWidget(_view);

    this->setLayout(&layout);
    _lineEdit->setFocus();
}

Search::~Search()
{
    delete _scene;
    delete _view;
}
/**
 * @brief Search::initScene
 *
 * initializes the scene when you first create the widget
 */
void Search::initScene()
{
    _scene = new  QGraphicsScene();
    _indent = 7;
    _scaleFactor = 3;

    _lineEdit = new QLineEdit();
    _lineEdit->setFont(QFont("times",10));
    _lineEdit->resize((this->size().width() - _indent)/_scaleFactor,25);
    _currentTagPoint = QPoint(0,_lineEdit->height() * _scaleFactor + _indent);

    connect(_lineEdit, SIGNAL(returnPressed()), SLOT(addTag()));

    _scene->addWidget(_lineEdit);
    _scene->items()[0]->setScale(_scaleFactor);

    //scene->addPixmap(QPixmap("c:/Users/AG/Downloads/kak_narisovat_sticha.jpg"));
}

/**
 * @brief Search::addTag
 * It adds to the scene tag with data
 *
 * @param data: text data
 */
void Search::addTag(const QString &data)
{
    //adding a new tag
    MyTagItem* tag = new MyTagItem(_currentTagPoint,data);
    _scene->addItem(tag);

    //Calculation of positions for the next tag:
    int newx = _currentTagPoint.x() + tag->getWidth() + _indent;
    _currentTagPoint.setX(newx);

    if(newx > this->size().width())
    {
        _currentTagPoint.setY(_currentTagPoint.y() + tag->getHeight() + _indent);
        _currentTagPoint.setX(0);
        tag->setPos(_currentTagPoint);
        newx = _currentTagPoint.x() + tag-> getWidth() + _indent;
        _currentTagPoint.setX(newx);
    }
}

void Search::addTag()
{
    QString data = _lineEdit->text();
    if(!data.isEmpty())
    {
        _lineEdit->clear();
        addTag(data);
    }
}

void Search::resizeEvent(QResizeEvent *event)
{
    event->accept();
    _view->resize(this->size());
    _lineEdit->resize((this->size().width() - _indent)/_scaleFactor,25);

    // сцена немного трясётся при масштабирвоании
    QRect r = _view->rect();
    r.setHeight(r.height() - _indent);
    r.setWidth(r.width() - _indent);
    _scene->setSceneRect(r);
}
