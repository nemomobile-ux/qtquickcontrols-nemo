#ifndef RINGINDICATOR_H
#define RINGINDICATOR_H

#include <QObject>
#include <QtMath>
#include <QQuickPaintedItem>
#include <QSGGeometry>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>


class RingIndicator : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(float startAngle READ startAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(float stopAngle READ stopAngle WRITE setStopAngle NOTIFY stopAngleChanged)
    Q_PROPERTY(float lineHeight READ lineHeight WRITE setLineHeight NOTIFY lineHeightChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)

public:
    RingIndicator(QQuickItem *parent = nullptr);
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    float startAngle() {return m_startAngle;}
    float stopAngle() {return m_stopAngle;}
    float lineHeight() {return m_lineHeight;}
    QString color() {return m_color.name();}

    void setStartAngle(float startAngle);
    void setStopAngle(float stopAngle);
    void setLineHeight(float height);
    void setColor(QString color);

signals:
    void startAngleChanged();
    void stopAngleChanged();
    void lineHeightChanged();
    void colorChanged();

private:
    float m_startAngle;
    float m_stopAngle;
    float m_lineHeight;
    QColor m_color;

    float normalizeAngile(float ang);
};

#endif // RINGINDICATOR_H
