/*
 * Copyright (C) 2013 Andrea Bernabei <and.bernabei@gmail.com>
 * Copyright (C) 2021-2023 Chupligin Sergey <neochapay@gmail.com>
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

#ifndef NEMOWINDOW_H
#define NEMOWINDOW_H

#include "editfilter.h"
#include <QQuickWindow>

class NemoWindow : public QQuickWindow {
    Q_OBJECT
    Q_PROPERTY(bool allowExtendedEvents READ allowExtendedEvents WRITE setAllowExtendedEvents NOTIFY allowExtendedEventsChanged)

public:
    explicit NemoWindow(QWindow* parent = 0);
    Qt::ScreenOrientation primaryOrientation() const;

    bool allowExtendedEvents() const;
    void setAllowExtendedEvents(bool newAllowExtendedEvents);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent* event) override;

signals:
    void orientationChanged(Qt::ScreenOrientation orientation);
    void goBack();

    void allowExtendedEventsChanged();

private:
    EditFilter* m_filter;
    QScreen* m_screen;

    bool m_mousePressed;
    bool m_mouseEventTriggered;
    QPointF m_firstPoint;
    bool m_allowExtendedEvents;
};

#endif // NEMOWINDOW_H
