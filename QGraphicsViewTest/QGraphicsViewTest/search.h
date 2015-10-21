#ifndef SEARCH_H
#define SEARCH_H

#include <QObject>
#include <QWidget>

#include "qgraphicsviewtest.h"
#include "mytagitem.h"

class Search : public QWidget
{
    Q_OBJECT
public:
    explicit Search(QWidget *parent = 0);
    virtual ~Search();
    void resizeEvent ( QResizeEvent * event );

    void initScene();
    void addTag(const QString &data);


    QGraphicsScene* scene;
    QGraphicsViewTest*  view;
    QPoint currentTagPoint;
    int _indent;

    int dataval;

signals:

public slots:
    void addTag();
};

#endif // SEARCH_H
