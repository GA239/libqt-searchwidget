#include "CustomCompleter.h"

#include <QAbstractItemView>

CustomCompleter::CustomCompleter(QAbstractItemModel* model, QObject* parent) :
        QCompleter(model,parent)
{
}

CustomCompleter::CustomCompleter(const QStringList &list, QObject* parent) :
        QCompleter(list,parent)
{

}
