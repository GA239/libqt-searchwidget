#include "searchwidget.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPushButton>
#include <QAbstractItemView>
#include <QAbstractProxyModel>

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
    this->enableNewTagCreation = true;
    this->flowLayout = new FlowLayout;

    this->setLayout(this->flowLayout);
    this->setAttribute(Qt::WA_StaticContents);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    tagCompleterItemDelegate = new TagCompleterItemDelegate(this);
    //! [1]


    //! [2]
    lineEdit = new SearchLine();
    lineEdit->setStyleSheet("border:#ccc 1px;");
    this->lineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    lineEditCompleter = new LineEditCompleter(this);
    lineEditCompleter->setModel(this->model);
    lineEditCompleter->setWrapAround(false);
    lineEditCompleter->setCompletionMode(QCompleter::PopupCompletion);
    lineEditCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    lineEditCompleter->popup()->setStyleSheet("border: 1px solid black");
    lineEdit->setCompleter(lineEditCompleter);
    //lineEditCompleter->setWidget(this);

    closeButton = new CloseButton(this);

    connect(closeButton, SIGNAL(pressed()), this, SLOT(clear()));
    connect(lineEdit, SIGNAL(returnPressed()), SLOT(onReturnPressed()));
    //connect(lineEditCompleter, SIGNAL(activated(QModelIndex)),this, SLOT(onCompleterFinished(QModelIndex)));
    connect(lineEditCompleter, SIGNAL(completeFinished(QModelIndex)),this, SLOT(onCompleterFinished(QModelIndex)));
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(onSearchTextChanged(QString)) );

    this->flowLayout->addWidget(lineEdit);
    this->flowLayout->addWidget(closeButton);

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
    addTag(tag);
    return;
}

/**
 * @brief Creates and adds new TagButton element to widget.
 * @param index associated with tag; name of tag also takes from index
 */
void SearchWidget::addTag(const QModelIndex index)
{
    TagButton *tag = new TagButton(this);
    tag->setText(this->model->data(index, Qt::DisplayRole).toString());
    tag->setIndex(index);
    addTag(tag);
    return;
}

/**
 * @brief Adds a new TagButton element to widget and calculates the size for LineEdit.
 * @param tag - TagButton element.
 */
void SearchWidget::addTag(TagButton *tag)
{
    this->flowLayout->removeWidget(this->lineEdit);
    this->flowLayout->removeWidget(this->closeButton);
    this->flowLayout->addWidget(tag);

    int closeButtonWidth = this->closeButton->minimumWidth() + this->flowLayout->spacing();
    int lastTagLength = tag->minimumWidth() + flowLayout->spacing();
    int length = calcTagsSpace(false) + lastTagLength + closeButtonWidth;

    int newWidth = this->lineEdit->size().width() - lastTagLength;

    if(this->size().width() - length <  this->lineEdit->minimumWidth())
    {
        int rest = this->size().width() - 2*this->buttonPadding;
        newWidth = rest - closeButtonWidth;
    }
    this->lineEdit->setFixedSize(newWidth,this->lineEdit->size().height());

    this->flowLayout->addWidget(this->lineEdit);
    this->flowLayout->addWidget(this->closeButton);

    connect(tag, SIGNAL(deltag(TagButton*)), this, SLOT(removeTagSlot(TagButton*)) );

    this->lineEdit->repaint();
    this->flowLayout->update();
    this->repaint();
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

        int closeButtonWidth = this->closeButton->minimumWidth() + this->flowLayout->spacing();
        int tagsSpace = calcTagsSpace(true);

        int stringLength = tagsSpace - tag->minimumWidth() - flowLayout->spacing() - closeButtonWidth;
        int newWidth = this->size().width() - 2*this->buttonPadding - stringLength;

        if(newWidth + closeButtonWidth + tagsSpace > this->size().width() - 2*this->buttonPadding)
        {
            newWidth = this->size().width() - 2*this->buttonPadding;
        }
        lineEdit->setFixedSize(newWidth, this->fontMetrics().height() + 2*this->buttonPadding);

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
    int closeButtonWidth = this->closeButton->minimumWidth() + this->flowLayout->spacing();
    lineEdit->setFixedSize((this->size().width() - 2*this->buttonPadding - closeButtonWidth), this->fontMetrics().height() + 2*this->buttonPadding);

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


    int closeButtonWidth = this->closeButton->minimumWidth() + this->flowLayout->spacing();
    int tagsSpace = calcTagsSpace(true);

    int stringLength = tagsSpace - tag->minimumWidth() - flowLayout->spacing() - closeButtonWidth;
    int newWidth = this->size().width() - 2*this->buttonPadding - stringLength;

    if(newWidth + closeButtonWidth + tagsSpace > this->size().width() - 2*this->buttonPadding)
    {
        newWidth = this->size().width() - 2*this->buttonPadding;
    }
    lineEdit->setFixedSize(newWidth, this->fontMetrics().height() + 2*this->buttonPadding);


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
    int closeButtonWidth = this->closeButton->minimumWidth() + this->flowLayout->spacing();
    int newWidth = this->size().width() - 2*this->buttonPadding - calcTagsSpace(true) - closeButtonWidth;
    if(newWidth < this->lineEdit->minimumWidth())
    {
       newWidth = this->size().width() - 2*this->buttonPadding - closeButtonWidth;
    }
    this->lineEdit->setFixedSize(newWidth, this->fontMetrics().height() + 2*this->buttonPadding);
    lineEditCompleter->popup()->setFixedWidth(this->size().width());
}

int SearchWidget::minimumHeight()
{
    return this->lineEdit->sizeHint().height() + 4 * this->buttonPadding;
}

int SearchWidget::minimumWidth()
{
    return this->width();
}

QSize SearchWidget::minimumSize()
{
    QSize size;
    size.setHeight(this->minimumHeight());
    size.setWidth(this->minimumWidth());
    return size;
}

/**
 * @brief Returns the recommended size of the search line.
 * Reimplemented method.
 *
 * @return
 */
QSize SearchWidget::sizeHint()
{
    QSize size;
    size.setHeight(this->minimumHeight());
    size.setWidth(this->minimumWidth());
    return size;
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
 * @brief Ñalculates the space occupied by the last line of tags.
 * @param if lastTag == true then calculates with the last tag, else
 * without  the last tag.
 */
int SearchWidget::calcTagsSpace(bool lastTag)
{
    TagButton *tag;
    QVector< QVector<int> > indices;
    QVector<int> tagsNumberInRow;
    QVector<int> currentRow;

    int currentRowNumber = -1;
    int currentYPos = -1;
    tagsNumberInRow.push_back(0);

    int count = this->children().count();

    if(!lastTag)
        count--;

    for(int i = 0; i < count ; i++){
        tag = qobject_cast<TagButton *>(this->children().at(i));
        if(tag != NULL){
            if(currentYPos != tag->y())
            {
                currentYPos = tag->y();
                currentRowNumber++;
                tagsNumberInRow.push_back(0);
                if(currentRow.length() != 0)
                    indices.push_back(currentRow);
                currentRow.clear();
            }
            currentRow.push_back(i);
            tagsNumberInRow[currentRowNumber]++;
        }
    }
    indices.push_back(currentRow);

    int l = 0;
    for(int k = 0; k < indices[indices.length()-1].length(); k++)
    {
        tag = qobject_cast<TagButton *>(this->children().at(indices[indices.length()-1][k]));
        l+= tag->minimumWidth();
    }
    return l + this->flowLayout->spacing() * tagsNumberInRow[indices.length()-1];
}

/**
 * @brief Action on the end of the selection item in the comleter list.
 * @param proxyIndex - index in completion model
 */
void SearchWidget::onCompleterFinished(QModelIndex proxyIndex)
{
    if(proxyIndex.isValid()) {
        QAbstractProxyModel* proxyModel = qobject_cast<QAbstractProxyModel*>(this->lineEditCompleter->completionModel());
        Q_ASSERT(proxyModel != 0);
        QModelIndex index = proxyModel->mapToSource(proxyIndex);
        if(index.isValid()) {
            this->insertSelection(index);
            this->lineEdit->clear();
        }
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
    QPainter painter(this);
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::white);
    QRect widgetRect(this->rect().top(), this->rect().left(), this->rect().width() - 1, this->rect().height() - 1);
    painter.drawRect(widgetRect);
    QRect usedRect(this->rect().top(), this->rect().left(), this->rect().width(), this->lineEdit->rect().bottom());
    lineEdit->resize((this->size().width() - 2*this->buttonPadding), this->fontMetrics().height() + 2*this->buttonPadding);

    /*
    if(this->lineEditCompleter->popup()->isVisible()){
        QRect rect = QRect(this->rect().bottomLeft(),QSize(this->size().width(),0));
        this->lineEditCompleter->complete(rect);
    }
    */

    lineEditCompleter->popup()->setGeometry(mapToGlobal(this->rect().topLeft()).x(),            //popup left top x
                                            mapToGlobal(this->lineEdit->pos()).y() -1           //popup left top y
                                            + this->lineEdit->height() + this->buttonPadding,
                                            lineEditCompleter->popup()->size().width(),         //popup width
                                            lineEditCompleter->popup()->size().height());       //popup height

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

