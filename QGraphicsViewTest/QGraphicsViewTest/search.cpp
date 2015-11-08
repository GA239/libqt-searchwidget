#include "search.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPushButton>

#include <QAbstractItemView>
#include "tagcompleteritemdelegate.h"


Search::Search(QWidget *parent) : QWidget(parent)
{
    _scene = new  QGraphicsScene();

    _view = new  CustomGraphicsView(_scene);
    _view->setRenderHint(QPainter::Antialiasing,true);
    this->initLineEdit();

    _currentTagPoint = QPoint(0,_lineEdit->height() + INDENT);

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
 * @brief Search::initLineEdit
 * initializes the lineEdit when you first create the widget
 */
void Search::initLineEdit()
{
    _lineEdit = new QLineEdit();
    _lineEdit->setStyleSheet("border: 3px solid gray; border-radius: 10px; padding: 5 8px;");
    _lineEdit->resize((this->size().width() - INDENT),LINE_EDIT_HEIGHT);

    QFont font = QFont("times",FONT_SIZE);
    _lineEdit->setFont(font);

    QStringList wordList;
    wordList << "C++" << "C#" << "php" << "qt";
    _completer = new CustomCompleter(wordList,this);

    TagCompleterItemDelegate* tagCompleterItemDelegate = new TagCompleterItemDelegate(this,font);
    _completer->setCompletionMode(QCompleter::PopupCompletion);
    _completer->popup()->setItemDelegate(tagCompleterItemDelegate);

    _lineEdit->setCompleter(_completer);

    connect(_lineEdit, SIGNAL(returnPressed()), SLOT(addTag()));
}

/**
 * @brief Search::addTag
 * It adds new tag with data
 *
 * @param data: text data
 */
void Search::addTag(const QString &data)
{
    //adding a new tag
    mySecondTag* tag = new mySecondTag(_currentTagPoint,data);

    _scene->addItem(tag);
    connect(tag, SIGNAL(delnode(mySecondTag*)), this, SLOT(removeNode(mySecondTag*)));

    //Calculation of positions for the next tag:
    int newx = _currentTagPoint.x() + tag->getWidth() + INDENT;
    _currentTagPoint.setX(newx);

    if(newx > this->size().width())
    {
        _currentTagPoint.setY(_currentTagPoint.y() + tag->getHeight() + INDENT);
        _currentTagPoint.setX(0);
        tag->setPos(_currentTagPoint);
        newx = _currentTagPoint.x() + tag-> getWidth() + INDENT;
        _currentTagPoint.setX(newx);
    }
}
/**
 * @brief Search::addTag
 * It adds new tag to the scene
 */
void Search::addTag()
{
    QString data = _lineEdit->text();
    if(!data.isEmpty())
    {
        addTag(data);
        _lineEdit->clear();
    }
}

/**
 * @brief Search::removeNode
 * It removes tag frome the scene
 *
 * @param node - tag
 */
void Search::removeNode(mySecondTag *node)
{
    _scene->removeItem(node);
    node->deleteLater();
}

/**
 * @brief Search::resizeEvent
 *
 * resize the widget and all of its elements
 *
 * @param event
 */
void Search::resizeEvent(QResizeEvent *event)
{
    event->accept();

    _view->resize(this->size());
    _lineEdit->resize((this->size().width()),LINE_EDIT_HEIGHT);

    QRect r = _view->rect();
    r.setHeight(r.height() - INDENT);
    r.setWidth(r.width() - INDENT);

    // сцена немного трясётся при масштабирвоании
    _scene->setSceneRect(r);
}
