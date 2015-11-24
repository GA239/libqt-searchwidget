#ifndef CUSTOMPOPUP_H
#define CUSTOMPOPUP_H

#include <QObject>
#include <QAbstractItemView>
#include <QListView>

class CustomPopup : public QListView
{

    Q_OBJECT

public:
    CustomPopup(QWidget * parent = 0);
    //void hideEvent(QHideEvent* event);

signals:
       //bool popupHidden();


};

#endif // CUSTOMPOPUP_H
