#include "closebutton.h"

CloseButton::CloseButton(QWidget *parent) : QWidget(parent)
{
    this->buttonPadding = 10;
    this->calcSize();
    this->setAttribute(Qt::WA_StaticContents);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

CloseButton::~CloseButton()
{

}

/**
 * @brief CloseButton::minimumWidth
 * @return
 */
int CloseButton::minimumWidth() const
{
    return this->widgetWidth;
}
/**
 * @brief CloseButton::minimumHeight
 * @return
 */
int CloseButton::minimumHeight() const
{
    return this->widgetHeight;
}
/**
 * @brief CloseButton::sizeHint
 * @return
 */
QSize CloseButton::sizeHint() const
{
    QSize size(this->minimumWidth(), this->minimumHeight());
    return size;
}

/**
 * @brief CloseButton::paintEvent
 * @param event
 */
void CloseButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setPen(QPen(QColor(222,222,221), 0));
    painter.setBrush(QBrush(QColor(222,222,221)));
    QRect widgetRect(this->rect().top(), this->rect().left(), this->rect().width() - 1, this->rect().height() - 1);
    painter.drawEllipse(widgetRect);

    painter.setPen(QPen(QColor(114, 114, 114), 6));
    painter.drawLine(this->closerRect.topLeft(), this->closerRect.bottomRight());
    painter.drawLine(this->closerRect.bottomLeft(), this->closerRect.topRight());
}

/**
 * @brief CloseButton::mousePressEvent
 * @param event
 */
void CloseButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit pressed();
}

void CloseButton::calcSize()
{
    int closerSize = this->fontMetrics().height();
    this->widgetWidth  = closerSize + 2 * this->buttonPadding;
    this->widgetHeight = closerSize + 2 * this->buttonPadding;
    this->closerRect = QRect(this->buttonPadding,this->buttonPadding, closerSize, closerSize);
}

