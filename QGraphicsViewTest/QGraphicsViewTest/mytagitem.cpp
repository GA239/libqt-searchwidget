#include "mytagitem.h"

MyTagItem::MyTagItem(QPoint position, const QString& data)
{
    _position = position;
    _data = data;
    _font = QFont("times",36);
    _height = 50;
    _thickness = 3;

    _width = _font.pointSize() * _data.size();

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

    painter->setFont(_font);
    painter->setPen(QPen(Qt::blue));
    painter->drawText(this->boundingRect(),_data,option);
    painter->restore();
}

void MyTagItem::setFont(QFont font)
{
    _font = font;
    _width = _font.pointSize() * _data.size();
}

void MyTagItem::setThickness(int thickness)
{
    _thickness = thickness;
}

void MyTagItem::setHeight(int height)
{
    _height = height;
}

int MyTagItem::getWidth()
{
    return _width;
}

int MyTagItem::getHeight()
{
    return _height;
}

