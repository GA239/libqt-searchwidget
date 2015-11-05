#include "mytagitem.h"

#include <QApplication>

MyTagItem::MyTagItem(QPoint position, const QString& data) //todo: все параметры в конструктор
{
    _position = position;
    _data = data;
    _font = QFont("times",36);
    _thickness = 3;

    QFontMetrics metrics(_font);
    _width = metrics.width(_data) + 10;
    _height = metrics.height();
}

QRectF MyTagItem::boundingRect() const
{
    return QRectF(_position,QSizeF(_width,_height));
}

void MyTagItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->setPen(QPen(Qt::red,_thickness));
    painter->drawRect(this->boundingRect());

    QTextOption option;
    option.setAlignment(Qt::AlignCenter);
    option.setAlignment(Qt::AlignHCenter);

    painter->setFont(_font);
    painter->setPen(QPen(Qt::blue));
    painter->drawText(this->boundingRect(),_data,option);
    painter->restore();
}

void MyTagItem::mousePressEvent(QGraphicsSceneMouseEvent *pe)
{
    //QApplication::setOverrideCursor(Qt::PointingHandCursor);
    //QGraphicsItem::mousePressEvent(pe);
    emit delnode(this);
}

void MyTagItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *pe)
{
    QApplication::restoreOverrideCursor();
    QGraphicsItem::mouseReleaseEvent(pe);
    //emit delnode(this);
}

void MyTagItem::setFont(QFont font)
{
    _font = font;
    _width = (_font.pointSize() * _data.size());
}

void MyTagItem::setThickness(int thickness)
{
    _thickness = thickness;
}

void MyTagItem::setHeight(int height)
{
    _height = height;
}

void MyTagItem::setPos(QPoint pos)
{
    _position = pos;
}

int MyTagItem::getWidth()
{
    return _width;
}

int MyTagItem::getHeight()
{
    return _height;
}

