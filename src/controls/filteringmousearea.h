#ifndef QQUICKFILTERINGMOUSEAREA_H
#define QQUICKFILTERINGMOUSEAREA_H

#include <QMouseEvent>
#include <QQuickItem>

class FilteringMouseArea : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(bool pressed READ isPressed NOTIFY pressedChanged)
    Q_PROPERTY(QPointF pressPos READ pressPos NOTIFY pressPosChanged)
    Q_PROPERTY(QPointF deltaPos READ deltaPos NOTIFY deltaPosChanged)
    Q_PROPERTY(bool swipingX READ isSwipingX NOTIFY swipingXChanged)
    Q_PROPERTY(bool swipingY READ isSwipingY NOTIFY swipingYChanged)
    Q_PROPERTY(int swipingThreshold READ swipingThreshold WRITE setSwipingThreshold NOTIFY swipingThresholdChanged)

public:
    explicit FilteringMouseArea(QQuickItem* parent = 0);

    bool handlePress();
    bool handleMove();
    bool handleRelease();

    bool isPressed() const { return m_pressed; }
    void setPressed(const bool pressed);

    QPointF position() const { return m_lastPos; }
    void setPosition(const QPointF& pos);

    QPointF pressPos() const { return m_pressPos; }
    void setPressPos(const QPointF& pos);

    QPointF deltaPos() const { return m_deltaPos; }
    void setDeltaPos(const QPointF& pos);

    bool isSwipingX() const { return m_swipingX; }
    void setSwipingX(const bool swiping);

    bool isSwipingY() const { return m_swipingY; }
    void setSwipingY(const bool swiping);

    int swipingThreshold() const { return m_swipingThreshold; }
    void setSwipingThreshold(const int threshold);

signals:
    void pressedChanged();
    void pressed(const QPointF& pos);
    void released(const QPointF& pos);
    void positionChanged(const QPointF& pos);
    void pressPosChanged();
    void deltaPosChanged();
    void swipingXChanged();
    void swipingYChanged();
    void swipingThresholdChanged();

public slots:
    void grabMouseEvents();
    void ungrabMouseEvents();

protected:
    virtual bool childMouseEventFilter(QQuickItem*, QEvent*);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseUngrabEvent();
    bool sendMouseEvent(QQuickItem* item, QMouseEvent* event);

private:
    bool m_pressed;
    QPointF m_lastPos;
    QPointF m_pressPos;
    QPointF m_deltaPos;
    bool m_swipingX;
    bool m_swipingY;
    int m_swipingThreshold;
};

#endif // QQUICKFILTERINGMOUSEAREA_H
