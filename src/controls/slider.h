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


#ifndef SLIDER_H
#define SLIDER_H

#include <QQuickPaintedItem>
#include <QPainter>

#include "theme.h"

class Slider: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(double minimumValue READ minimumValue WRITE setMinimumValue NOTIFY minimumValueChanged)
    Q_PROPERTY(double maximumValue READ maximumValue WRITE setMaximumValue NOTIFY maximumValueChanged)
    Q_PROPERTY(int decimalPlaces  READ decimalPlaces  WRITE setdecimalPlaces  NOTIFY decimalPlacesChanged)
    Q_PROPERTY(bool showValue READ showValue WRITE setShowValue NOTIFY showValueChanged)

public:
    Slider(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;

    double value() {return m_value;}
    void setValue(double value);

    double minimumValue() {return m_minimumValue;}
    void setMinimumValue(double minValue);

    double maximumValue() {return m_maximumValue;}
    void setMaximumValue(double maxValue);

    int decimalPlaces() {return m_decimalPlaces;}
    void setdecimalPlaces(int places);

    bool showValue() {return m_showValue;}
    void setShowValue(bool show);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void touchEvent(QTouchEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void valueChanged();
    void minimumValueChanged();
    void maximumValueChanged();
    void decimalPlacesChanged();
    void showValueChanged();

private:
    Theme m_theme;
    double m_value;
    double m_minimumValue;
    double m_maximumValue;
    int m_decimalPlaces;
    bool m_showValue;
    bool m_mouseButtonPressed;

    void m_calculateSlider(float x);

};

#endif // SLIDER_H
