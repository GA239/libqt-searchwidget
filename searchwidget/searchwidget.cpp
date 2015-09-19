#include "searchwidget.h"
#include <QFileIconProvider>
#include <QFontDatabase>

SearchWidget::SearchWidget(QWidget *parent, bool defaultFont) : QWidget(parent)
{
    //initial params
    buttonPadding = 10;//10px
    padding = 5;//5px
    fontHeight = 22;//??
    //
    height = parent->height();
    width = parent->width();
    buttonStyle = "";
    this->defaultFont = defaultFont;
    //frame init
    frame = new QFrame(parent);
    frame->setFrameStyle(QFrame::Sunken | QFrame::Box);
    frame->setGeometry(0,0,parent->width(),parent->height());
    frame->setObjectName("searchFrame");
    searchLine = new QLineEdit(frame);
    searchLine->setGeometry(1,1,parent->width()-2,parent->height()-2);
    //define default/segoe font
    if(!defaultFont)
    {
        int id = QFontDatabase::addApplicationFont(":/fonts/fonts/segoeui.ttf");
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        font = QFont(family, 22, QFont::Normal,false);
    }
    else
    {
        font = QFont();
    }
    searchLine->setFont(font);
    //completer initialization
    completer = new TagCustomCompleter(this);
    completer->setWidget(this);
    completer->setCompletionColumn(1);
    tagCompleterItemDelegate = new TagCompleterItemDelegate(this, defaultFont);
    completer->popup()->setItemDelegate(tagCompleterItemDelegate);
    completer->popup()->setSelectionMode(QAbstractItemView::SingleSelection);
    completer->setCompletionRole(Qt::DisplayRole);
    TagEventFilter* filter = new TagEventFilter(searchLine);
    completer->popup()->installEventFilter(filter);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    searchLine->setCompleter(completer);
    //close/erase button
    close_btn = new QTagLabelButton(frame,defaultFont);
    close_btn->setFontHeight(fontHeight);
    close_btn->setPadding(padding);
    close_btn->setButtonPadding(buttonPadding);
    close_btn->setText("");
    close_btn->setGeometry(parent->width() - buttonPadding - 15,(parent->height()/2) -7,15,15);
    if(buttonStyle.length()>0)
    {
        close_btn->setStyleSheet(buttonStyle);
    }
    close_btn->setMargin(padding);
    close_btn->setCursor(Qt::ArrowCursor);
    close_btn->show();

    flowLayout = new FlowLayout(frame);
    flowLayout->setSizeConstraint(QLayout::SetMaximumSize);
    flowLayout->setGeometry(frame->geometry());
    lentag = 0;
    //close/erase button click event
    connect(close_btn, SIGNAL(clicked(QTagLabelButton*)),
                              this, SLOT(clearSelectionBtn()));
}

SearchWidget::~SearchWidget()
{

}

/**
 * @brief SearchWidget::model
 * @return
 */
QAbstractItemModel *SearchWidget::model()
{
    return this->itemModel;
}
/**
 * @brief SearchWidget::setModel
 * @param model
 */
void SearchWidget::setModel(QAbstractItemModel *model)
{
    this->itemModel = model;
    completer->setModel(itemModel);
    selModel = new QItemSelectionModel(itemModel);
    connect( selModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onItemSelected(QItemSelection,QItemSelection)) );
    completer->popup()->setItemDelegate(tagCompleterItemDelegate); //Must be set after every time the model is set
    connect(completer, SIGNAL(activated(QModelIndex)),
                          this, SLOT(insertSelection(QModelIndex)));
    return;
}

/**
 * @brief SearchWidget::selectionModel
 * @return
 */
QItemSelectionModel *SearchWidget::selectionModel() const
{
    return this->selModel;
}

/**
 * @brief SearchWidget::setSelectionModel
 */
void SearchWidget::setSelectionModel(QItemSelectionModel *selectionModel)
{
    this->selModel = selectionModel;
    connect( selModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(onItemSelected(QItemSelection,QItemSelection)) );
}

/**
 * @brief SearchWidget::selectionMode
 * @return
 */
QAbstractItemView::SelectionMode SearchWidget::selectionMode() const
{
    return this->selMode;
}

/**
 * @brief SearchWidget::setSelectionMode
 * @param mode
 */
void SearchWidget::setSelectionMode(QAbstractItemView::SelectionMode mode)
{
    this->selMode = mode;
}

/**
 * @brief SearchWidget::getSearchString
 * @return
 */
QString SearchWidget::getSearchString()
{
    return this->searchLine->text();
}

/**
 * @brief SearchWidget::insertSelection
 * @param current index
 */
void SearchWidget::insertSelection(QModelIndex curIndex)
{
    QString str = curIndex.data().toString();
    QModelIndex index = ((GraphProxyModel*)itemModel)->indexByName(str,0);
    QItemSelection selection = QItemSelection(index,index);
    selectionModel()->select(selection, QItemSelectionModel::Select);
}

/**
 * @brief SearchWidget::insertCompletion
 * @param current index
 */
void SearchWidget::insertCompletion(QModelIndex curIndex)
{
    QString str = curIndex.data().toString();
    QFontMetrics fm(font);
    qDebug()<<str;
    //lentag += fm.width(str)+20;
    lentag += fm.width(str)+2*padding+2*buttonPadding+fontHeight;
    QTagLabelButton *btn = new QTagLabelButton(this, defaultFont);
    btn->setFontHeight(fontHeight);
    btn->setPadding(padding);
    btn->setButtonPadding(buttonPadding);
    btn->setText(str);
    btn->setGeometry(0,5,fm.width(str)+padding+2*buttonPadding+fontHeight,((QWidget*)parent())->height()-10);
    if(buttonStyle.length()>0)
    {
        btn->setStyleSheet(buttonStyle);
    }
    btn->setMargin(padding);
    flowLayout->addWidget(btn);
    btn->setCursor(Qt::ArrowCursor);
    btn->show();

    connect(btn, SIGNAL(clicked(QTagLabelButton*)),
                          this, SLOT(removeBtn(QTagLabelButton*)));

    searchLine->setGeometry(1 + lentag,1,width - lentag - 2,height - 2);
    searchLine->setText(" ");
    itemMap.insert(str,curIndex);
}

/**
 * @brief SearchWidget::removeBtn
 * @param current button for delete
 */
void SearchWidget::removeBtn(QTagLabelButton *btn)
{
    QString str = btn->text();
    QFontMetrics fm(font);
    //lentag -= (fm.width(btn->text())+20);
    lentag -=  (fm.width(str)+2*padding+2*buttonPadding+fontHeight);
    delete flowLayout->itemAt(flowLayout->indexOf(btn))->widget();
    searchLine->setGeometry(1 + lentag,1,width - lentag - 2,height - 2);
    if(itemMap.contains(str))
    {
        selModel->select(itemMap.value(str), QItemSelectionModel::Deselect);
        itemMap.remove(str);
    }
}

/**
 * @brief SearchWidget::clearAllBtn
 * removes all buttons
 */
void SearchWidget::clearAllBtn()
{
    foreach(QLayoutItem *item,flowLayout->itemList)
    {
        delete item->widget();
    }
    lentag = 0;
}

/**
 * @brief SearchWidget::clearSelectionBtn
 */
void SearchWidget::clearSelectionBtn()
{
    foreach(QLayoutItem *item,flowLayout->itemList)
    {
        removeBtn((QTagLabelButton*)item->widget());
    }

    searchLine->setText("");
}

/**
 * gets width
 */
int SearchWidget::getWidth() const
{
    return width;
}

/**
 * sets width
 */
void SearchWidget::setWidth(int value)
{
    width = value;
}

/**
 * gets height
 */
int SearchWidget::getHeight() const
{
    return height;
}

/**
 * sets height
 */
void SearchWidget::setHeight(int value)
{
    height = value;
}

/**
 * gets font height
 */
int SearchWidget::getFontHeight() const
{
    return fontHeight;
}

/**
 * sets font height
 */
void SearchWidget::setFontHeight(int value)
{
    fontHeight = value;
}

/**
 * gets padding
 */
int SearchWidget::getPadding() const
{
    return padding;
}

/**
 * sets padding
 */
void SearchWidget::setPadding(int value)
{
    padding = value;
}

/**
 * gets button padding
 */
int SearchWidget::getButtonPadding() const
{
    return buttonPadding;
}

/**
 * sets button padding
 */
void SearchWidget::setButtonPadding(int value)
{
    buttonPadding = value;
}

void SearchWidget::onItemSelected(const QItemSelection & selected, const QItemSelection & deselected )
{
    QModelIndexList list;
    list = selected.indexes();
    for(int i = 0; i < list.count(); i++)
    {
        insertCompletion(list.at(i));
    }
}

/**
 * sets search line style
 */
void SearchWidget::setSearchlineStyle(QString style)
{
    searchLine->setStyleSheet(style);
}

/**
 * sets frame style
 */
void SearchWidget::setFrameStyle(QString style)
{
    frame->setStyleSheet(style);
}

/**
 * sets tag buttons style
 */
void SearchWidget::setTagButtonStyle(QString style)
{
    buttonStyle = style;
}

/**
 * sets close button visible
 */
void SearchWidget::setClosebtnVisible(bool closebtnVisible)
{
    this->closebtnVisible = closebtnVisible;
    if(!closebtnVisible)close_btn->hide();
}
