#ifndef TAGCOMPLETERITEMDELEGATE_H
#define TAGCOMPLETERITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QPainter>
#include <QObject>


//class TagCompleterItemDelegate : public QStyledItemDelegate
class TagCompleterItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    TagCompleterItemDelegate(QObject *parent, QFont font = QFont());
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    bool editorEvent( QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index );

    QFont _font;

signals:
       mouseButtonPressed(const QModelIndex &index);

};

#endif // TAGCOMPLETERITEMDELEGATE_H
