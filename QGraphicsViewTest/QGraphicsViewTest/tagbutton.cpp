#include "tagbutton.h"
#include <QDebug>
#include <QMouseEvent>

/**
 * @brief TagButton::TagButton
 * @param parent
 */
TagButton::TagButton(QWidget *parent) : QWidget(parent)
{
    this->buttonPadding = 10;
    this->calcSize();
    this->setAttribute(Qt::WA_StaticContents);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

/**
 * @brief TagButton::~TagButton
 */
TagButton::~TagButton()
{

}

/**
 * @brief TagButton::minimumWidth
 * @return
 */
int TagButton::minimumWidth() const
{
    return this->widgetWidth;
}

/**
 * @brief TagButton::minimumHeight
 * @return
 */
int TagButton::minimumHeight() const
{
    return this->widgetHeight;
}

/**
 * @brief TagButton::sizeHint
 * @return
 */
QSize TagButton::sizeHint() const
{
    QSize size(this->minimumWidth(), this->minimumHeight());
    return size;
}

/**
 * @brief Sets tag text, displyed on button
 * @param text
 */
void TagButton::setText(QString text)
{
    this->widgetText = text;
    this->calcSize();
    this->repaint();
    return;
}

/**
 * @brief TagButton::text
 * @return
 */
QString TagButton::text()
{
    return this->widgetText;
}

/**
 * @brief Sets unical element id
 * @param id
 */
void TagButton::setId(qintptr id)
{
    this->id = id;
}

/**
 * @brief TagButton::paintEvent
 * @param event
 */
void TagButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //! [1] draw background
    painter.setPen(QPen(Qt::gray, 0));
    painter.setBrush(QBrush(QColor(193,193,193)));
    QRect widgetRect(this->rect().top(), this->rect().left(), this->rect().width() - 1, this->rect().height() - 1);
    painter.drawRect(widgetRect);
    //! [1]
    //! [2] draw text
    painter.setPen(QPen(Qt::black, 0));
    painter.setBrush(QBrush(Qt::transparent));
    //painter.drawRect(this->textRect);
    painter.setBrush(QBrush(Qt::black));
    painter.drawText(this->textRect, Qt::AlignLeft, this->widgetText);
    //! [2]
    //! [3] draw closer
    painter.setPen(QPen(Qt::black, 0));
    painter.setBrush(QBrush(Qt::transparent));
    //painter.drawRect(this->closerRect);
    painter.setPen(QPen(QColor(114, 114, 114), 4));
    painter.drawLine(this->closerRect.topLeft(), this->closerRect.bottomRight());
    painter.drawLine(this->closerRect.bottomLeft(), this->closerRect.topRight());
    //! [3]
}

/**
 * @brief TagButton::mousePressEvent
 * @param event
 */
void TagButton::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePos = event->pos();
    if(mousePos.x() >= this->closerRect.left()
            && mousePos.x() <= this->closerRect.right()
            && mousePos.y() >= this->closerRect.top()
            && mousePos.y() <= this->closerRect.bottom()) {
        emit this->deltag(this);
        qDebug() << "close()";
    }
}

/**
 * @brief TagButton::calcSize
 */
void TagButton::calcSize()
{
    QFontMetrics fontMetrics(this->font());
    QRect rect = fontMetrics.boundingRect(this->widgetText);
    this->fontHeight = rect.height();
    this->widgetWidth = rect.width() + 3 * this->buttonPadding + rect.height();
    this->widgetHeight = rect.height() + 2 * this->buttonPadding;
    this->textRect = QRect(this->buttonPadding, this->buttonPadding, rect.width(), rect.height());
    this->closerRect = QRect(this->widgetWidth - this->buttonPadding - fontHeight,
                             this->buttonPadding, this->fontHeight, this->fontHeight);
}

