#ifndef MYSECONDTAG_H
#define MYSECONDTAG_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QWidget>
#include <QPainter>


class CustomGraphicsView;

class Tag : public QObject,  public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Tag(QObject *parent = 0);

    Tag(QPointF position, const QString &data, CustomGraphicsView *graphView = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*,QWidget*);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* pe);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* pe);
    void calculateForces(void);
    bool advance(void);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void    setFont(QFont font);
    void    setThickness(int thickness);
    void    setHeight(int height);
    int     getWidth();
    int     getHeight();

signals:
     void   delnode(Tag* node);

private:
    CustomGraphicsView *view;
    QPointF newNodePosition;
    QString _data;
    QFont   _font;
    int     _height;
    int     _thickness;
    int     _width;
public slots:
};

#endif // MYSECONDTAG_H
