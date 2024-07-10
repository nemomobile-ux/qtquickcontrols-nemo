#include "plugin.h"
#include "nemoimageprovider.h"
#include "theme.h"
#include <QtQml>

void QQuickNemoControlsExtensionPlugin::registerTypes(const char* uri)
{
    Q_ASSERT(uri == QLatin1String("Nemo"));
    qmlRegisterModule(uri, 2, 0);
}

void QQuickNemoControlsExtensionPlugin::initializeEngine(QQmlEngine* engine, const char* uri)
{
    Theme* theme = new Theme();

    QQmlExtensionPlugin::initializeEngine(engine, uri);
    QQmlContext* context = engine->rootContext();
    context->setContextProperty("size", theme->size);
    context->setContextProperty("Theme", theme);

    engine->addImageProvider(QLatin1String("theme"), new NemoImageProvider);
}
