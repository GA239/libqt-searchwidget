#ifndef SEARCH_H
#define SEARCH_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QStringListModel>
#include <QItemSelectionModel>

#include "customraphicsview.h"
#include "customcompleter.h"
#include "mysecondtag.h"
#include "tagcompleteritemdelegate.h"

#define FONT_SIZE 30
#define INDENT 7
#define LINE_EDIT_HEIGHT 90

class Search : public QWidget
{
    Q_OBJECT
public:
    explicit Search(QWidget *parent = 0);
    virtual ~Search();
    void resizeEvent ( QResizeEvent * event );

    void initLineEdit();
    void addTag(const QString &data);

    void setModel(QAbstractItemModel *model);
    QItemSelectionModel* selectionModel() const;


    QGraphicsScene*             _scene;
    CustomGraphicsView*         _view;
    QPoint                      _currentTagPoint;
    QLineEdit*                  _lineEdit;
    CustomCompleter*            _completer;
    QAbstractItemModel*         _model;
    QItemSelectionModel*        _selModel;
    TagCompleterItemDelegate*   _tagCompleterItemDelegate;

public slots:
    void addTag();
    void removeNode(mySecondTag* node);
    void insertSelection(QModelIndex curIndex);
};

#endif // SEARCH_H
