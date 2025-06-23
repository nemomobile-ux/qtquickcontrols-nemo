#include "qmltest.h"
#include <QTest>
#include <QtQml/QQmlEngine>

Q_DECLARE_METATYPE(QList<QQmlError>)

QmlTest::QmlTest(const QString& file, QWindow* parent)
    : QQuickView { parent }
{
    QTest::createTouchDevice();

    qRegisterMetaType<QList<QQmlError>>();

    Q_ASSERT(!file.isEmpty());
    if (!QFile(file).exists()) {
        qFatal() << "test qml file " << file << " not exists";
    }

    m_signalSpy = new QSignalSpy(engine(), SIGNAL(warnings(QList<QQmlError>)));
    m_signalSpy->setParent(this);

    setSource(QUrl::fromLocalFile(file));

    Q_ASSERT(status() == QQuickView::Ready);
    Q_ASSERT(rootObject());

    show();
    Q_ASSERT(QTest::qWaitForWindowExposed(this));
}

int QmlTest::warnings() const
{
    return m_signalSpy->count();
}
