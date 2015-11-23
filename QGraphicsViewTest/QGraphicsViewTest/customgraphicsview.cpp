#include "customraphicsview.h"


CustomGraphicsView::CustomGraphicsView(QGraphicsScene* pScene, QWidget *pwgt)
    : QGraphicsView (pScene,pwgt)
{
    this->timerId = 0;
}

/**
 * @brief Handles the timer event: update tags on scene
 * @param event
 */
void CustomGraphicsView::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
//! [1] create list of Nodes and fill it from scene nodes
    QList<Tag *> tags;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Tag *tag = qgraphicsitem_cast<Tag *>(item))
            tags << tag;
    }
//! [1]
//! [2] calculate new position of nodes, used forces between nodes
    foreach (Tag *tag, tags) {
        tag->calculateForces();
    }
//! [2]
//! [3]
    bool itemsMoved = false;
    foreach (Tag *tag, tags) {
        if (tag->advance()) {
            itemsMoved = true;
        }
    }
//! [3]
//! [4]
    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
//! [4]
    return;
}

/**
 * @brief CustomGraphicsView::drawBackground
 * @param painter
 * @param rect
 */
void CustomGraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(QBrush(QColor(Qt::gray)));
    painter->drawRect(rect);
    return;
}

/**
 * @brief start update graph scene timer
 * you need to run this function when item is moved
 */
void CustomGraphicsView::itemMoved()
{
    if (this->timerId == 0) {
        timerId = startTimer(1000 / 25);
    }
    return;
}

