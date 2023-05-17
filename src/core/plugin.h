#ifndef QQUICKNEMOCONTROLSEXTENSIONPLUGIN_H
#define QQUICKNEMOCONTROLSEXTENSIONPLUGIN_H

#include <QQmlExtensionPlugin>

class QQuickNemoControlsExtensionPlugin : public QQmlExtensionPlugin {
public:
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid FILE "nemo.json")
public:
    void registerTypes(const char* uri);
    void initializeEngine(QQmlEngine* engine, const char* uri);
};

#endif // QQUICKNEMOCONTROLSEXTENSIONPLUGIN_H
