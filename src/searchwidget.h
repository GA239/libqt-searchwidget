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
#include "closebutton.h"


class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWidget(QWidget *parent = 0);
    virtual ~SearchWidget();
    void resizeEvent ( QResizeEvent * event );
    int minimumHeight();
    int minimumWidth();
    QSize minimumSize();
    QSize sizeHint();
    //! [2] Custom public methods
    void addTag(const QString &data);
    void addTag(const QModelIndex index);
    void addTag(TagButton *tag);
    void removeTag(TagButton *tag);
    TagButton *getTagByIndex(const QModelIndex index);

    //! [2]
    void setModel(QAbstractItemModel *model);
    void setSelectionModel(QItemSelectionModel *selModel);
    QItemSelectionModel* selectionModel() const;
    QModelIndexList tags(void);
    QStringList unfindedTags();
    void setEnableNewTagCreation(bool status);

public slots:
    void removeTagSlot(TagButton *tag);
    void onTagSelected(const QItemSelection &selected, const QItemSelection &deselected);
    void onCompleterFinished(QModelIndex proxyIndex);
    void onReturnPressed(void);
    void onSearchTextChanged(QString text);
    void clear(void);

protected:
    void paintEvent(QPaintEvent *event);

private:
   void calcSize(void);
   void insertSelection(QModelIndex index);
   int calcTagsSpace(bool lastTag);

private:
    SearchLine *lineEdit;
    CloseButton *closeButton;
    LineEditCompleter *lineEditCompleter;
    QAbstractItemModel *model;
    QItemSelectionModel *selModel;
    TagCompleterItemDelegate *tagCompleterItemDelegate;
    FlowLayout *flowLayout;
    int buttonPadding;
    bool enableNewTagCreation;

    int fixedSpace;
    int tagSpace;
};

#endif // SEARCH_H
