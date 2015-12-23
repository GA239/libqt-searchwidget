#include "tagcompleteritemdelegate.h"
#include <QFontDatabase>

/**
 * @brief Default constructor.
 * @param parent
 */
TagCompleterItemDelegate::TagCompleterItemDelegate(QObject *parent)
        :QStyledItemDelegate(parent)
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

