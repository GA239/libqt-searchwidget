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

