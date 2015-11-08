#ifndef SEARCH_H
#define SEARCH_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QStringListModel>

#include "customraphicsview.h"
#include "customcompleter.h"
#include "mysecondtag.h"

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


    QGraphicsScene*     _scene;
    CustomGraphicsView*  _view;
    QPoint              _currentTagPoint;
    QLineEdit*          _lineEdit;
    CustomCompleter*    _completer;

public slots:
    void addTag();
    void removeNode(mySecondTag* node);

};

#endif // SEARCH_H
