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
<<<<<<< HEAD
#include "tagbutton.h"
=======
#include "custompopup.h"
#include "customlineedit.h"
>>>>>>> dea7b3eb2d9a3e3caada4c83e5cb1bd327c62c4d

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
<<<<<<< HEAD
    QModelIndexList tags(void);
    QStringList unfindedTags();

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
=======
    void timerEvent(QTimerEvent *event);
    bool eventFilter(QObject * watched, QEvent * event);

public slots:
    void addTag();
    void removeNode(Tag* node);
    void insertSelection(QModelIndex curIndex);
    void cleanLineEdit();
    void addTagTromPopup(const QModelIndex &index);
    void textWatcher();

private:
    QGraphicsScene*             _scene;
    CustomGraphicsView*         _view;
    QPointF                      _currentTagPoint;
    CustomLineEdit*                  _lineEdit;
    CustomCompleter*            _completer;
    QAbstractItemModel*         _model;
    QItemSelectionModel*        _selModel;
    TagCompleterItemDelegate*   _tagCompleterItemDelegate;
    CustomPopup*                _popup;
    int timerId;
>>>>>>> dea7b3eb2d9a3e3caada4c83e5cb1bd327c62c4d
};

#endif // SEARCH_H
