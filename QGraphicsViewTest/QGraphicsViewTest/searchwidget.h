#ifndef SEARCH_H
#define SEARCH_H

#include <QObject>
#include <QGraphicsView>
#include <QWidget>
#include <QLineEdit>
#include <QStringListModel>
#include <QItemSelectionModel>
#include "customraphicsview.h"
#include "customcompleter.h"
#include "tag.h"
#include "tagcompleteritemdelegate.h"
#include "custompopup.h"
#include "customlineedit.h"

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
};

#endif // SEARCH_H
