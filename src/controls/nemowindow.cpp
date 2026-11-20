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
#include <QScreen>

NemoWindow::NemoWindow(QWindow* parent)
    : QQuickWindow(parent)
    , m_filter(new EditFilter(this))
    , m_screen(screen())
    , m_mousePressed(false)
    , m_mouseEventTriggered(false)
    , m_firstPoint(QPointF())
    , m_hideStatusBar(false)
{
    if (qEnvironmentVariableIsSet("NEMO_DISABLE_EXTENDED_EVENTS")) {
        m_allowExtendedEvents = false;
    } else {
        m_allowExtendedEvents = true;
    }

    installEventFilter(m_filter);
    connect(m_screen, &QScreen::orientationChanged, this, &NemoWindow::orientationChanged);
    connect(m_filter, &EditFilter::touchEvent, this, &NemoWindow::touchEventHandler);
    connect(m_filter, &EditFilter::backEvent, this, &NemoWindow::goBack);
}

Qt::ScreenOrientation NemoWindow::primaryOrientation() const
{

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

void NemoWindow::mousePressEvent(QMouseEvent*)
{
    m_mousePressed = true;
    m_mouseEventTriggered = false;
    m_firstPoint = QPointF();
}

void NemoWindow::mouseReleaseEvent(QMouseEvent*)
{
    m_mousePressed = false;
    if (m_mouseEventTriggered && allowExtendedEvents()) {
        emit goBack();
    }
    m_mouseEventTriggered = false;
    m_firstPoint = QPointF();
}

void NemoWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_mousePressed || event->points().isEmpty()) {
        return;
    }

    if (m_firstPoint.isNull()) {
        m_firstPoint = event->points().first().position();
    }

    const QPointF currentPos = event->points().first().position();
    if (currentPos.x() - m_firstPoint.x() > width() / 4
        && m_firstPoint.x() < width() / 4) {
        m_mouseEventTriggered = true;
    } else {
        m_mouseEventTriggered = false;
    }
}

void NemoWindow::touchEventHandler(QEvent* event)
{
    QTouchEvent* tEvent = static_cast<QTouchEvent*>(event);
    if (tEvent->points().isEmpty()) {
        return;
    }

    if (event->type() == QEvent::TouchBegin) {
        m_mousePressed = true;
        m_mouseEventTriggered = false;
        m_firstPoint = tEvent->points().first().position();
    } else if (event->type() == QEvent::TouchEnd) {
        const QPointF endPos = tEvent->points().first().position();
        if (endPos.x() - m_firstPoint.x() > width() / 4
            && m_firstPoint.x() < width() / 4
            && allowExtendedEvents()) {
            emit goBack();
        }
        m_mousePressed = false;
        m_mouseEventTriggered = false;
        m_firstPoint = QPointF();
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

bool NemoWindow::hideStatusBar() const
{
    return m_hideStatusBar;
}

void NemoWindow::setHideStatusBar(bool newHideStatusBar)
{
    if (m_hideStatusBar == newHideStatusBar)
        return;
    m_hideStatusBar = newHideStatusBar;
    emit hideStatusBarChanged();
}
