#include "customlineedit.h"

CustomLineEdit::CustomLineEdit(QWidget *parent)
    :QLineEdit(parent)
{
    _notAbleToModifie = false;
}
/**
 * @brief CustomLineEdit::changeModificationPossibility
 *
 * It changes the ability to edit the line
 *
 */
void CustomLineEdit::changeModificationPossibility()
{
    _notAbleToModifie = !_notAbleToModifie;
}

bool CustomLineEdit::notAbleToModifie()
{
    return this->_notAbleToModifie;
}

void CustomLineEdit::keyPressEvent(QKeyEvent *event)
{
    _notAbleToModifie = false;
    QLineEdit::keyPressEvent(event);
}
