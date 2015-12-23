#include "searchwidget.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPushButton>
#include <QAbstractItemView>
<<<<<<< HEAD
#include <QAbstractProxyModel>
=======
#include <QCoreApplication>
>>>>>>> dea7b3eb2d9a3e3caada4c83e5cb1bd327c62c4d

/**
 * @brief Default Constructor. Sets tefault values, and make
 * the default setting of the widget.
 *
 * @param parent
 */
SearchWidget::SearchWidget(QWidget *parent) : QWidget(parent)
{
    //! [1]
    this->model = new QStringListModel(this);
    this->buttonPadding = 10;
    this->flowLayout = new FlowLayout;
    this->setLayout(this->flowLayout);
    this->setAttribute(Qt::WA_StaticContents);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    tagCompleterItemDelegate = new TagCompleterItemDelegate(this);
    //! [1]
    //! [2]
    lineEdit = new SearchLine();
    lineEdit->setStyleSheet("border:#ccc 1px;");
    this->fontMetrics().height();
    lineEdit->resize(this->size().width(),this->fontMetrics().height() + 2 * this->buttonPadding);
    this->lineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

<<<<<<< HEAD
    lineEditCompleter = new LineEditCompleter(this);
    lineEditCompleter->setModel(this->model);
    lineEditCompleter->setWrapAround(false);
    lineEditCompleter->setCompletionMode(QCompleter::PopupCompletion);
    lineEdit->setCompleter(lineEditCompleter);
=======
    _view = new  CustomGraphicsView(_scene);
    _view->setRenderHint(QPainter::Antialiasing,true);
    _tagCompleterItemDelegate = new TagCompleterItemDelegate(this,QFont("times",FONT_SIZE));

    this->initLineEdit();
>>>>>>> dea7b3eb2d9a3e3caada4c83e5cb1bd327c62c4d

    connect(lineEdit, SIGNAL(returnPressed()), SLOT(onReturnPressed()));
    //connect(lineEditCompleter, SIGNAL(activated(QModelIndex)),this, SLOT(onCompleterFinished(QModelIndex)));
    connect(lineEditCompleter, SIGNAL(completeFinished(QModelIndex)),this, SLOT(onCompleterFinished(QModelIndex)));
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(onSearchTextChanged(QString)) );

    this->flowLayout->addWidget(lineEdit);
    this->calcSize();
    this->repaint();
    lineEdit->setFocus();
    //! [2]
}

/**
 * @brief Destructor.
 */
SearchWidget::~SearchWidget()
{

}

/**
 * @brief Creates and adds new TagButton element to widget.
 * @param name of new tag
 */
void SearchWidget::addTag(const QString &data)
{
    TagButton *tag = new TagButton(this);
    tag->setText(data);
    //! [1]
    this->flowLayout->removeWidget(this->lineEdit);
    this->flowLayout->addWidget(tag);
    this->flowLayout->addWidget(this->lineEdit);
    connect(tag, SIGNAL(deltag(TagButton*)), this, SLOT(removeTagSlot(TagButton*)) );
    this->repaint();
    //! [1]
    return;
}

/**
 * @brief Creates and adds new TagButton element to widget.
 * @param index associated with tag; name of tag also takes from index
 */
void SearchWidget::addTag(const QModelIndex index)
{
<<<<<<< HEAD
    TagButton *tag = new TagButton(this);
    tag->setText(this->model->data(index, Qt::DisplayRole).toString());
    tag->setIndex(index);
    //![1]
    this->flowLayout->removeWidget(this->lineEdit);
    this->flowLayout->addWidget(tag);
    this->flowLayout->addWidget(this->lineEdit);
    connect(tag, SIGNAL(deltag(TagButton*)), this, SLOT(removeTagSlot(TagButton*)) );
    this->repaint();
    //![1]
    return;
}

/**
 * @brief Removes TagButton element from search widget.
 * @param index
 */
void SearchWidget::removeTag(TagButton *tag)
{
    if(tag != NULL) {
        this->flowLayout->removeWidget(tag);
        tag->deleteLater();
    }
    return;
}

/**
 * @brief Returns TagButton associated with the index if present, else return NULL.
 * @param index
 * @return
 */
TagButton *SearchWidget::getTagByIndex(const QModelIndex index)
{
    TagButton *tag = NULL;
    int count = this->children().count();
    for(int i = 0; i < count; i++) {
        tag = qobject_cast<TagButton *> (this->children().at(i));
        if(tag != NULL) {
            if(tag->index() == index) {
                break;
            }
        }
    }
    return tag;
=======
    _lineEdit = new CustomLineEdit();
    _lineEdit->setStyleSheet("border: 3px solid gray; border-radius: 10px; padding: 5 8px;");
    _lineEdit->resize((this->size().width() - INDENT),LINE_EDIT_HEIGHT);

    _lineEdit->setFont(QFont("times",FONT_SIZE));
    _completer = new CustomCompleter(this);
    _completer->setCompletionMode(QCompleter::PopupCompletion);
    _popup = new CustomPopup(this);
    _completer->setPopup(_popup);
    _lineEdit->setCompleter(_completer);

    connect(_completer, SIGNAL(activated(QModelIndex)), this ,SLOT(addTagTromPopup(QModelIndex)));
    connect(_lineEdit, SIGNAL(textChanged(QString)), SLOT(textWatcher()));
    connect(_lineEdit, SIGNAL(returnPressed()), SLOT(addTag()));
>>>>>>> dea7b3eb2d9a3e3caada4c83e5cb1bd327c62c4d
}

/**
 * @brief Clears search widget: removes all tags and clears search line
 */
void SearchWidget::clear(void)
{
    //! [1] remove finded tags
    this->selModel->clear();
    //! [1]
    //! [2] remove unfinded tags
    TagButton *tag;
    int count = this->children().count();
    for(int i = 0; i < count ; i++) {

        tag = qobject_cast<TagButton *>(this->children().at(i));
        if(tag != NULL) {
            this->flowLayout->removeWidget(tag);
            tag->deleteLater();
        }
    }
    //! [2]
    //! [3] clear text in search line
    this->lineEdit->clear();
    //! [3]
    return;
}

/**
 * @brief Sets new data model used by search widget
 * @param model
 */
void SearchWidget::setModel(QAbstractItemModel *model)
{
    delete this->model;
    this->model = model;
    this->lineEditCompleter->setModel(model);
    this->selModel = new QItemSelectionModel(model);
    lineEditCompleter->popup()->setItemDelegate(tagCompleterItemDelegate); //Must be set after every time the model is set
    return;
}

/**
 * @brief Sets new selection model used by search widget
 * @param selection model
 */
void SearchWidget::setSelectionModel(QItemSelectionModel *selModel)
{
    ///@todo remove prev selection model
    this->selModel = selModel;
    connect( this->selModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onTagSelected(QItemSelection,QItemSelection)) );
}

/**
 * @brief Action on request for tag removing from widget
 * @param pointer to TagButton object
 */
void SearchWidget::removeTagSlot(TagButton *tag)
{
    this->flowLayout->removeWidget(tag);
    tag->deleteLater();
    //![2]
    if(tag->index().isValid()) {
        QModelIndex index = tag->index();
        QItemSelection selection = QItemSelection(index, index);
        QItemSelection widgetSelection = selectionModel()->selection();
        widgetSelection.merge(selection, QItemSelectionModel::Toggle);
        selectionModel()->select(widgetSelection, QItemSelectionModel::ClearAndSelect);
    }
    //![2]
    return;
}

/**
 * @brief Function is called when search widged is resized.
 * @param event
 */
void SearchWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    lineEdit->resize((this->size().width() - 2*this->buttonPadding), this->fontMetrics().height() + 2*this->buttonPadding);
}

/**
 * @brief Adds new index in SearchWidget selection model
 * @param new index
 */
void SearchWidget::insertSelection(QModelIndex index)
{
    if(index.isValid()) {
        QItemSelection selection = QItemSelection(index, index);
        QItemSelection widgetSelection = selectionModel()->selection();
        widgetSelection.merge(selection, QItemSelectionModel::Select);
        selectionModel()->select(widgetSelection, QItemSelectionModel::ClearAndSelect);
    }
    return;
}

/**
 * @brief Action on the end of the selection item in the comleter list.
 * @param proxyIndex - index in completion model
 */
void SearchWidget::onCompleterFinished(QModelIndex proxyIndex)
{
<<<<<<< HEAD
    if(proxyIndex.isValid()) {
        QAbstractProxyModel* proxyModel = qobject_cast<QAbstractProxyModel*>(this->lineEditCompleter->completionModel());
        Q_ASSERT(proxyModel != 0);
        QModelIndex index = proxyModel->mapToSource(proxyIndex);
        if(index.isValid()) {
            this->insertSelection(index);
            this->lineEdit->clear();
        }
=======
    QString data = _lineEdit->text();
    if(!data.isEmpty())
    {
        addTag(data);
        this->cleanLineEdit();
>>>>>>> dea7b3eb2d9a3e3caada4c83e5cb1bd327c62c4d
    }
    return;
}

/**
 * @brief Action on search line Return or Enter key pressed.
 */
void SearchWidget::onReturnPressed(void)
{
    QString prefixText = this->lineEditCompleter->completionPrefix();
    QString completionText = this->lineEditCompleter->currentCompletion();
    QString editText = this->lineEdit->text();
    if(prefixText != completionText && prefixText == editText){
        this->addTag(this->lineEdit->text());
        this->lineEdit->clear();
    }
    return;
}

/**
 * @brief Action on the selection model changes: select and unselect items in widgets,
 * usinf this selection model.
 *
 * @param topLeft
 * @param bottomRight
 */
void SearchWidget::onTagSelected(const QItemSelection & selected, const QItemSelection & deselected)
{
    QModelIndexList list;
    TagButton *tag;
    list = deselected.indexes();
    for(int i = 0; i < list.count(); i++) {
        tag = this->getTagByIndex(list.at(i));
        this->removeTag(tag);
    }

    list = selected.indexes();
    for(int i = 0; i < list.count(); i++) {
        this->addTag(list.at(i));
    }
    return;
}

/**
 * @brief Checks the search line on the availability of special characters (',')
 * and produces tags finding in the text.
 *
 * @param text
 */
void SearchWidget::onSearchTextChanged(QString text)
{
    QString leftSide = text.right(1);
    if(leftSide == ",") {
        QString name = text.left(text.length() - 1);
        this->addTag(name);
        this->lineEdit->clear();
    }
    return;
}

/**
 * @brief Function is called when a search widget repaint event occurs.
 * @param event
 */
void SearchWidget::paintEvent(QPaintEvent *event)
{
    /// @attention QWidget::paintEngine() will never be called (see docs); the backingstore will be used instead.
    Q_UNUSED(event);
    QPalette palatte = this->palette();
    QPainter painter(this);
    painter.setPen(Qt::transparent);
    painter.setBrush(Qt::white);
    QRect widgetRect(this->rect().top(), this->rect().left(), this->rect().width(), this->rect().height());
    painter.drawRect(widgetRect);
    QRect usedRect(this->rect().top(), this->rect().left(), this->rect().width(), this->lineEdit->rect().bottom());
    lineEdit->resize((this->size().width() - 2*this->buttonPadding), this->fontMetrics().height() + 2*this->buttonPadding);
    return;
}

/**
 * @brief Calculates the size of the base elements of the widget
 */
void SearchWidget::calcSize()
{
    //! [2] calc line edit competer size
    QRect widgetRect(this->rect().top(), this->rect().left(), this->rect().width() - 1, this->rect().height() - 1);
    //! [2]
}

void SearchWidget::cleanLineEdit()
{
    _lineEdit->clear();
}
/**
 * @brief SearchWidget::addTagTromPopup
 *
 * adds a tag with the data from the Completer with current index
 *
 * @param index
 */
void SearchWidget::addTagTromPopup(const QModelIndex &index)
{
    this->_completer->popup()->setCurrentIndex(index);
    this->addTag();
    this->_lineEdit->changeModificationPossibility();
}
/**
 * @brief SearchWidget::textWatcher
 *
 * Following the lineedit and prohibit editing if needed
 *
 */
void SearchWidget::textWatcher()
{
    if(this->_lineEdit->notAbleToModifie())
    {
        this->cleanLineEdit();
    }
}

/**
 * @brief Returns curent SearchWidget selection model
 * @return
 */
QItemSelectionModel* SearchWidget::selectionModel() const
{
    return this->selModel;
}

/**
 * @brief Returns tags (indexes) selected by SearchWidget in model
 * @return list of indexes
 */
QModelIndexList SearchWidget::tags()
{
    QModelIndexList indexList;
    TagButton *tag;
    int count = this->children().count();
    for(int i = 0; i < count; i++) {
        tag = qobject_cast<TagButton *> (this->children().at(i));
        if(tag != NULL) {
            if(tag->index().isValid()) {
               indexList.append(tag->index());
            }
        }
    }
    return indexList;
}

<<<<<<< HEAD
/**
 * @brief Returns list of tags name undefinded in model
 * @return list of strings
 */
QStringList SearchWidget::unfindedTags()
{
   QStringList stringList;
   TagButton *tag;
   int count = this->children().count();
   for(int i = 0; i < count; i++) {
       tag = qobject_cast<TagButton *> (this->children().at(i));
       if(tag != NULL) {
           if(!tag->index().isValid()) {
              stringList.append(tag->text());
           }
       }
   }
   return stringList;
}

=======
bool SearchWidget::eventFilter(QObject *watched, QEvent *event)
{
    return QObject::eventFilter(watched, event);
}
>>>>>>> dea7b3eb2d9a3e3caada4c83e5cb1bd327c62c4d
