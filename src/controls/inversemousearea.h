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

#ifndef INVERSEMOUSEAREA_H
#define INVERSEMOUSEAREA_H

#include <QQuickItem>
class QGraphicsSceneMouseEvent;

class InverseMouseArea : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

public:
    InverseMouseArea(QQuickItem* parent = nullptr);
    bool active() const;
    void setActive(bool newActive);

signals:
    void activeChanged();
    void pressed();

protected:
    bool eventFilter(QObject* object, QEvent* event);
    void itemChange(ItemChange change, const ItemChangeData value);
    bool contains(const QPointF& point) const;

private slots:
    void resetFilterOnWindowUpdate(QQuickWindow* win);

private:
    bool m_active;
    bool m_pressed;

    QPointF mapToRootItem(QPointF pos);
};

#endif // INVERSEMOUSEAREA_H
