#include "searchline.h"

SearchLine::SearchLine()
{
    this->buttonPadding = 10;
    this->calcSize();
}

SearchLine::~SearchLine()
{

}

/**
 * @brief TagButton::minimumWidth
 * @return
 */
int SearchLine::minimumWidth() const
{
    return this->widgetWidth;
}

/**
 * @brief TagButton::minimumHeight
 * @return
 */
int SearchLine::minimumHeight() const
{
    return this->widgetHeight;
}

/**
 * @brief TagButton::sizeHint
 * @return
 */
QSize SearchLine::sizeHint() const
{
    QSize size(this->minimumWidth(), this->minimumHeight());
    return size;
}

/**
 * @brief SearchLine::calcSize
 */
void SearchLine::calcSize()
{
    int fontHeight = this->fontMetrics().height();
    this->widgetWidth = 2 * fontHeight + 3 * this->buttonPadding;
    this->widgetHeight = fontHeight + 2 * this->buttonPadding;
    return;
}

/**
 * @brief SearchLine::paintEvent
 * @param event
 */
void SearchLine::paintEvent(QPaintEvent *event)
{
    this->calcSize();
    return QLineEdit::paintEvent(event);
}
