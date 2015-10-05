#include "simpledelegate.h"

SimpleDelegate::SimpleDelegate(QObject* pobj)
    :QItemDelegate(pobj)
{
    buttonPressed = false;
    color = Qt::gray;
}

void SimpleDelegate::paint(QPainter *pPainter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    QRect rect = option.rect;

    //rect_2.setWidth(rect.width()/2);
    QLinearGradient gradient(0,0, rect.width(), rect.height());
    gradient.setColorAt(0, Qt::white);
    QLinearGradient gradient_2 = gradient;

    gradient.setColorAt(1, color);

    pPainter->setBrush(gradient);
    pPainter->drawRect(rect);

    if(option.state & QStyle::State_MouseOver)
    {
        gradient_2.setColorAt(1, Qt::green);
        pPainter->setBrush(gradient_2);
        pPainter->drawRect(rect);
    }

    pPainter->setPen(QPen(Qt::black,2,Qt::SolidLine)); // Настройки рисования

    int x1,x2,y1,y2;
    rect.getCoords(&x1,&y1,&x2,&y2);
    pPainter->drawLine(x2-15,y1,x2,y2); // Рисование линии
    pPainter->drawLine(x2-15,y2,x2,y1); // Рисование линии
    pPainter->drawLine(x2-15,y1,x2-15,y2); // Рисование линии

    QItemDelegate::paint(pPainter,option, index);
}

bool SimpleDelegate::editorEvent( QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index )
{
    Q_ASSERT(event);
    Q_ASSERT(model);
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *me = static_cast<QMouseEvent*>(event);
        QRect rect = option.rect;
        QPoint point = me->pos();
        if(point.x() < rect.width() - 15)
        {
            color = Qt::gray;
        }
        else
        {
            color = Qt::red;
            //model =  static_cast<QStringListModel>;
            //model->
            //model->removeRows(index.row(),1,index);
            //model->rowsRemoved(index,1,1,QPrivateSignal);
            //setbuttonPressed(true);
            //тут нужно удалять элиемент
            //setbuttonPressed(false);

        }
    }
    return false;
}

void SimpleDelegate::setbuttonPressed(bool value)
{
    buttonPressed = value;
}

