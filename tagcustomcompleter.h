#ifndef TAGCUSTOMCOMPLETER_H
#define TAGCUSTOMCOMPLETER_H

#include <QCompleter>

class TagCustomCompleter : public QCompleter
{
    Q_OBJECT
public:
    explicit TagCustomCompleter(QWidget *parent = 0);
    QString pathFromIndex( const QModelIndex& index ) const;
    QStringList splitPath( const QString& path ) const;

signals:
    void signal_complete(QString&) const;

public slots:
};

#endif // TAGCUSTOMCOMPLETER_H
