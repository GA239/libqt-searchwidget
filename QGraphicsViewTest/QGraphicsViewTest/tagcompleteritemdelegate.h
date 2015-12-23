#ifndef TAGCOMPLETERITEMDELEGATE_H
#define TAGCOMPLETERITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QPainter>
#include <QObject>


//class TagCompleterItemDelegate : public QStyledItemDelegate
class TagCompleterItemDelegate : public QItemDelegate
{
<<<<<<< HEAD

public:
    TagCompleterItemDelegate(QObject *parent=0);
=======
    Q_OBJECT

public:
    TagCompleterItemDelegate(QObject *parent, QFont font = QFont());
>>>>>>> dea7b3eb2d9a3e3caada4c83e5cb1bd327c62c4d
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    bool editorEvent( QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index );

    QFont _font;

signals:
       mouseButtonPressed(const QModelIndex &index);

};

#endif // TAGCOMPLETERITEMDELEGATE_H
