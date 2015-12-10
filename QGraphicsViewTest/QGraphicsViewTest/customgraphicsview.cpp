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

