#include "LineEditCompleter.h"

#include <QAbstractItemView>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

/**
 * @brief LineEditCompleter::LineEditCompleter
 * @param model
 * @param parent
 */
LineEditCompleter::LineEditCompleter(QAbstractItemModel* model, QObject* parent) :
        QCompleter(model,parent)
{
}

/**
 * @brief LineEditCompleter::LineEditCompleter
 * @param list
 * @param parent
 */
LineEditCompleter::LineEditCompleter(const QStringList &list, QObject* parent) :
        QCompleter(list,parent)
{

}

/**
 * @brief LineEditCompleter::LineEditCompleter
 * @param parent
 */
LineEditCompleter::LineEditCompleter(QObject *parent):
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
bool LineEditCompleter::eventFilter(QObject *o, QEvent *e)
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
                /*qDebug() << "LineEditCompleter::eventFilter currentIndex currentRow = " << this->currentRow();
                QModelIndex curIndex = this->currentIndex();
                QString name = this->model()->data(curIndex, Qt::DisplayRole).toString();
                qDebug() << "LineEditCompleter::eventFilter currentIndex.name = " << name;
                qDebug() << "LineEditCompleter::eventFilter  currentCompletion = " << this->currentCompletion();
                */
                //emit this->completeFinished(this->currentIndex());
                emit this->completeFunished();
                emit this->completeFinished(this->currentIndex());
            }
         }
     }
    return eventResuslt;
}
