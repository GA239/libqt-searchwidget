#include "tagcustomcompleter.h"
#include <QLineEdit>


TagCustomCompleter::TagCustomCompleter(QWidget *parent) :
    QCompleter(parent)
{
    setCaseSensitivity(Qt::CaseInsensitive);
    setCompletionMode(QCompleter::PopupCompletion);
    setCompletionRole(Qt::DisplayRole);
    //setCompletionMode(QCompleter::InlineCompletion);
}

QString TagCustomCompleter::pathFromIndex( const QModelIndex& index ) const
{
    QString path = QCompleter::pathFromIndex( index );

    QString text = static_cast<QLineEdit*>( widget() )->text();
    if(text.trimmed().length()==0)return text;

    int pos = text.lastIndexOf( ',' );

    emit signal_complete(path);

    /*if ( pos >= 0 )
        path = text.left( pos ) + " " + path;*/

    return path;
}

QStringList TagCustomCompleter::splitPath( const QString& path ) const
{
    int pos = path.lastIndexOf( ',' ) + 1;

    while ( pos < path.length() && path.at( pos ) == QLatin1Char( ' ' ) )
        pos++;

    return QStringList( path.mid( pos ) );
}
