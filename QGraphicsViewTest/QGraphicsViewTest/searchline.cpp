#include "searchline.h"

/**
 * @brief Default Constructor. Sets tefault values, and make
 * the default setting of the search line.
 */
SearchLine::SearchLine()
{
    this->buttonPadding = 10;
    this->calcSize();
}

/**
 * @brief Desstructor
 */
SearchLine::~SearchLine()
{

}

/**
 * @brief  Returns the minimum width of the search line.
 * Reimplemented method.
 *
 * @return
 */
int SearchLine::minimumWidth() const
{
    return this->widgetWidth;
}

/**
 * @brief  Returns the minimum height of the search line.
 * Reimplemented method.
 *
 * @return
 */
int SearchLine::minimumHeight() const
{
    return this->widgetHeight;
}

/**
 * @brief Returns the recommended size of the search line.
 * Reimplemented method.
 *
 * @return
 */
QSize SearchLine::sizeHint() const
{
    QSize size(this->minimumWidth(), this->minimumHeight());
    return size;
}

/**
 * @brief Calculates the size of the base elements of the serach line.
 */
void SearchLine::calcSize()
{
    int fontHeight = this->fontMetrics().height();
    this->widgetWidth = 2 * fontHeight + 3 * this->buttonPadding;
    this->widgetHeight = fontHeight + 2 * this->buttonPadding;
    return;
}

/**
 * @brief Function is called when a search line repaint event occurs.
 * @param event
 */
void SearchLine::paintEvent(QPaintEvent *event)
{
    this->calcSize();
    return QLineEdit::paintEvent(event);
}
