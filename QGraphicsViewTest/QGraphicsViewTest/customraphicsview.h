#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QObject>
#include "tag.h"


///
/// \brief The CustomGraphicsView class
///
/// This class will need to be if you want to extend
/// the functionality of graphic widget
///
class CustomGraphicsView : public QGraphicsView
{
public:
    CustomGraphicsView(QGraphicsScene* pScene, QWidget *pwgt=0);
    void itemMoved(void);

protected:
    void timerEvent(QTimerEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    int timerId;
};

#endif // CUSTOMGRAPHICSVIEW_H
