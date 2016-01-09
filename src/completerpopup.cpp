#include "completerpopup.h"

CompleterPopup::CompleterPopup(QWidget *parent) :
    QListView(parent)

{
    this->widgetWidth = 100;
    this->widgetHeight = 200;
}

/**
 * @brief Function is called when Completer popup is resized.
 * @param event
 */
void CompleterPopup::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    this->setGeometry(this->position.x(),this->position.y(),this->minimumWidth(),this->minimumHeight());
    return;
}

/**
 * @brief  Returns the minimum width of the Completer popup.
 * Reimplemented method.
 *
 * @return
 */
int CompleterPopup::minimumWidth() const
{
    return this->widgetWidth;
}

/**
 * @brief  Returns the minimum height of the Completer popup.
 * Reimplemented method.
 *
 * @return
 */
int CompleterPopup::minimumHeight() const
{
    return this->widgetHeight;
}

/**
 * @brief  Sets the width of the Completer popup.
 *
 * @param width of the Completer popup.
 */
void CompleterPopup::setWidth(int width)
{
    this->widgetWidth = width;
    return;
}
/**
 * @brief  Sets the left top position of the Completer popup.
 *
 * @param pos left top position.
 */
void CompleterPopup::setPoint(QPoint pos)
{
    this->position = pos;
    return;
}

/**
 * @brief Returns the recommended size of the Completer popup.
 * Reimplemented method.
 *
 * @return
 */
QSize CompleterPopup::sizeHint() const
{
    QSize size(this->minimumWidth(), this->minimumHeight());
    return size;
}

