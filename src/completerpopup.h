#ifndef COMPLETERPOPUP_H
#define COMPLETERPOPUP_H

#include <QObject>
#include <QAbstractItemView>
#include <QListView>

class CompleterPopup : public QListView
{

    Q_OBJECT

public:
    CompleterPopup(QWidget * parent = 0);
    int minimumWidth() const;
    int minimumHeight() const;
    void setWidth(int width);
    void setPoint(QPoint pos);
    QSize sizeHint() const;


private:
    void resizeEvent(QResizeEvent * event);

    QPoint position;
    int widgetWidth;
    int widgetHeight;
    int buttonPadding;

};



#endif // COMPLETERPOPUP_H
