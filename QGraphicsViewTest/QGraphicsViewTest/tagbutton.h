#ifndef TAGBUTTON_H
#define TAGBUTTON_H

#include <QWidget>
#include <QLabel>
#include <QPainter>

class TagButton : public QWidget
{
    Q_OBJECT
public:
    explicit TagButton(QWidget *parent = 0);
    ~TagButton();
    int minimumWidth() const;
    int minimumHeight() const;
    QSize sizeHint() const;

    // custom method
    void setText(QString widgetText);
    QString text(void);
    void setInternalId(qintptr id);
    qintptr internalId(void);

signals:
    void deltag(TagButton *tag);

public slots:

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void calcSize(void);

private:
    QString widgetText;
    qintptr id;
    int widgetWidth;
    int widgetHeight;
    int fontHeight;
    QRect textRect;
    QRect closerRect;
    int buttonPadding;
};

#endif // TAGBUTTON_H
