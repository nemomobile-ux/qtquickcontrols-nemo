/*
 * Copyright (C) 2023 Chupligin Sergey <neochapay@gmail.com>
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

#include "inversemousearea.h"
#include <QQuickWindow>

InverseMouseArea::InverseMouseArea(QQuickItem* parent)
    : QQuickItem(parent)
    , m_active(true)
{
    connect(this, &QQuickItem::windowChanged, this, &InverseMouseArea::resetFilterOnWindowUpdate);

    connect(this, &QQuickItem::enabledChanged, this, &InverseMouseArea::update);
    connect(this, &QQuickItem::visibleChanged, this, &InverseMouseArea::update);
}

bool InverseMouseArea::active() const
{
    return m_active;
}

void InverseMouseArea::setActive(bool newActive)
{
    if (m_active == newActive) {
        return;
    }

    m_active = newActive;

    emit activeChanged();
}

bool InverseMouseArea::eventFilter(QObject* object, QEvent* event)
{
    Q_UNUSED(object);
    if (m_active && event->type() == QEvent::MouseButtonPress && !this->contains(static_cast<QMouseEvent*>(event)->pos())) {
        emit pressed();
    }
    return false;
}

void InverseMouseArea::itemChange(ItemChange change, const ItemChangeData value)
{
    Q_UNUSED(value);
    if (m_active && change == ItemSceneChange && window()) {
        window()->installEventFilter(this);
    }
}

void InverseMouseArea::resetFilterOnWindowUpdate(QQuickWindow* win)
{
    if (win) {
        win->installEventFilter(this);
    }
}

bool InverseMouseArea::contains(const QPointF& point) const
{
    if (!m_active) {
        return false;
    }

    QPointF scenePos = mapToItem(parentItem(), point);
    QPointF global = parentItem()->mapToScene(QPointF(0, 0));

    bool cont = QRectF(global.x(), global.y(), parentItem()->width(), parentItem()->height()).contains(scenePos);
    return cont;
}
