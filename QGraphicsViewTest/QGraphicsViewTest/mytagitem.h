#ifndef MYTAGITEM_H
#define MYTAGITEM_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <QObject>

//class MyTagItem : public QGraphicsItem
class MyTagItem : public QGraphicsObject
{

    Q_OBJECT

public:
    MyTagItem(QPoint position, const QString &data);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*,QWidget*);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* pe);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* pe);

    void    setFont(QFont font);
    void    setThickness(int thickness);
    void    setHeight(int height);
    void    setPos(QPoint pos);

    int     getWidth();
    int     getHeight();


signals:
     void   delnode(MyTagItem* node);

private:
    QPoint  _position;
    QString _data;
    QFont   _font;
    int     _height;
    int     _thickness;
    int     _width;

};

#endif // MYTAGITEM_H
