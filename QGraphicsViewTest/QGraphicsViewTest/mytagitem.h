#ifndef MYTAGITEM_H
#define MYTAGITEM_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>


class MyTagItem : public QGraphicsItem
{
public:
    MyTagItem(QPoint position, const QString &data);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem*,QWidget*);

    void setFont(QFont font);
    void setThickness(int thickness);
    void setHeight(int height);
    int getWidth();
    int getHeight();

private:
    QPoint _position;
    QString _data;
    QFont _font;
    int _height;
    int _thickness;
    int _width;
};

#endif // MYTAGITEM_H
