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

#ifndef NEMOWINDOW_H
#define NEMOWINDOW_H

#include "editfilter.h"
#include <QPointF>
#include <QQuickWindow>

class NemoWindow : public QQuickWindow {
    Q_OBJECT
    Q_PROPERTY(bool allowExtendedEvents READ allowExtendedEvents WRITE setAllowExtendedEvents NOTIFY allowExtendedEventsChanged)
    Q_PROPERTY(qreal backGestureThreshold READ backGestureThreshold WRITE setBackGestureThreshold NOTIFY backGestureThresholdChanged)
    Q_PROPERTY(Qt::Edge backGestureEdge READ backGestureEdge WRITE setBackGestureEdge NOTIFY backGestureEdgeChanged)

public:
    explicit NemoWindow(QWindow* parent = nullptr);
    Qt::ScreenOrientation primaryOrientation() const;

    bool allowExtendedEvents() const;
    void setAllowExtendedEvents(bool newAllowExtendedEvents);

    qreal backGestureThreshold() const;
    void setBackGestureThreshold(qreal threshold);

    Qt::Edge backGestureEdge() const;
    void setBackGestureEdge(Qt::Edge edge);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

signals:
    void orientationChanged(Qt::ScreenOrientation orientation);
    void goBack();

    void allowExtendedEventsChanged();
    void backGestureThresholdChanged();
    void backGestureEdgeChanged();

private slots:
    void touchEventHandler(QEvent* event);

private:
    enum class GestureInput {
        None,
        Mouse,
        Touch
    };

    void beginBackGesture(GestureInput input, const QPointF& pos);
    void updateBackGesture(const QPointF& pos);
    void finishBackGesture(const QPointF& pos);
    void cancelBackGesture();
    bool isWithinBackGestureEdge(const QPointF& pos) const;
    bool hasReachedBackGestureDistance(const QPointF& pos) const;

    EditFilter* m_filter;
    QScreen* m_screen;

    GestureInput m_gestureInput;
    bool m_gestureTriggered;
    QPointF m_gestureStartPos;
    bool m_allowExtendedEvents;
    qreal m_backGestureThreshold;
    Qt::Edge m_backGestureEdge;
};

#endif // NEMOWINDOW_H
