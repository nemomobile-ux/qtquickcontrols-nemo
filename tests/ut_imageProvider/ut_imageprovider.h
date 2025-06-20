#ifndef UT_IMAGEPROVIDER_H
#define UT_IMAGEPROVIDER_H

#include <QObject>

class Ut_ImageProvider : public QObject {
    Q_OBJECT
private slots:
    void init();
    void cleanup();

    void getImage();
    void getWrongImage();
    void getImageBySize();

    void getPximap();
    void getWrongPximap();
    void getPximapBySize();
};

#endif // UT_IMAGEPROVIDER_H
