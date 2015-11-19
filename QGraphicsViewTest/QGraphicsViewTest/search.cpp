#include "search.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPushButton>

#include <QAbstractItemView>

Search::Search(QWidget *parent) : QWidget(parent)
{
    _scene = new  QGraphicsScene();

    _view = new  CustomGraphicsView(_scene);
    _view->setRenderHint(QPainter::Antialiasing,true);
    _tagCompleterItemDelegate = new TagCompleterItemDelegate(this,QFont("times",FONT_SIZE));
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

    _lineEdit->setFont(QFont("times",FONT_SIZE));
    _completer = new CustomCompleter(this);
    _completer->setCompletionMode(QCompleter::PopupCompletion);
    _lineEdit->setCompleter(_completer);

    connect(_lineEdit, SIGNAL(returnPressed()), SLOT(addTag()));
    connect(_completer, SIGNAL(completeFunished()),_lineEdit, SLOT(clear()));
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

void Search::setModel(QAbstractItemModel *model)
{
    _model = model;
    _completer->setModel(_model);
    _selModel = new QItemSelectionModel(_model);

    //connect( selModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onItemSelected(QItemSelection,QItemSelection)) );
    _completer->popup()->setItemDelegate(_tagCompleterItemDelegate); //Must be set after every time the model is set
    connect(_completer, SIGNAL(activated(QModelIndex)),this, SLOT(insertSelection(QModelIndex)));
    return;
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

/**
 * @brief SearchWidget::insertSelection
 * @param current index
 */
void Search::insertSelection(QModelIndex curIndex)
{
    QString str = curIndex.data().toString();
    //QModelIndex index = (itemModel)->indexByName(str,0);
    QModelIndex index = (_model)->index(1,1);
    QItemSelection selection = QItemSelection(index,index);
    this->selectionModel()->select(selection, QItemSelectionModel::Select);
}

/**
 * @brief SearchWidget::selectionModel
 * @return
 */
QItemSelectionModel* Search::selectionModel() const
{
    return this->_selModel;
}
