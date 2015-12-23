#include "tagcompleteritemdelegate.h"
#include <QFontDatabase>
#include <QEvent>

<<<<<<< HEAD
/**
 * @brief Default constructor.
 * @param parent
 */
TagCompleterItemDelegate::TagCompleterItemDelegate(QObject *parent)
        :QStyledItemDelegate(parent)
=======
TagCompleterItemDelegate::TagCompleterItemDelegate(QObject *parent, QFont font)
        :QItemDelegate(parent)
>>>>>>> dea7b3eb2d9a3e3caada4c83e5cb1bd327c62c4d
{
}
/**
 * @brief Function is called when a comleter list row needed to repaint.
 * @param painter
 * @param option
 * @param index
 */
void TagCompleterItemDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    // focus
<<<<<<< HEAD
    if (option.state & QStyle::State_HasFocus) {
=======
    if ((option.state & QStyle::State_HasFocus) || (option.state &  QStyle::State_MouseOver))
    {
>>>>>>> dea7b3eb2d9a3e3caada4c83e5cb1bd327c62c4d
        painter->fillRect(option.rect, QColor(0xb0,0xb0,0xb0));
        painter->setPen(QPen(QColor(0,0,0)));
    }
    else {
        painter->fillRect(option.rect, Qt::white);
        painter->setPen(QPen(QColor(0xb0,0xb0,0xb0)));
    }
    //
    QString title = index.data(Qt::DisplayRole).toString();
    QRect r = option.rect.adjusted(5, 0, 100, -10);
    //painter->drawRect(r);
    painter->drawText(r.left(), r.top()-10, r.width() + 45, r.height(), Qt::AlignBottom|Qt::AlignLeft, title, &r);


}
/**
 * @brief Returns the recommended size of the comleter list row.
 * @param option
 * @param index
 * @return
 */
QSize TagCompleterItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(200,65);
}

<<<<<<< HEAD
=======
/**
 * @brief TagCompleterItemDelegate::editorEvent
 *
 * Rewrite  editing event handler
 *
 * @param event
 * @param model
 * @param option
 * @param index
 * @return
 */
bool TagCompleterItemDelegate::editorEvent( QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index )
{
    Q_ASSERT(event);
    Q_ASSERT(model);
    /*
    if (event->type() == QEvent::MouseButtonPress)
    {
      emit this->mouseButtonPressed(index);
    }
    */
    return false;
}
>>>>>>> dea7b3eb2d9a3e3caada4c83e5cb1bd327c62c4d
