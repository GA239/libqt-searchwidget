#include "mysecondtag.h"
#include <QApplication>

mySecondTag::mySecondTag(QObject *parent) : QObject(parent)
{

}

mySecondTag::mySecondTag(QPoint position, const QString &data, QObject *parent) //todo: все параметры в конструктор
{
    _position = position;
    _data = data;
    _font = QFont("times",36);
    _thickness = 3;

    QFontMetrics metrics(_font);
    _width = metrics.width(_data) + 10;
    _height = metrics.height();
}

QRectF mySecondTag::boundingRect() const
{
    return QRectF(_position,QSizeF(_width,_height));
}

void mySecondTag::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
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


void mySecondTag::mousePressEvent(QGraphicsSceneMouseEvent *pe)
{
    //QApplication::setOverrideCursor(Qt::PointingHandCursor);
    //QGraphicsItem::mousePressEvent(pe);
    emit delnode(this);
}

void mySecondTag::mouseReleaseEvent(QGraphicsSceneMouseEvent *pe)
{
    //QApplication::restoreOverrideCursor();
    //QGraphicsItem::mouseReleaseEvent(pe);
    //emit delnode(this);
}

void mySecondTag::setFont(QFont font)
{
    _font = font;
    _width = (_font.pointSize() * _data.size());
}

void mySecondTag::setThickness(int thickness)
{
    _thickness = thickness;
}

void mySecondTag::setHeight(int height)
{
    _height = height;
}

void mySecondTag::setPos(QPoint pos)
{
    _position = pos;
}

int mySecondTag::getWidth()
{
    return _width;
}

int mySecondTag::getHeight()
{
    return _height;
}
