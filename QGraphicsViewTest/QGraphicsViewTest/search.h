#ifndef SEARCH_H
#define SEARCH_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QStringListModel>
#include <QCompleter>

#include "qgraphicsviewtest.h"
#include "mytagitem.h"

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
    QCompleter*         _completer;

    int _indent;
    int _scaleFactor;

    //TRASH
signals:

public slots:
    void addTag();

};

#endif // SEARCH_H
