#ifndef QGRAPHICSVIEWTEST_H
#define QGRAPHICSVIEWTEST_H

#include <QGraphicsView>
#include <QObject>

class QGraphicsViewTest : public QGraphicsView
{
public:
    QGraphicsViewTest(QGraphicsScene* pScene, QWidget *pwgt=0);
};

#endif // QGRAPHICSVIEWTEST_H
