#ifndef TAGCOMPLETERITEMDELEGATE_H
#define TAGCOMPLETERITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class TagCompleterItemDelegate : public QStyledItemDelegate
{
    QFont font1;
    QFont font2;
    //need to use defaylt font
    bool defaultFont;
public:
    TagCompleterItemDelegate(QObject *parent=0, bool defaultFont = true);
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    void setFonts(QFont font1,QFont font2){this->font1 = font1;this->font2 = font2;}
};

#endif // TAGCOMPLETERITEMDELEGATE_H
