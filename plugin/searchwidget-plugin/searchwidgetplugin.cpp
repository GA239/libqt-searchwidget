#include "searchwidgetplugin.h"

#include <QtPlugin>

searchwidgetPlugin::searchwidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void searchwidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool searchwidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *searchwidgetPlugin::createWidget(QWidget* parent)
{    
    return new SearchWidget();
}

QString searchwidgetPlugin::name() const
{
    return QLatin1String("searchwidget");
}

QString searchwidgetPlugin::group() const
{
    return QLatin1String("");
}

QIcon searchwidgetPlugin::icon() const
{
    return QIcon();
}

QString searchwidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString searchwidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool searchwidgetPlugin::isContainer() const
{
    return false;
}

QString searchwidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"searchwidget\" name=\"searchwidget\">\n</widget>\n");
}

QString searchwidgetPlugin::includeFile() const
{
    return QLatin1String("..\..\src\searchwidget.h ");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(searchwidgetplugin, searchwidgetPlugin)
#endif // QT_VERSION < 0x050000
