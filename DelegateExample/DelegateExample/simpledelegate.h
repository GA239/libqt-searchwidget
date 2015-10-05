#ifndef SIMPLEDELEGATE_H
#define SIMPLEDELEGATE_H

#include <QtGui>
#include <QItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>

#include <QObject>

class SimpleDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    SimpleDelegate(QObject* pobj);
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    bool editorEvent( QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index );
    void setbuttonPressed(bool value);

private:
    bool buttonPressed;
    QColor color;
};

#endif // SIMPLEDELEGATE_H
