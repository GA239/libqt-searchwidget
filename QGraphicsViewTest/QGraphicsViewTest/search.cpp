#include "search.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPushButton>

#include <QAbstractItemView>

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

    QStringList wordList;
    wordList << "C++" << "C#" << "php" << "qt";

    _completer = new QCompleter(wordList,_lineEdit);
    _completer->setCaseSensitivity(Qt::CaseInsensitive);
    _completer->setCompletionMode(QCompleter::InlineCompletion);
    _lineEdit->setCompleter(_completer);

    connect(_lineEdit, SIGNAL(returnPressed()), SLOT(addTag()));

    _scene->addWidget(_lineEdit);
    _scene->items()[0]->setScale(_scaleFactor);

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

    //MyTagItem* tag = new MyTagItem(_currentTagPoint,data);
    mySecondTag* tag = new mySecondTag(_currentTagPoint,data);

    _scene->addItem(tag);

    //connect(tag, SIGNAL(delnode(MyTagItem*)), this, SLOT(removeNode(MyTagItem*)));
    connect(tag, SIGNAL(delnode(mySecondTag*)), this, SLOT(removeSecondNode(mySecondTag*)));

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
        addTag(data);
        _lineEdit->clear();
    }
}

void Search::removeNode(MyTagItem* node)
{
    _scene->removeItem(node);
    //node->deleteLater();
}

void Search::removeSecondNode(mySecondTag *node)
{
    _scene->removeItem(node);
}

void Search::resizeEvent(QResizeEvent *event)
{
    event->accept();

    _view->resize(this->size());
    _lineEdit->resize((this->size().width() - _indent)/_scaleFactor,25);

    QRect r = _view->rect();
    r.setHeight(r.height() - _indent);
    r.setWidth(r.width() - _indent);

    // сцена немного трясётся при масштабирвоании
    _scene->setSceneRect(r);
}
