#ifndef MYSECONDTAG_H
#define MYSECONDTAG_H

#include <QObject>
#include <QGraphicsItem>
#include <QWidget>
#include <QPainter>

class mySecondTag : public QObject,  public QGraphicsItem
{
    Q_OBJECT
public:
    explicit mySecondTag(QObject *parent = 0);

    mySecondTag(QPoint position, const QString &data, QObject *parent = 0);

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
     void   delnode(mySecondTag* node);

private:
    QPoint  _position;
    QString _data;
    QFont   _font;
    int     _height;
    int     _thickness;
    int     _width;
public slots:
};

#endif // MYSECONDTAG_H
