#ifndef UT_QMLACTIONBUTTON_H
#define UT_QMLACTIONBUTTON_H

#include <QObject>

class Ut_QmlListViewItemWithActions : public QObject {
    Q_OBJECT
private slots:
    void checkWarning();
};

#endif
