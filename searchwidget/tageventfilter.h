#ifndef TAGEVENTFILTER_H
#define TAGEVENTFILTER_H

#include <QObject>
#include <QLineEdit>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QDebug>

class TagEventFilter : public QObject
{
    Q_OBJECT
public:
    TagEventFilter(QLineEdit* lineEdit, QObject* parent = NULL)
       :QObject(parent)
       ,mLineEdit(lineEdit)
    { }
    virtual ~TagEventFilter()
    { }

    bool eventFilter(QObject* watched, QEvent* event)
    {
       qDebug()<<event->type();
       QAbstractItemView* view = qobject_cast<QAbstractItemView*>(watched);
       if (event->type() == QEvent::Leave)
       {
           mLineEdit->clear();
           view->hide();
           return true;
       }
       return false;
    }

 private:
    QLineEdit* mLineEdit;
};

#endif // TAGEVENTFILTER_H
