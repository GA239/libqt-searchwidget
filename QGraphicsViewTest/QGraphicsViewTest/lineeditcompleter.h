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
class LineEditCompleter : public QCompleter
{
    Q_OBJECT

   public:
       LineEditCompleter(QAbstractItemModel * model, QObject * parent = 0);
       LineEditCompleter(const QStringList  &list, QObject * parent = 0);
       LineEditCompleter(QObject * parent = 0);
       bool eventFilter(QObject *o, QEvent *e);

signals:
       bool completeFunished();
       bool completeFinished(QModelIndex index);

private:

protected:

};

#endif // CustomCompleter_H
