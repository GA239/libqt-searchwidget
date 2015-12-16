#ifndef SEARCH_H
#define SEARCH_H

#include <QObject>
#include <QGraphicsView>
#include <QWidget>
#include <QLineEdit>
#include <QStringListModel>
#include <QPaintEngine>
#include <QItemSelectionModel>
#include "searchline.h"
#include "lineeditcompleter.h"
#include "flowlayout.h"
#include "tagcompleteritemdelegate.h"
#include "tagbutton.h"

#define FONT_SIZE 30
#define INDENT 7
#define LINE_EDIT_HEIGHT 90

class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWidget(QWidget *parent = 0);
    virtual ~SearchWidget();
    void resizeEvent ( QResizeEvent * event );

    void initLineEdit();
    void addTag(const QString &data);

    void setModel(QAbstractItemModel *model);
    QItemSelectionModel* selectionModel() const;
    void timerEvent(QTimerEvent *event);

public slots:
    void addTag();
    void removeTagSlot(TagButton *tag);
    void insertSelection(QModelIndex curIndex);

protected:
    void paintEvent(QPaintEvent *event);

private:
   void calcSize(void);

private:
    QPointF _currentTagPoint;
    QLineEdit *lineEdit;
    LineEditCompleter *lineEditCompleter;
    QAbstractItemModel *model;
    QItemSelectionModel *selModel;
    TagCompleterItemDelegate *_tagCompleterItemDelegate;
    int timerId;
    FlowLayout *flowLayout;
    QRect lineEditRect;
    QRect completerRect;
    int lineEditWidth;
    int lineEditHeight;
    int buttonPadding;
};

#endif // SEARCH_H
