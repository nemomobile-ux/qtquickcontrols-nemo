/*
 * Copyright (C) 2013 Andrea Bernabei <and.bernabei@gmail.com>
 * Copyright (C) 2021-2025 Chupligin Sergey <neochapay@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "nemowindow.h"

#include <QMouseEvent>
#include <QScreen>
#include <QTouchEvent>

#include <QtGlobal>

namespace {

qreal clampedGestureThreshold(qreal threshold)
{
    if (threshold <= 0.0) {
        return 0.25;
    }
    return qMin(threshold, 1.0);
}

bool isValidBackGestureEdge(Qt::Edge edge)
{
    return edge == Qt::LeftEdge || edge == Qt::RightEdge;
}

}

NemoWindow::NemoWindow(QWindow* parent)
    : QQuickWindow(parent)
    , m_filter(new EditFilter(this))
    , m_screen(nullptr)
    , m_gestureInput(GestureInput::None)
    , m_gestureTriggered(false)
    , m_gestureStartPos()
    , m_allowExtendedEvents(!qEnvironmentVariableIsSet("NEMO_DISABLE_EXTENDED_EVENTS"))
    , m_backGestureThreshold(0.25)
    , m_backGestureEdge(Qt::LeftEdge)
{
    installEventFilter(m_filter);

    auto attachScreen = [this](QScreen* newScreen) {
        if (m_screen == newScreen) {
            return;
        }
        if (m_screen) {
            disconnect(m_screen, &QScreen::orientationChanged, this, &NemoWindow::orientationChanged);
        }
        m_screen = newScreen;
        if (m_screen) {
            connect(m_screen, &QScreen::orientationChanged, this, &NemoWindow::orientationChanged);
        }
    };

    attachScreen(screen());
    connect(this, &QWindow::screenChanged, this, attachScreen);
    connect(m_filter, &EditFilter::touchEvent, this, &NemoWindow::touchEventHandler);
    connect(m_filter, &EditFilter::backEvent, this, &NemoWindow::goBack);
}

Qt::ScreenOrientation NemoWindow::primaryOrientation() const
{
    if (!m_screen) {
        return Qt::PrimaryOrientation;
    }
    return m_screen->primaryOrientation();
}

void NemoWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
    case Qt::Key_Return:
    case Qt::Key_Backspace:
    case Qt::Key_Left:
        if (allowExtendedEvents()) {
            emit goBack();
        }
        break;
    default:
        break;
    }
    QQuickWindow::keyPressEvent(event);
}

void NemoWindow::mousePressEvent(QMouseEvent* event)
{
    if (!event || event->source() != Qt::MouseEventNotSynthesized) {
        cancelBackGesture();
        return;
    }

    beginBackGesture(GestureInput::Mouse, event->position());
}

void NemoWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (!event || m_gestureInput != GestureInput::Mouse) {
        if (event && event->source() != Qt::MouseEventNotSynthesized) {
            cancelBackGesture();
        }
        return;
    }

    finishBackGesture(event->position());
}

void NemoWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (!event || m_gestureInput != GestureInput::Mouse) {
        return;
    }

    updateBackGesture(event->position());
}

void NemoWindow::touchEventHandler(QEvent* event)
{
    auto* tEvent = static_cast<QTouchEvent*>(event);
    if (!tEvent || tEvent->points().isEmpty()) {
        return;
    }

    const QPointF pos = tEvent->points().first().position();

    switch (event->type()) {
    case QEvent::TouchBegin:
        beginBackGesture(GestureInput::Touch, pos);
        break;
    case QEvent::TouchUpdate:
        if (m_gestureInput == GestureInput::Touch) {
            updateBackGesture(pos);
        }
        break;
    case QEvent::TouchEnd:
        if (m_gestureInput == GestureInput::Touch) {
            finishBackGesture(pos);
        }
        break;
    case QEvent::TouchCancel:
        if (m_gestureInput == GestureInput::Touch) {
            cancelBackGesture();
        }
        break;
    default:
        break;
    }
}

bool NemoWindow::allowExtendedEvents() const
{
    if (qEnvironmentVariableIsSet("NEMO_DISABLE_EXTENDED_EVENTS")) {
        return false;
    }
    return m_allowExtendedEvents;
}

void NemoWindow::setAllowExtendedEvents(bool newAllowExtendedEvents)
{
    if (qEnvironmentVariableIsSet("NEMO_DISABLE_EXTENDED_EVENTS") && newAllowExtendedEvents) {
        qWarning() << "Extended events disabled in env";
        return;
    }

    if (m_allowExtendedEvents == newAllowExtendedEvents) {
        return;
    }
    m_allowExtendedEvents = newAllowExtendedEvents;
    emit allowExtendedEventsChanged();
}

qreal NemoWindow::backGestureThreshold() const
{
    return m_backGestureThreshold;
}

void NemoWindow::setBackGestureThreshold(qreal threshold)
{
    const qreal normalized = clampedGestureThreshold(threshold);
    if (qFuzzyCompare(m_backGestureThreshold, normalized)) {
        return;
    }
    m_backGestureThreshold = normalized;
    emit backGestureThresholdChanged();
}

Qt::Edge NemoWindow::backGestureEdge() const
{
    return m_backGestureEdge;
}

void NemoWindow::setBackGestureEdge(Qt::Edge edge)
{
    if (!isValidBackGestureEdge(edge)) {
        qWarning() << "Unsupported back gesture edge, falling back to Qt::LeftEdge";
        edge = Qt::LeftEdge;
    }

    if (m_backGestureEdge == edge) {
        return;
    }

    m_backGestureEdge = edge;
    emit backGestureEdgeChanged();
}

void NemoWindow::beginBackGesture(GestureInput input, const QPointF& pos)
{
    if (input == GestureInput::None) {
        return;
    }

    if (m_gestureInput != GestureInput::None && m_gestureInput != input) {
        return;
    }

    m_gestureInput = input;
    m_gestureStartPos = pos;
    m_gestureTriggered = false;

    if (!allowExtendedEvents() || !isWithinBackGestureEdge(pos)) {
        cancelBackGesture();
    }
}

void NemoWindow::updateBackGesture(const QPointF& pos)
{
    if (m_gestureInput == GestureInput::None) {
        return;
    }

    if (!allowExtendedEvents() || !isWithinBackGestureEdge(m_gestureStartPos)) {
        cancelBackGesture();
        return;
    }

    m_gestureTriggered = hasReachedBackGestureDistance(pos);
}

void NemoWindow::finishBackGesture(const QPointF& pos)
{
    if (m_gestureInput == GestureInput::None) {
        return;
    }

    updateBackGesture(pos);
    if (m_gestureTriggered && allowExtendedEvents()) {
        emit goBack();
    }

    cancelBackGesture();
}

void NemoWindow::cancelBackGesture()
{
    m_gestureInput = GestureInput::None;
    m_gestureTriggered = false;
    m_gestureStartPos = QPointF();
}

bool NemoWindow::isWithinBackGestureEdge(const QPointF& pos) const
{
    const qreal edgeArea = qMax<qreal>(0.0, width() * m_backGestureThreshold);

    switch (m_backGestureEdge) {
    case Qt::LeftEdge:
        return pos.x() <= edgeArea;
    case Qt::RightEdge:
        return pos.x() >= (width() - edgeArea);
    default:
        return false;
    }
}

bool NemoWindow::hasReachedBackGestureDistance(const QPointF& pos) const
{
    const qreal distanceThreshold = qMax<qreal>(0.0, width() * m_backGestureThreshold);

    switch (m_backGestureEdge) {
    case Qt::LeftEdge:
        return (pos.x() - m_gestureStartPos.x()) >= distanceThreshold;
    case Qt::RightEdge:
        return (m_gestureStartPos.x() - pos.x()) >= distanceThreshold;
    default:
        return false;
    }
}
