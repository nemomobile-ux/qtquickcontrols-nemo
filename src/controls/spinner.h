/*
 * Copyright (C) 2021 Chupligin Sergey <neochapay@gmail.com>
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

#ifndef SPINNER_H
#define SPINNER_H

#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QQuickPaintedItem>
#include <QSequentialAnimationGroup>
#include <QTimer>

#include "theme.h"

class AnimatedBrush : public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    AnimatedBrush()
    {
        m_brush = QBrush(QColor("black"));
        m_brush.setStyle(Qt::SolidPattern); // fill color is active
    }

    QColor color() const
    {
        return m_brush.color();
    }

    void setColor(const QColor& c)
    {
        m_brush.setColor(c);
    }

    void paint(QPainter *painter) {Q_UNUSED(painter)}

    QBrush get() {return m_brush;}

    QBrush m_brush;

signals:
    void colorChanged();
};

class Spinner : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

public:
    explicit Spinner(QQuickItem *parent = nullptr);
    void paint(QPainter *painter);
    bool enabled() {return m_enabled;}
    void setEnabled(bool enabled);

signals:
    void enabledChanged();

private:
    void reset();

    QSequentialAnimationGroup *spinAnim;
    QParallelAnimationGroup *step1;
    QParallelAnimationGroup *step2;
    QParallelAnimationGroup *step3;
    QParallelAnimationGroup *step4;

    Theme *m_theme;

    QRect m_circle1;
    QRect m_circle2;
    QRect m_circle3;
    QRect m_circle4;

    AnimatedBrush *colorCircle1;
    AnimatedBrush *colorCircle2;
    AnimatedBrush *colorCircle3;
    AnimatedBrush *colorCircle4;

    QTimer *m_updateTimer;

    QPropertyAnimation *circle1toAccentColor;
    QPropertyAnimation *circle2toAccentColor;
    QPropertyAnimation *circle3toAccentColor;
    QPropertyAnimation *circle4toAccentColor;

    QPropertyAnimation *circle1toBackgroundColor;
    QPropertyAnimation *circle2toBackgroundColor;
    QPropertyAnimation *circle3toBackgroundColor;
    QPropertyAnimation *circle4toBackgroundColor;

    bool m_enabled;
};

#endif // SPINNER_H
