#include "windowsvideoplugin.h"
#include "windowsvideoitem.h"
#include <QQmlEngine>

void WindowsVideoPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(engine)
    Q_UNUSED(uri)
    
    // Register the WindowsVideoItem type
    qmlRegisterType<WindowsVideoItem>("OpenHD.WindowsVideo", 1, 0, "WindowsVideoItem");
}
