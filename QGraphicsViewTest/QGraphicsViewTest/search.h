#ifndef SEARCH_H
#define SEARCH_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QStringListModel>
#include <QCompleter>

#include "qgraphicsviewtest.h"
#include "mytagitem.h"
#include "mysecondtag.h"


#include "mycompleter.h"


class Search : public QWidget
{
    Q_OBJECT
public:
    explicit Search(QWidget *parent = 0);
    virtual ~Search();
    void resizeEvent ( QResizeEvent * event );

    void initScene();
    void addTag(const QString &data);


    QGraphicsScene*     _scene;
    QGraphicsViewTest*  _view;
    QPoint              _currentTagPoint;
    QLineEdit*          _lineEdit;
//    QCompleter*         _completer;
    MyCompleter*         _completer;

    int _indent;

    //TRASH
signals:

public slots:
    void addTag();
    void removeNode(MyTagItem *node);
    void removeSecondNode(mySecondTag* node);

};

#endif // SEARCH_H
