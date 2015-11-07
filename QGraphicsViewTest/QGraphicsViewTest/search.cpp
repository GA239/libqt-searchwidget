#include "search.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPushButton>

#include <QAbstractItemView>
#include "tagcompleteritemdelegate.h"


Search::Search(QWidget *parent) : QWidget(parent)
{
    _scene = new  QGraphicsScene();
    _view = new  QGraphicsViewTest(_scene);
    _view->setRenderHint(QPainter::Antialiasing,true);

    this->initScene();


    QVBoxLayout layout;
    layout.addWidget(_view);
    layout.addWidget(_lineEdit);

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
    _indent = 7;
    _lineEdit = new QLineEdit();

    _lineEdit->setStyleSheet("border: 3px solid gray; border-radius: 10px; padding: 5 8px;");
    _lineEdit->resize((this->size().width() - _indent),100);

    _lineEdit->setFont(QFont("times",30));
    _currentTagPoint = QPoint(0,_lineEdit->height() + _indent);

    connect(_lineEdit, SIGNAL(returnPressed()), SLOT(addTag()));

    QStringList wordList;
    wordList << "C++looooooooooooooooooooon" << "C#" << "php" << "qt";

    _completer = new MyCompleter(wordList,this);
    _completer->setCompletionMode(QCompleter::PopupCompletion);

    TagCompleterItemDelegate* tagCompleterItemDelegate = new TagCompleterItemDelegate(this, true);

    _completer->popup()->setItemDelegate(tagCompleterItemDelegate);
    _lineEdit->setCompleter(_completer);

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
    _lineEdit->resize((this->size().width()),100);

    QRect r = _view->rect();
    r.setHeight(r.height() - _indent);
    r.setWidth(r.width() - _indent);

    // сцена немного трясётся при масштабирвоании
    _scene->setSceneRect(r);
}
