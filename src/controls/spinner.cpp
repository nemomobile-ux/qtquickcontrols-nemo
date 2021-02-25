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

#include "spinner.h"

#include <QPropertyAnimation>

Spinner::Spinner(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_enabled(true)
{
    m_theme = new Theme();
    setWidth(m_theme->itemHeightMedium());
    setHeight(m_theme->itemHeightMedium());

    QSizeF itemSize = size();
    int circleSize = (int)(itemSize.width()/2-m_theme->itemSpacingMedium()/8);

    m_circle1 = QRect(0,
                      0,
                      circleSize,
                      circleSize);

    m_circle2 = QRect(itemSize.width()/2+m_theme->itemSpacingMedium()/8,
                      0,
                      circleSize,
                      circleSize);

    m_circle4 = QRect(0,
                      itemSize.width()/2+m_theme->itemSpacingMedium()/8,
                      circleSize,
                      circleSize);

    m_circle3 = QRect(itemSize.width()/2+m_theme->itemSpacingMedium()/8,
                      itemSize.width()/2+m_theme->itemSpacingMedium()/8,
                      circleSize,
                      circleSize);

    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout,
            this,  [this]() {update();});

    spinAnim  = new QSequentialAnimationGroup();
    step1 = new QParallelAnimationGroup();
    step2 = new QParallelAnimationGroup();
    step3 = new QParallelAnimationGroup();
    step4 = new QParallelAnimationGroup();

    colorCircle1 = new AnimatedBrush();
    colorCircle2 = new AnimatedBrush();
    colorCircle3 = new AnimatedBrush();
    colorCircle4 = new AnimatedBrush();

    colorCircle1->setColor(QColor(m_theme->backgroundAccentColor()));
    colorCircle2->setColor(QColor(m_theme->backgroundAccentColor()));
    colorCircle3->setColor(QColor(m_theme->backgroundAccentColor()));
    colorCircle4->setColor(QColor(m_theme->backgroundAccentColor()));

    circle1toAccentColor = new QPropertyAnimation(colorCircle1, "color");
    circle1toAccentColor->setDuration(400);
    circle1toAccentColor->setStartValue(m_theme->backgroundAccentColor());
    circle1toAccentColor->setEndValue(m_theme->accentColor());

    circle2toAccentColor = new QPropertyAnimation(colorCircle2, "color");
    circle2toAccentColor->setDuration(400);
    circle2toAccentColor->setStartValue(m_theme->backgroundAccentColor());
    circle2toAccentColor->setEndValue(m_theme->accentColor());

    circle3toAccentColor = new QPropertyAnimation(colorCircle3, "color");
    circle3toAccentColor->setDuration(400);
    circle3toAccentColor->setStartValue(m_theme->backgroundAccentColor());
    circle3toAccentColor->setEndValue(m_theme->accentColor());

    circle4toAccentColor = new QPropertyAnimation(colorCircle4, "color");
    circle4toAccentColor->setDuration(400);
    circle4toAccentColor->setStartValue(m_theme->backgroundAccentColor());
    circle4toAccentColor->setEndValue(m_theme->accentColor());

    circle1toBackgroundColor = new QPropertyAnimation(colorCircle1, "color");
    circle1toBackgroundColor->setDuration(400);
    circle1toBackgroundColor->setStartValue(m_theme->accentColor());
    circle1toBackgroundColor->setEndValue(m_theme->backgroundAccentColor());

    circle2toBackgroundColor = new QPropertyAnimation(colorCircle2, "color");
    circle2toBackgroundColor->setDuration(400);
    circle2toBackgroundColor->setStartValue(m_theme->accentColor());
    circle2toBackgroundColor->setEndValue(m_theme->backgroundAccentColor());

    circle3toBackgroundColor = new QPropertyAnimation(colorCircle3, "color");
    circle3toBackgroundColor->setDuration(400);
    circle3toBackgroundColor->setStartValue(m_theme->accentColor());
    circle3toBackgroundColor->setEndValue(m_theme->backgroundAccentColor());

    circle4toBackgroundColor = new QPropertyAnimation(colorCircle4, "color");
    circle4toBackgroundColor->setDuration(400);
    circle4toBackgroundColor->setStartValue(m_theme->accentColor());
    circle4toBackgroundColor->setEndValue(m_theme->backgroundAccentColor());

    step1->addAnimation(circle1toAccentColor);
    step1->addAnimation(circle4toBackgroundColor);

    step2->addAnimation(circle2toAccentColor);
    step2->addAnimation(circle1toBackgroundColor);

    step3->addAnimation(circle3toAccentColor);
    step3->addAnimation(circle2toBackgroundColor);

    step4->addAnimation(circle4toAccentColor);
    step4->addAnimation(circle3toBackgroundColor);

    spinAnim->addAnimation(step1);
    spinAnim->addAnimation(step2);
    spinAnim->addAnimation(step3);
    spinAnim->addAnimation(step4);

    spinAnim->setLoopCount(-1);

/*Start by default*/
    spinAnim->start();
    m_updateTimer->start(40);
}

void Spinner::paint(QPainter *painter)
{
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setBrush(colorCircle1->get());
    painter->drawEllipse(m_circle1);

    painter->setBrush(colorCircle2->get());
    painter->drawEllipse(m_circle2);

    painter->setBrush(colorCircle3->get());
    painter->drawEllipse(m_circle3);

    painter->setBrush(colorCircle4->get());
    painter->drawEllipse(m_circle4);
}

void Spinner::setEnabled(bool enabled)
{
    if(enabled != m_enabled) {
        m_enabled = enabled;
        emit enabledChanged();
        if(!m_enabled) {
            reset();
        } else {
            QPropertyAnimation *goToForward = new QPropertyAnimation(this, "opacity");
            goToForward->setDuration(400);
            goToForward->setStartValue(0);
            goToForward->setEndValue(1);
            goToForward->start();

            spinAnim->start();
            m_updateTimer->start(100);
        }
    }
}

void Spinner::reset()
{
    m_updateTimer->stop();

    colorCircle1->setColor(QColor(m_theme->backgroundAccentColor()));
    colorCircle2->setColor(QColor(m_theme->backgroundAccentColor()));
    colorCircle3->setColor(QColor(m_theme->backgroundAccentColor()));
    colorCircle4->setColor(QColor(m_theme->backgroundAccentColor()));
    update();

    QPropertyAnimation *goToBack = new QPropertyAnimation(this, "opacity");
    goToBack->setDuration(400);
    goToBack->setStartValue(1);
    goToBack->setEndValue(0);
    goToBack->start();

    spinAnim->stop();
}
