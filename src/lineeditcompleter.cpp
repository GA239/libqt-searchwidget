#include "LineEditCompleter.h"

#include <QAbstractItemView>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

#include <QGraphicsProxyWidget>

/**
 * @brief Constructor
 * @param model
 * @param parent
 */
LineEditCompleter::LineEditCompleter(QAbstractItemModel* model, QObject* parent) :
        QCompleter(model,parent)
{
    this->timerId = 0;
    connect(this, SIGNAL(activated(QModelIndex)), this, SLOT(onActivated(QModelIndex)) );
}

/**
 * @brief Constructor
 * @param list
 * @param parent
 */
LineEditCompleter::LineEditCompleter(const QStringList &list, QObject* parent) :
        QCompleter(list,parent)
{
    this->timerId = 0;
    connect(this, SIGNAL(activated(QModelIndex)), this, SLOT(onActivated(QModelIndex)) );
}

/**
 * @brief Constructor
 * @param parent
 */
LineEditCompleter::LineEditCompleter(QObject *parent):
    QCompleter(parent)
{
    this->timerId = 0;
    connect(this, SIGNAL(activated(QModelIndex)), this, SLOT(onActivated(QModelIndex)) );

    QPoint pos = QPoint(0,0);
    int w = 100;
    int h = 100;
    QRect geometry(pos.x(), pos.y(), w, h);
    QGraphicsProxyWidget *proxyWidget = this->popup()->graphicsProxyWidget();
    if (proxyWidget)
        proxyWidget->setGeometry(geometry);
    else
        this->popup()->setGeometry(geometry);
}

/**
 * @brief Rewrited eventFilter. Function is called when a search completer event occurs.
 * @param object
 * @param event
 * @return
 */
bool LineEditCompleter::eventFilter(QObject *object, QEvent *event)
{
    bool eventResuslt = QCompleter::eventFilter(object,event);
    if(eventResuslt) {
         if(event->type() == QEvent::KeyPress){
            QKeyEvent *keyEvent = (QKeyEvent *)(event);
            const int key = keyEvent->key();
            if ((key == Qt::Key_Return) || (key == Qt::Key_Enter)) {
                ;
            }
         }
    }
    return eventResuslt;
}

/**
 * @brief Schedules clear search line text (timeout is 1 ms)
 * Use this when text in search line must be cleared after
 * receiving all events from completer and other emited text changes.
 *
 * @param index
 */
void LineEditCompleter::onActivated(QModelIndex index)
{
    this->activatedIndex = index;
    if (!this->timerId) {
        this->timerId = startTimer(1);
    }
}

/**
 * @brief Function is called when a timer event occurs, used for
 * emiting message about end of selection.
 *
 * @param event - parameters describe timer event.
 */
void LineEditCompleter::timerEvent(QTimerEvent *event)
{
    QCompleter::timerEvent(event);
    if(event->timerId() == this->timerId) {
        killTimer(this->timerId);
        this->timerId = 0;
        emit this->completeFinished(this->activatedIndex);
    }
    return;
}

