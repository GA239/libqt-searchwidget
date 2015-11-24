#include "CustomCompleter.h"

#include <QAbstractItemView>
#include <QEvent>
#include <QKeyEvent>

CustomCompleter::CustomCompleter(QAbstractItemModel* model, QObject* parent) :
        QCompleter(model,parent)
{
}

CustomCompleter::CustomCompleter(const QStringList &list, QObject* parent) :
        QCompleter(list,parent)
{
}

CustomCompleter::CustomCompleter(QObject *parent):
    QCompleter(parent)
{
}

/**
 * @brief CustomCompleter::eventFilter
 *
 * rewrited eventFilter, need to clean up lineedit after you add the tag
 *
 * @param o
 * @param e
 * @return
 */
bool CustomCompleter::eventFilter(QObject *o, QEvent *e)
{
    return QCompleter::eventFilter(o,e);
}
