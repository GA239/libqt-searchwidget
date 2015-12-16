#include "tagcompleteritemdelegate.h"
#include <QFontDatabase>

TagCompleterItemDelegate::TagCompleterItemDelegate(QObject *parent)
        :QStyledItemDelegate(parent)
{
}

/**
 * @brief TagCompleterItemDelegate::paint
 *
 * function to redraw the list
 *
 * @param painter
 * @param option
 * @param index
 */
void TagCompleterItemDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    // focus
    if (option.state & QStyle::State_HasFocus) {
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
 * @brief TagCompleterItemDelegate::sizeHint
 * @param option
 * @param index
 * @return
 */
QSize TagCompleterItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    return QSize(200,65);
}

