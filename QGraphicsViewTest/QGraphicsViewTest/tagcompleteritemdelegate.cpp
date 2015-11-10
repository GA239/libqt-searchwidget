#include "tagcompleteritemdelegate.h"
#include <QFontDatabase>

TagCompleterItemDelegate::TagCompleterItemDelegate(QObject *parent, QFont font)
        :QStyledItemDelegate(parent)
{
    _font = font;
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
    if (option.state & QStyle::State_HasFocus)
    {
        painter->fillRect(option.rect, QColor(0xb0,0xb0,0xb0));
        painter->setPen(QPen(QColor(0,0,0)));
    }
    else
    {
        painter->fillRect(option.rect, Qt::white);
        painter->setPen(QPen(QColor(0xb0,0xb0,0xb0)));
    }
    QString title = index.data(Qt::DisplayRole).toString();
    QRect r = option.rect.adjusted(5, 0, 100, -10);
    painter->setFont(_font);
    painter->drawText(r.left(), r.top()-10, r.width() + 45, r.height(), Qt::AlignBottom|Qt::AlignLeft, title, &r);


/*
    QPen pen2(QColor(0xb0,0xb0,0xb0));
    painter->setPen(pen2);
    painter->setFont(QFont("times",12));
    r = option.rect.adjusted(5, 16+30, 0, 0);
    painter->drawText(r.left(), r.top(), r.width()-120, r.height(), Qt::AlignLeft|Qt::TextWordWrap, num + " документов", &r);
*/
}
/**
 * @brief TagCompleterItemDelegate::sizeHint
 * @param option
 * @param index
 * @return
 */
QSize TagCompleterItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    return QSize(100,65);
}
