#ifndef WINDOWSVIDEOPLUGIN_H
#define WINDOWSVIDEOPLUGIN_H

#include <QQmlEngineExtensionPlugin>

class WindowsVideoPlugin : public QQmlEngineExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid)

public:
    void initializeEngine(QQmlEngine *engine, const char *uri) override;
};

#endif // WINDOWSVIDEOPLUGIN_H
