#include "qmltest.h"
#include <QTest>
#include <QtQml/QQmlEngine>

Q_DECLARE_METATYPE(QList<QQmlError>)

QmlTest::QmlTest(const QString& file, QWindow* parent)
    : QQuickView { parent }
{
    QTest::createTouchDevice();
    engine()->addImportPath(QString(BUILD_DIR));
    engine()->addPluginPath(QString(BUILD_DIR) + "/Nemo");

    qRegisterMetaType<QList<QQmlError>>();
    if (file.isEmpty()) {
        qFatal() << "file path is empty";
    }

    if (!QFile(file).exists()) {
        qFatal() << "test qml file " << file << " not exists";
    }

    m_signalSpy = new QSignalSpy(engine(), SIGNAL(warnings(QList<QQmlError>)));
    m_signalSpy->setParent(this);

    setSource(QUrl::fromLocalFile(file));

    if (status() != QQuickView::Ready) {
        qFatal() << "QQuickView not ready";
    }
    show();
}

int QmlTest::warnings() const
{
    return m_signalSpy->count();
}
