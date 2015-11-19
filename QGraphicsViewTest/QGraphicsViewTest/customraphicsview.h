#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QObject>

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
};

#endif // CUSTOMGRAPHICSVIEW_H
