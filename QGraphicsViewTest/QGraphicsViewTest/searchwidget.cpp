#include "searchwidget.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPushButton>
#include <QAbstractItemView>
#include <QAbstractProxyModel>

SearchWidget::SearchWidget(QWidget *parent) : QWidget(parent)
{
    this->clearLaterTimerId = 0;
    this->model = new QStringListModel(this);
    this->completerIsFinished = 0;
    this->buttonPadding = 10;
    this->flowLayout = new FlowLayout;
    this->setLayout(this->flowLayout);
    this->setAttribute(Qt::WA_StaticContents);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    _tagCompleterItemDelegate = new TagCompleterItemDelegate(this);
    //! [1]
    lineEdit = new SearchLine();
    lineEdit->setStyleSheet("border:#ccc 1px;");
    this->fontMetrics().height();
    lineEdit->resize(this->size().width(),this->fontMetrics().height() + 2 * this->buttonPadding);
    this->lineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    lineEditCompleter = new LineEditCompleter(this);
    lineEditCompleter->setModel(this->model);
    //lineEditCompleter->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    //lineEditCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    lineEditCompleter->setWrapAround(false);
    lineEditCompleter->setCompletionMode(QCompleter::PopupCompletion);
    lineEdit->setCompleter(lineEditCompleter);

    connect(lineEdit, SIGNAL(returnPressed()), SLOT(completerReturnPressedAction()));
    //connect(lineEditCompleter, SIGNAL(completeFunished()), SLOT(completerReturnPressedAction()));
    connect(lineEditCompleter, SIGNAL(activated(QModelIndex)),this, SLOT(completerFinishedAction(QModelIndex)));
    connect(lineEditCompleter, SIGNAL(activated(const QString&)), lineEdit, SLOT(clear()), Qt::QueuedConnection);
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(test(QString)) );
    connect(lineEditCompleter->popup(), SIGNAL(entered(QModelIndex)), lineEdit, SLOT(clear()) );
    connect(lineEditCompleter, SIGNAL(activated(QModelIndex)), lineEdit, SLOT(clear()) );
    //! [1]
    this->flowLayout->addWidget(lineEdit);
    this->calcSize();
    this->repaint();
    lineEdit->setFocus();
}

SearchWidget::~SearchWidget()
{

}

/**
 * @brief Search::initLineEdit
 * initializes the lineEdit when you first create the widget
 */
void SearchWidget::initLineEdit()
{

}

/**
 * @brief Search::addTag
 * It adds new tag with data
 *
 * @param data: text data
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
 * @brief SearchWidget::addTag
 * @param index
 */
void SearchWidget::addTag(const QModelIndex index)
{
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
 * @brief SearchWidget::removeTag
 * @param index
 */
void SearchWidget::removeTag(const QModelIndex index)
{
    TagButton *tag;
    int count = this->children().count();
    for(int i = 0; i < count; i++) {
        tag = qobject_cast<TagButton *> (this->children().at(i));
        if(tag != NULL) {
            if(tag->index() == index) {
                this->flowLayout->removeWidget(tag);
                tag->deleteLater();
            }
        }
    }
    return;
}

/**
 * @brief SearchWidget::removeAllTags
 */
void SearchWidget::removeAllTags()
{
    TagButton *tag;
    int count = this->children().count();
    for(int i = 0; i < count ; i++) {

        tag = qobject_cast<TagButton *>(this->children().at(i));
        if(tag != NULL) {
            this->flowLayout->removeWidget(tag);
            tag->deleteLater();
        }
    }
    this->selModel->clear();
    return;
}

/**
 * @brief SearchWidget::setModel
 * @param model
 */
void SearchWidget::setModel(QAbstractItemModel *model)
{
    delete this->model;
    this->model = model;
    this->lineEditCompleter->setModel(model);
    this->selModel = new QItemSelectionModel(model);
    lineEditCompleter->popup()->setItemDelegate(_tagCompleterItemDelegate); //Must be set after every time the model is set
    return;
}

/**
 * @brief SearchWidget::setSelectionModel
 * @param selModel
 */
void SearchWidget::setSelectionModel(QItemSelectionModel *selModel)
{
    ///@todo remove prev selection model
    this->selModel = selModel;
    connect( this->selModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onTagSelected(QItemSelection,QItemSelection)) );
}

/**
 * @brief Search::removeNode
 * It removes tag frome the scene
 *
 * @param node - tag
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
 * @brief Search::resizeEvent
 *
 * resize the widget and all of its elements
 *
 * @param event
 */
void SearchWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    lineEdit->resize((this->size().width() - 2*this->buttonPadding), this->fontMetrics().height() + 2*this->buttonPadding);
}

/**
 * @brief SearchWidget::insertSelection
 * @param current index
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
 * @brief SearchWidget::completerFinishedAction
 * @param index
 */
void SearchWidget::completerFinishedAction(QModelIndex proxyIndex)
{
    if(proxyIndex.isValid()) {
        QAbstractProxyModel* proxyModel = qobject_cast<QAbstractProxyModel*>(this->lineEditCompleter->completionModel());
        Q_ASSERT(proxyModel != 0);
        QModelIndex index = proxyModel->mapToSource(proxyIndex);
        if(index.isValid()) {
            this->insertSelection(index);
            this->clearLater();
        }
    }
    else {
        ;
    }
    return;
}

/**
 * @brief SearchWidget::completerReturnPressedAction
 */
void SearchWidget::completerReturnPressedAction()
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
 * @brief SearchWidget::onTagSelected
 * @param topLeft
 * @param bottomRight
 */
void SearchWidget::onTagSelected(const QItemSelection & selected, const QItemSelection & deselected)
{
    QModelIndexList list;

    list = deselected.indexes();
    for(int i = 0; i < list.count(); i++) {
        this->removeTag(list.at(i));
    }

    list = selected.indexes();
    for(int i = 0; i < list.count(); i++) {
        this->addTag(list.at(i));
    }
    return;
}

/**
 * @brief SearchWidget::test
 * @param text
 */
void SearchWidget::test(QString text)
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
 * @brief SearchWidget::clearLaterTimer
 */
void SearchWidget::clearLaterTimer()
{

}

/**
 * @brief SearchWidget::paintEvent
 */
void SearchWidget::paintEvent(QPaintEvent *event)
{
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

void SearchWidget::timerEvent(QTimerEvent *event)
{
    QWidget::timerEvent(event);
    killTimer(this->clearLaterTimerId);
    this->clearLaterTimerId = 0;
    this->lineEdit->clear();
    return;
}

void SearchWidget::calcSize()
{
    //! [2] calc line edit competer size
    QRect widgetRect(this->rect().top(), this->rect().left(), this->rect().width() - 1, this->rect().height() - 1);
    //! [2]
}

/**
 * @brief SearchWidget::clearLater
 */
void SearchWidget::clearLater()
{
    if (!this->clearLaterTimerId)
    {
        this->clearLaterTimerId = startTimer(1);
    }
    return;
}

/**
 * @brief SearchWidget::selectionModel
 * @return
 */
QItemSelectionModel* SearchWidget::selectionModel() const
{
    return this->selModel;
}

/**
 * @brief SearchWidget::tags
 * @return
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

/**
 * @brief SearchWidget::unfindedTags
 * @return
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

