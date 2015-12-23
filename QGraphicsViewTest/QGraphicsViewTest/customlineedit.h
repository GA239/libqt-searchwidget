#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QObject>
#include <qlineedit.h>

class CustomLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    CustomLineEdit(QWidget * parent = 0);

    void changeModificationPossibility();
    bool notAbleToModifie();
    void keyPressEvent(QKeyEvent *event);


private:
    bool _notAbleToModifie;
};

#endif // CUSTOMLINEEDIT_H
