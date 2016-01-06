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
    int minimumHeight();
    int minimumWidth();
    QSize minimumSize();
    QSize sizeHint();
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
    void setEnableNewTagCreation(bool status);

public slots:
    void removeTagSlot(TagButton *tag);
    void onTagSelected(const QItemSelection &selected, const QItemSelection &deselected);
    void onCompleterFinished(QModelIndex proxyIndex);
    void onReturnPressed(void);
    void onSearchTextChanged(QString text);

protected:
    void paintEvent(QPaintEvent *event);

private:
   void calcSize(void);
   void insertSelection(QModelIndex index);

private:
    QLineEdit *lineEdit;
    LineEditCompleter *lineEditCompleter;
    QAbstractItemModel *model;
    QItemSelectionModel *selModel;
    TagCompleterItemDelegate *tagCompleterItemDelegate;
    FlowLayout *flowLayout;
    int buttonPadding;
    bool enableNewTagCreation;

};

#endif // SEARCH_H
