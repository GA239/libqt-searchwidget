#ifndef QTAGLABELBUTTON_H
#define QTAGLABELBUTTON_H

#include <QLabel>

class QTagLabelButton : public QLabel
{
    Q_OBJECT
    QFont font2;
    //need to use defaylt font
    bool defaultFont;
    //params
    int buttonPadding;
    int padding;
    int fontHeight;

public:
    explicit QTagLabelButton(QWidget *parent = 0, bool defaultFont = true, int fontHeight = 22);
    void paintEvent(QPaintEvent*);
    void setMainFont(QFont mfont){font2 = mfont;}

    int getButtonPadding() const;
    void setButtonPadding(int value);

    int getPadding() const;
    void setPadding(int value);

    int getFontHeight() const;
    void setFontHeight(int value);

signals:
    void clicked(QTagLabelButton *btn);
    void hovered();
    void unhovered();

public slots:

protected:
    bool event(QEvent *e);
};

#endif // QTAGLABELBUTTON_H
