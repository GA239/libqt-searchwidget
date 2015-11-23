#include "tag.h"
#include <QApplication>
#include "customraphicsview.h"
#include <QDebug>

Tag::Tag(QObject *parent) : QObject(parent)
{

}

Tag::Tag(QPointF position, const QString &data, CustomGraphicsView *graphView) : view(graphView) //todo: все параметры в конструктор
{
    this->setFlag(ItemIsMovable);
    /// @fix setFlag(ItemIsSelectable);
    this->setFlag(ItemSendsGeometryChanges);
    this->setCacheMode(DeviceCoordinateCache);
    this->setPos(position);

    _data = data;
    _font = QFont("times",36);
    _thickness = 3;

    QFontMetrics metrics(_font);
    _width = metrics.width(_data) + 10;
    _height = metrics.height();
}

QRectF Tag::boundingRect() const
{
    return QRectF(this->pos(),QSizeF(_width,_height));
}

void Tag::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
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


void Tag::mousePressEvent(QGraphicsSceneMouseEvent *pe)
{
    //QApplication::setOverrideCursor(Qt::PointingHandCursor);
    //QGraphicsItem::mousePressEvent(pe);
    emit delnode(this);
}

void Tag::mouseReleaseEvent(QGraphicsSceneMouseEvent *pe)
{
    //QApplication::restoreOverrideCursor();
    //QGraphicsItem::mouseReleaseEvent(pe);
    //emit delnode(this);
}

/**
 * @brief Calculates forces on the current tag and calculates the coordinates of this element in next iteration.
 */
void Tag::calculateForces()
{
    qreal xvel = 0;     // next iteration x ofset
    qreal yvel = 0;     // next iteration y ofset
    QRectF sceneRect = this->scene()->sceneRect();
//! [2]Sum up all forces pushing this item away
    foreach (QGraphicsItem *item, scene()->items())
    {
        Tag *tag = qgraphicsitem_cast<Tag *>(item);
        if (!tag)
            continue;

        QPointF vec = mapToItem(tag, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();
        double l = 2.0 * (dx * dx + dy * dy);
        if (l > 0)
        {
            xvel += (dx * 150.0) / l;
            yvel += (dy * 150.0) / l;
        }
    }
//! [2]
//! [3] Now subtract all forces pulling items together
//! [3]
//! [4] Calc force pulling items to top left corner
    QPointF vec = QPointF(sceneRect.left(), sceneRect.top());
    xvel -= (this->pos().x() - vec.x())/30.;
    yvel -= (this->pos().y() - vec.y())/10.;
//! [4]
//! [5] Check new position for remove jitter
    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1) {
        xvel = yvel = 0;
    }
//! [5]
//! [6] Calculate new node position
    newNodePosition = pos() + QPointF(xvel, yvel);
    newNodePosition.setX(qMin(qMax(newNodePosition.x(), sceneRect.left() + 10), sceneRect.right() - 10));
    newNodePosition.setY(qMin(qMax(newNodePosition.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
//! [6]
    return;
}

/**
 * @brief set new node position, if position changed
 * @return
 */
bool Tag::advance()
{
    if (newNodePosition == pos()) {
        return false;
    }
    setPos(newNodePosition);
    //qDebug() << "mySecondTag::advance() -> new position x=" << newNodePosition.x() << ", y=" << newNodePosition.y();
    return true;
}

/**
 * @brief Receives item event change messages for this node
 * @param change
 * @param value
 * @return
 */
QVariant Tag::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
        case ItemPositionHasChanged: {
            this->view->itemMoved();
        } break;
        default:
            break;
    };
    return QGraphicsItem::itemChange(change, value);
}

void Tag::setFont(QFont font)
{
    _font = font;
    _width = (_font.pointSize() * _data.size());
}

void Tag::setThickness(int thickness)
{
    _thickness = thickness;
}

void Tag::setHeight(int height)
{
    _height = height;
}

int Tag::getWidth()
{
    return _width;
}

int Tag::getHeight()
{
    return _height;
}
