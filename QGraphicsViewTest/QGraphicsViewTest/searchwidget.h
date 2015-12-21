#ifndef SEARCH_H
#define SEARCH_H

#include <QObject>
#include <QGraphicsView>
#include <QWidget>
#include <QLineEdit>
#include <QStringListModel>
#include <QPaintEngine>
#include <QItemSelectionModel>
#include <QTimer>
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
    //! [2] Custom public methods
    void addTag(const QString &data);
    void addTag(const QModelIndex index);
    void removeTag(TagButton *tag);
    TagButton *getTagByIndex(const QModelIndex index);
    void clear(void);
    //! [2]
    void setModel(QAbstractItemModel *model);
    void setSelectionModel(QItemSelectionModel *selModel);
    QItemSelectionModel* selectionModel() const;
    QModelIndexList tags(void);
    QStringList unfindedTags();

public slots:
    void removeTagSlot(TagButton *tag);
    void insertSelection(QModelIndex index);
    void onCompleterFinished(QModelIndex proxyIndex);
    void onReturnPressed(void);
    void onTagSelected(const QItemSelection &selected, const QItemSelection &deselected);
    void onSearchTextChanged(QString text);

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);

private:
   void calcSize(void);
   void clearLater(void);

private:
    QLineEdit *lineEdit;
    LineEditCompleter *lineEditCompleter;
    QAbstractItemModel *model;
    QItemSelectionModel *selModel;
    TagCompleterItemDelegate *tagCompleterItemDelegate;
    FlowLayout *flowLayout;
    QRect lineEditRect;
    QRect completerRect;
    int lineEditWidth;
    int lineEditHeight;
    int buttonPadding;
    int timerId;
};

#endif // SEARCH_H
