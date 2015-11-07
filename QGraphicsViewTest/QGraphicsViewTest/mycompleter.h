#ifndef MYCOMPLETER_H
#define MYCOMPLETER_H

#include <QObject>
#include <QCompleter>
#include <QAbstractItemView>

class MyCompleter : public QCompleter
{
    Q_OBJECT

   public:
       inline MyCompleter(QAbstractItemModel * model, QObject * parent = 0) :
               QCompleter(model,parent)
       {

       }
       inline MyCompleter(const QStringList & list, QObject * parent = 0) :
               QCompleter(list,parent)
       {
       }

private:
};

#endif // MYCOMPLETER_H
