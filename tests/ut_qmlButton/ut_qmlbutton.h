#ifndef UT_QMLACTIONBUTTON_H
#define UT_QMLACTIONBUTTON_H

#include <QObject>

class Ut_QmlButton : public QObject {
    Q_OBJECT
private slots:
    void init();
    void cleanup();

    void checkWarning();
};

#endif // UT_QMLACTIONBUTTON_H
