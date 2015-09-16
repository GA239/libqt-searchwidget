#include "qtaglabelbutton.h"
#include <QEvent>
#include <QPainter>
#include <QFontDatabase>

QTagLabelButton::QTagLabelButton(QWidget *parent, bool defaultFont, int fontHeight) :
    QLabel(parent)
{
     setAttribute(Qt::WA_Hover);
     this->defaultFont = defaultFont;
     if(!defaultFont)
     {
        int id = QFontDatabase::addApplicationFont(":/fonts/fonts/segoeui.ttf");
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        font2 = QFont(family, fontHeight, QFont::Normal,false);
     }
     else
     {
         font2 = QFont();
         font2.setPointSize(fontHeight);
     }
}

bool QTagLabelButton::event(QEvent *e)
{

    if(e->type() == QEvent::HoverMove)
    {
        emit hovered();
        return true;
    }
    else if(e->type() == QEvent::HoverLeave)
    {
        emit unhovered();
        return true;
    }
    else if(e->type() == QEvent::MouseButtonPress)
    {
        emit clicked(this);
        return true;
    }

    return QLabel::event(e);
}

void QTagLabelButton::paintEvent(QPaintEvent*)
{
    QFontMetrics fm(font2);
    setGeometry(pos().x(),5,fm.width(text())+padding+2*buttonPadding+fontHeight,((QWidget*)parent())->height()-10);
/*    int startx = width()-14;
    int starty = ((QWidget*)parent())->height()/2-14;*/
    int startx = width()-fontHeight-buttonPadding;
    int starty = ((QWidget*)parent())->height()/2-fontHeight;
    //QImage *image = new QImage();
    //image->load(":/images/images/close1.png");
    QPainter painter( this );
    painter.setPen( QPen( Qt::black ) );
    painter.setFont(font2);
    //draw text
    painter.drawText(buttonPadding,((QWidget*)parent())->height()/2+2,text());
    //draw rect
    painter.setBrush(QBrush(QColor(218,226,232)));
    painter.setPen(QPen(QColor(218,226,232)));
    painter.drawRect(startx,starty,fontHeight,fontHeight);
    //draw cross
    painter.setPen(QPen(QColor(160,173,192)));
    painter.drawLine(startx + 4, starty + 4, startx + fontHeight-3, starty + fontHeight-3);
    painter.drawLine(startx + 5, starty + 3, startx + fontHeight-2, starty + fontHeight-4);

    painter.drawLine(startx + 4, starty + fontHeight-3, startx + fontHeight-3, starty + 4);
    painter.drawLine(startx + 5, starty + fontHeight-2, startx + fontHeight-2, starty + 5);

    painter.drawLine(startx + 5, starty + 4, startx + fontHeight-3, starty + fontHeight - 4);
    painter.drawLine(startx + 5, starty + fontHeight-3, startx + fontHeight-3, starty + 5);

    /*painter.drawLine(startx + 4, starty + 4, startx + 11, starty + 11);
    painter.drawLine(startx + 5, starty + 3, startx + 12, starty + 10);

    painter.drawLine(startx + 4, starty + 11, startx + 11, starty + 4);
    painter.drawLine(startx + 5, starty + 12, startx + 12, starty + 5);

    painter.drawLine(startx + 5, starty + 4, startx + 11, starty + 10);
    painter.drawLine(startx + 5, starty + 11, startx + 12, starty + 5);*/
    //painter.drawPixmap(width()-14,((QWidget*)parent())->height()/2-14,14,14,QPixmap::fromImage(*image));
}

/**
 * gets font height
 */
int QTagLabelButton::getFontHeight() const
{
    return fontHeight;
}

/**
 * sets font height
 */
void QTagLabelButton::setFontHeight(int value)
{
    fontHeight = value;
}

/**
 * gets padding
 */
int QTagLabelButton::getPadding() const
{
    return padding;
}

/**
 * sets padding
 */
void QTagLabelButton::setPadding(int value)
{
    padding = value;
}

/**
 * gets button padding
 */
int QTagLabelButton::getButtonPadding() const
{
    return buttonPadding;
}

/**
 * sets button padding
 */
void QTagLabelButton::setButtonPadding(int value)
{
    buttonPadding = value;
}
