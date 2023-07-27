#include "filteringmousearea.h"
#include <QQuickWindow>

FilteringMouseArea::FilteringMouseArea(QQuickItem* parent)
    : QQuickItem(parent)
    , m_pressed(false)
    , m_swipingX(false)
    , m_swipingY(false)
    , m_swipingThreshold(10)
{
    setFiltersChildMouseEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

void FilteringMouseArea::setPressed(const bool pressed)
{
    if (m_pressed != pressed) {
        m_pressed = pressed;
        emit pressedChanged();
    }
}

void FilteringMouseArea::setPosition(const QPointF& pos)
{
    if (m_lastPos != pos) {
        m_lastPos = pos;
        emit positionChanged(pos);
    }
}

void FilteringMouseArea::setPressPos(const QPointF& pos)
{
    if (m_pressPos != pos) {
        m_pressPos = pos;
        emit pressPosChanged();
    }
}

void FilteringMouseArea::setDeltaPos(const QPointF& pos)
{
    if (m_deltaPos != pos) {
        m_deltaPos = pos;
        emit deltaPosChanged();
    }
}

void FilteringMouseArea::setSwipingX(const bool swiping)
{
    if (m_swipingX != swiping) {
        m_swipingX = swiping;
        emit swipingXChanged();
    }
}

void FilteringMouseArea::setSwipingY(const bool swiping)
{
    if (m_swipingY != swiping) {
        m_swipingY = swiping;
        emit swipingYChanged();
    }
}

void FilteringMouseArea::setSwipingThreshold(const int threshold)
{
    if (m_swipingThreshold != threshold) {
        m_swipingThreshold = threshold;
        emit swipingThresholdChanged();
    }
}

bool FilteringMouseArea::childMouseEventFilter(QQuickItem* i, QEvent* e)
{
    if (!isVisible() || !isEnabled())
        return QQuickItem::childMouseEventFilter(i, e);
    switch (e->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease:
        return sendMouseEvent(i, static_cast<QMouseEvent*>(e));
    case QEvent::UngrabMouse:
        if (window() && window()->mouseGrabberItem() && window()->mouseGrabberItem() != this) {
            // The grab has been taken away from a child and given to some other item.
            mouseUngrabEvent();
        }
        break;
    default:
        break;
    }

    return QQuickItem::childMouseEventFilter(i, e);
}

void FilteringMouseArea::mouseMoveEvent(QMouseEvent* event)
{
    if (!isEnabled() || !isPressed()) {
        QQuickItem::mouseMoveEvent(event);
        return;
    }

    // TODO: we should only grab the mouse if there's a swipe ongoing.
    // The move event is very easy to trigger with touchscreens
    // so it's not a good measure of the fact that we want to swipe
    // grabMouse();

    setDeltaPos(QPointF(event->scenePosition().x() - pressPos().x(), event->scenePosition().y() - pressPos().y()));
    if (event->scenePosition().x() - pressPos().x() > swipingThreshold()) {
        setSwipingX(true);
    }

    if (event->scenePosition().y() - pressPos().y() > swipingThreshold()) {
        setSwipingY(true);
    }
    setPosition(event->position());
}

void FilteringMouseArea::mousePressEvent(QMouseEvent* event)
{
    if (!isEnabled() || !(event->button() & acceptedMouseButtons())) {
        QQuickItem::mousePressEvent(event);
    } else {
        setPressPos(event->scenePosition());
        emit pressed(event->position());
        setPressed(true);
        setPosition(event->position());
    }
}

void FilteringMouseArea::mouseReleaseEvent(QMouseEvent* event)
{
    if (!isEnabled() && !isPressed()) {
        QQuickItem::mouseReleaseEvent(event);
    } else {
        QQuickWindow* w = window();
        if (w && w->mouseGrabberItem() == this && m_pressed) {
            emit released(event->position());
            mouseUngrabEvent();
        }
    }
}

bool FilteringMouseArea::sendMouseEvent(QQuickItem* item, QMouseEvent* event)
{
    Q_UNUSED(item);

    QPointF localPos = mapFromScene(event->scenePosition());
    QQuickWindow* c = window();
    QQuickItem* grabber = c ? c->mouseGrabberItem() : 0;

    if ((contains(localPos)) && (!grabber || !grabber->keepMouseGrab())) {
        QMouseEvent mouseEvent(event->type(), localPos, event->scenePosition(), event->scenePosition(),
            event->button(), event->buttons(), event->modifiers());
        mouseEvent.setAccepted(false);

        switch (event->type()) {
        case QEvent::MouseMove:
            mouseMoveEvent(&mouseEvent);
            break;
        case QEvent::MouseButtonPress:
            mousePressEvent(&mouseEvent);
            break;
        case QEvent::MouseButtonRelease:
            mouseReleaseEvent(&mouseEvent);
            break;
        default:
            break;
        }
    }
    return false;
}

void FilteringMouseArea::mouseUngrabEvent()
{
    setPressed(false);
    setSwipingX(false);
    setSwipingY(false);
    QQuickWindow* w = window();
    if (w && w->mouseGrabberItem() == this)
        ungrabMouse();
}

void FilteringMouseArea::grabMouseEvents()
{
    qDebug() << "Glacier Header: Grabbing mouse!";
    grabMouse();
}

void FilteringMouseArea::ungrabMouseEvents()
{
    ungrabMouse();
}
