#ifndef CustomCompleter_H
#define CustomCompleter_H

#include <QObject>
#include <QCompleter>


///
/// \brief The CustomCompleter class
///
/// This class will need to be if you want to extend
/// the functionality of autocompletion
///
class CustomCompleter : public QCompleter
{
    Q_OBJECT

   public:
       CustomCompleter(QAbstractItemModel * model, QObject * parent = 0);
       CustomCompleter(const QStringList  &list, QObject * parent = 0);
       CustomCompleter(QObject * parent = 0);
       bool eventFilter(QObject *o, QEvent *e);
};

#endif // CustomCompleter_H
