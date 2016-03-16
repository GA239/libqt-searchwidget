#include "searchwidget.h"

SearchWidget::SearchWidget() :QScrollArea()
{
    this->setBackgroundRole(QPalette::Button);
    this->setStyleSheet("border:#ccc 1px;");
    this->setWidgetResizable(true);
    this->flowWidget = new FlowWidget(this);
    this->setWidget(this->flowWidget);

    QScrollBar* scrollbar = this->verticalScrollBar();
    QObject::connect(scrollbar, SIGNAL(rangeChanged(int,int)), this, SLOT(moveScrollBarToBottom(int, int)));
    this->lineEdit->setFocus();
}

void SearchWidget::setModel(QAbstractItemModel *model)
{
    this->flowWidget->setModel(model);
    return;
}

void SearchWidget::setSelectionModel(QItemSelectionModel *selModel)
{
    this->flowWidget->setSelectionModel(selModel);
    return;
}

QStringList SearchWidget::unfindedTags()
{
    return this->flowWidget->unfindedTags();
}

QModelIndexList SearchWidget::tags()
{
    return this->flowWidget->tags();
}

QItemSelectionModel *SearchWidget::selectionModel() const
{
    return this->flowWidget->selectionModel();
}

void SearchWidget::setEnableNewTagCreation(bool status)
{
    this->flowWidget->setEnableNewTagCreation(status);
    return;
}

TagButton *SearchWidget::getTagByIndex(const QModelIndex index)
{
    return this->flowWidget->getTagByIndex(index);
}

/**
 * @brief SearchWidget::addTags
 * @param indexList
 */
void SearchWidget::addTags(QModelIndexList indexList)
{
    for(int i = 0; i < indexList.count(); i++) {
        this->flowWidget->addTag(indexList.at(i));
    }
    return;
}

void SearchWidget::moveScrollBarToBottom(int min, int max)
{
    Q_UNUSED(min);
    this->verticalScrollBar()->setValue(max);
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
    if(this->enableNewTagCreation) {
        QString leftSide = text.right(1);
        if(leftSide == ",") {
            QString name = text.left(text.length() - 1);
            this->addTag(name);
            this->lineEdit->clear();
        }
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
    //QPalette palatte = this->palette();
    calcSize();
    QPainter painter(this);
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::white);
    QRect widgetRect(this->rect().top(), this->rect().left(), this->rect().width() - 1, this->rect().height() - 1);
    painter.drawRect(widgetRect);
    //QRect usedRect(this->rect().top(), this->rect().left(), this->rect().width(), this->lineEdit->rect().bottom());

    return;
}

/**
 * @brief Calculates the size of the base elements of the widget
 */
void SearchWidget::calcSize()
{
    //! [2] calc line edit competer size
    //QRect widgetRect(this->rect().top(), this->rect().left(), this->rect().width(), this->rect().height());
    //! [2]
    if(this->childrenNumber != this->children().count())
    {
        this->childrenNumber = this->children().count();
        this->tagSpace = calcTagsSpace();
    }

    bool rollBackLater = false;
    int newWidth = this->size().width() - this->fixedSpace  - this->tagSpace;
    if(newWidth < this->lineEdit->minimumWidth()){
       newWidth = this->size().width() - this->fixedSpace;
       this->tagRowNumber++;
       rollBackLater = true;
    }
    if(this->lineEditWidth != newWidth)
        this->lineEditWidth = newWidth;

    this->lineEdit->setFixedSize(this->lineEditWidth, this->fontMetrics().height() + 2*this->buttonPadding);

    int newHeight = (this->fontMetrics().height() + 2*this->buttonPadding + verticalSpacing) * this->tagRowNumber + this->buttonPadding;

    if(rollBackLater)
        this->tagRowNumber--;

    if(newHeight != this->widgetHeight){
       this->widgetHeight = newHeight;
       this->update();
    }

    this->setFixedHeight(this->widgetHeight);
    this->flowLayout->setGeometry(QRect(this->rect().top(), this->rect().left(), this->rect().width(), this->widgetHeight));

    lineEditCompleter->popup()->setGeometry(mapToGlobal(this->rect().bottomLeft()).x(),         //popup left top x
                                            mapToGlobal(this->rect().bottomLeft()).y(),         //popup left top y
                                            lineEditCompleter->popup()->size().width(),         //popup width
                                            lineEditCompleter->popup()->size().height());       //popup height
    return;
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

/**
 * @brief Sets enable or disable adding undefinded tag in search widget
 * @param status
 */
void SearchWidget::setEnableNewTagCreation(bool status)
{
    this->enableNewTagCreation = status;
}

