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
    bool eventResuslt = QCompleter::eventFilter(o,e);
    if(eventResuslt)
     {
         if(e->type() == QEvent::KeyPress)
         {
            QKeyEvent *ke = (QKeyEvent *)(e);
            const int key = ke->key();

            if ((key == Qt::Key_Return) || (key == Qt::Key_Enter))
            {
                 emit completeFunished();
            }
         }
     }
    return eventResuslt;
}
