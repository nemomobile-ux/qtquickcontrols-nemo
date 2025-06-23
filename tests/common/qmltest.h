#ifndef QMLTEST_H
#define QMLTEST_H

#include <QObject>
#include <QtQuick/QQuickView>
#include <QtTest/QSignalSpy>

class QmlTest : public QQuickView {
    Q_OBJECT
public:
    explicit QmlTest(const QString& file, QWindow* parent = nullptr);
    int warnings() const;

private:
    QSignalSpy* m_signalSpy;
};

#endif // QMLTEST_H
