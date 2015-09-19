#include "tagcompleteritemdelegate.h"
#include <QFontDatabase>

TagCompleterItemDelegate::TagCompleterItemDelegate(QObject *parent, bool defaultFont)
        :QStyledItemDelegate(parent)
{
    this->defaultFont = defaultFont;
    if(!defaultFont)
    {
        int id = QFontDatabase::addApplicationFont(":/fonts/fonts/segoeui.ttf");
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        font1 = QFont(family, 22, QFont::Normal,false);
        font2 = QFont(family, 9, QFont::Normal,false);
    }
    else
    {
        font1 = QFont();
        font2 = QFont();
    }
}

void TagCompleterItemDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    QString title = index.data(Qt::DisplayRole).toString();
    QString num = index.data(Qt::UserRole+10).toString();
    QRect r = option.rect.adjusted(5, 0, 0, -10);
    QPen pen1(QColor(0,0,0));
    painter->setPen(pen1);
    painter->setFont(font1);
    painter->drawText(r.left(), r.top()-10, r.width()-120, r.height(), Qt::AlignBottom|Qt::AlignLeft, title, &r);
    QPen pen2(QColor(0xb0,0xb0,0xb0));
    painter->setPen(pen2);
    painter->setFont(font2);
    r = option.rect.adjusted(5, 16+30, 0, 0);
    painter->drawText(r.left(), r.top(), r.width()-120, r.height(), Qt::AlignLeft|Qt::TextWordWrap, num + " документов", &r);
}

QSize TagCompleterItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    return QSize(200,60);
}
