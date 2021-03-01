/****************************************************************************************
**
** Copyright (C) 2021 Chupligin Sergey <neochapay@gmail.com>
** All rights reserved.
**
** You may use this file under the terms of BSD license as follows:
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the author nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
** ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************************/

#include "slider.h"

Slider::Slider(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_theme(new Theme())
    , m_value(0)
    , m_minimumValue(0)
    , m_maximumValue(1)
    , m_decimalPlaces(0)
    , m_showValue(false)
    , m_mouseButtonPressed(false)

{
    setWidth(m_theme.itemWidthLarge());
    setHeight(m_theme.itemHeightExtraSmall());
    setClip(false);

    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
}

void Slider::paint(QPainter *painter)
{
    QBrush fillDarkColorBruch(QColor(m_theme.fillDarkColor()));
    QBrush accentColorBrush(QColor(m_theme.accentColor()));
    QBrush backgroundColorBrush(QColor(m_theme.backgroundColor()));

    QPen indPen(QColor(m_theme.textColor()), m_theme.size->ratio(2),  Qt::SolidLine, Qt::FlatCap, Qt::BevelJoin);

    QSizeF itemSize = size();

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);
    painter->setPen(Qt::NoPen);

    /*Draw packground*/
    painter->setBrush(fillDarkColorBruch);
    painter->drawRect(QRect(0,itemSize.height()/4
                            ,itemSize.width()
                            ,itemSize.height()/2));
    /*Draw valueLine*/
    painter->setBrush(accentColorBrush);
    painter->drawRect(QRect(0,itemSize.height()/4
                            ,itemSize.width()*m_value/m_maximumValue
                            ,itemSize.height()/2));

    /*Draw polygon to value point*/
    float valueOffcet = itemSize.width()*m_value/m_maximumValue-itemSize.height()/2;
    float polyXOffcet = 0;

    if(valueOffcet >= itemSize.height()) {
        polyXOffcet = valueOffcet-itemSize.height();
    }

    QPointF polyPoints[4] = {
        QPointF(polyXOffcet,itemSize.height()/4),
        QPointF(valueOffcet+itemSize.height()/2, 0),
        QPointF(valueOffcet+itemSize.height()/2, itemSize.height()),
        QPointF(polyXOffcet,itemSize.height()/4*3)
    };

    painter->setBrush(accentColorBrush);
    painter->drawPolygon(polyPoints, 4);

    /*Draw point of values*/
    QRect valueRect(valueOffcet,
                         m_theme.size->ratio(1),
                         itemSize.height()-m_theme.size->ratio(2),
                         itemSize.height()-m_theme.size->ratio(2)
                       );

    painter->setBrush(backgroundColorBrush);
    painter->setPen(indPen);
    painter->drawEllipse(valueRect);
    /*Show value if needed*/
    if(m_showValue) {

        QFont font = painter->font();
        font.setPixelSize(m_theme.fontSizeTiny());
        painter->setFont(font);

        painter->drawText(valueRect
                          , Qt::AlignCenter
                          , QString::number(m_value, 'f', m_decimalPlaces));
    }
}

void Slider::setdecimalPlaces(int places)
{
    if(places != m_decimalPlaces) {
        m_decimalPlaces = places;
        emit decimalPlacesChanged();
    }
}

void Slider::setValue(qreal value)
{
    if(value != m_value && value >= m_minimumValue && value <= m_maximumValue) {
        m_value = value;
        emit valueChanged();
        update();
    }
}

void Slider::setMinimumValue(qreal minValue)
{
    if(minValue != m_minimumValue) {
        m_minimumValue = minValue;
        emit valueChanged();
        update();
    }
}

void Slider::setMaximumValue(qreal maxValue)
{
    if(maxValue != m_maximumValue) {
        m_maximumValue = maxValue;
        emit maximumValueChanged();
        update();
    }
}

void Slider::setShowValue(bool show)
{
    if(show != m_showValue) {
        m_showValue = show;
        emit showValueChanged();
        update();
    }
}

void Slider::mousePressEvent(QMouseEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress) {
        m_mouseButtonPressed = true;
    }

    if(event->type() == QEvent::MouseButtonRelease) {
        m_mouseButtonPressed = false;
    }
}

void Slider::mouseMoveEvent(QMouseEvent *event)
{
    if(m_mouseButtonPressed) {
        m_calculateSlider(event->pos().x());
    }
}

void Slider::touchEvent(QTouchEvent *event)
{
    m_calculateSlider(event->touchPoints().first().pos().x());
}

void Slider::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_calculateSlider(event->pos().x());
}

void Slider::m_calculateSlider(float x)
{
    if(x < 0) {
        return;
    }
    float fullWidth = size().width();
    float currValue = x/fullWidth*(m_maximumValue-m_minimumValue)+m_minimumValue;
    setValue(currValue);
}
