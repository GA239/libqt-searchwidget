#include "searchwidget.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPushButton>
#include <QAbstractItemView>

SearchWidget::SearchWidget(QWidget *parent) : QWidget(parent)
{
    this->buttonPadding = 10;
    this->flowLayout = new FlowLayout;
    this->setLayout(this->flowLayout);
    this->setAttribute(Qt::WA_StaticContents);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    _tagCompleterItemDelegate = new TagCompleterItemDelegate(this);
    this->initLineEdit();
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
    lineEdit = new SearchLine();
    lineEdit->setStyleSheet("border:#ccc 1px;");
    this->fontMetrics().height();
    lineEdit->resize(this->size().width(),this->fontMetrics().height() + 2 * this->buttonPadding);
    this->lineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    lineEditCompleter = new LineEditCompleter(this);
    lineEditCompleter->setCompletionMode(QCompleter::PopupCompletion);
    lineEdit->setCompleter(lineEditCompleter);

    connect(lineEdit, SIGNAL(returnPressed()), SLOT(addTag()));
    connect(lineEditCompleter, SIGNAL(completeFunished()),lineEdit, SLOT(clear()));
}

/**
 * @brief Search::addTag
 * It adds new tag with data
 *
 * @param data: text data
 */
void SearchWidget::addTag(const QString &data)
{
    //adding a new tag
    TagButton *tag = new TagButton(this);
    tag->setText(data);
    this->tagList.append(tag);
    this->flowLayout->removeWidget(this->lineEdit);
    this->flowLayout->addWidget(tag);
    this->flowLayout->addWidget(this->lineEdit);
    connect(tag, SIGNAL(deltag(TagButton*)), this, SLOT(removeTagSlot(TagButton*)) );
    this->repaint();
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
    //tag->setInternalId(index.internalId());
    tag->setIndex(index);
    this->tagList.append(tag);
    this->flowLayout->removeWidget(this->lineEdit);
    this->flowLayout->addWidget(tag);
    this->flowLayout->addWidget(this->lineEdit);
    connect(tag, SIGNAL(deltag(TagButton*)), this, SLOT(removeTagSlot(TagButton*)) );
    this->repaint();
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
            //if(tag->internalId() == index.internalId()) {
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
    this->model = model;
    this->lineEditCompleter->setModel(model);
    this->selModel = new QItemSelectionModel(model);

    //connect( selModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onItemSelected(QItemSelection,QItemSelection)) );
    lineEditCompleter->popup()->setItemDelegate(_tagCompleterItemDelegate); //Must be set after every time the model is set
    connect(lineEditCompleter, SIGNAL(activated(QModelIndex)),this, SLOT(insertSelection(QModelIndex)));
    return;
}

/**
 * @brief SearchWidget::setSelectionModel
 * @param selModel
 */
void SearchWidget::setSelectionModel(QItemSelectionModel *selModel)
{
    this->selModel = selModel;
    connect( this->selModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onTagSelected(QItemSelection,QItemSelection)) );
}

/**
 * @brief Search::addTag
 * It adds new tag to the scene
 */
void SearchWidget::addTag()
{
    QString data = lineEdit->text();
    if(!data.isEmpty())
    {
        addTag(data);
        lineEdit->clear();
    }
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
    lineEdit->resize((this->size().width() - 2*this->buttonPadding), this->fontMetrics().height() + 2*this->buttonPadding);
}

/**
 * @brief SearchWidget::insertSelection
 * @param current index
 */
void SearchWidget::insertSelection(QModelIndex curIndex)
{
/*
    QString str = curIndex.data().toString();
    //QModelIndex index = (itemModel)->indexByName(str,0);
    QModelIndex index = (this->model)->index(1,1);
    QItemSelection selection = QItemSelection(index,index);
    this->selectionModel()->select(selection, QItemSelectionModel::Select);
*/
    return;
}

/**
 * @brief SearchWidget::onTagSelected
 * @param topLeft
 * @param bottomRight
 */
void SearchWidget::onTagSelected(const QItemSelection & selected, const QItemSelection & deselected)
{
    qDebug() << "SearchWidget::onTagSelected(...)";
    QModelIndexList list;

    list = deselected.indexes();
    for(int i = 0; i < list.count(); i++) {
        this->removeTag(list.at(i));
        qDebug() << "deselected name = "<< this->model->data(list.at(i)) << "; id=" << list.at(i).internalId();
    }

    list = selected.indexes();
    for(int i = 0; i < list.count(); i++) {
        this->addTag(list.at(i));
        qDebug() << "selected name = "<< this->model->data(list.at(i)) << "; id=" << list.at(i).internalId();
    }
    return;
}

/**
 * @brief SearchWidget::paintEvent
 */
void SearchWidget::paintEvent(QPaintEvent *event)
{
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

void SearchWidget::calcSize()
{
    //! [2] calc line edit competer size
    QRect widgetRect(this->rect().top(), this->rect().left(), this->rect().width() - 1, this->rect().height() - 1);
    //! [2]
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
 * @brief Handles the timer event: update tags on scene
 * @param event
 */
void SearchWidget::timerEvent(QTimerEvent *event)
{
    return;
}

