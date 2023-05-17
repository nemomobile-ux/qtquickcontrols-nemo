/*
 * Copyright (C) 2018-2021 Chupligin Sergey <neochapay@gmail.com>
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

#ifndef SIZING_H
#define SIZING_H

#include <QObject>
#include <QSize>
#include <QSizeF>

class Sizing : public QObject {
    Q_OBJECT

    enum Densitie {
        ldpi,
        mdpi,
        hdpi,
        xhdpi,
        xxhdpi,
        xxxhdpi
    };
    Q_ENUMS(Densities)

    Q_PROPERTY(float mmScaleFactor READ mmScaleFactor WRITE setMmScaleFactor NOTIFY mmScaleFactorChanged)
    Q_PROPERTY(float dpScaleFactor READ dpScaleFactor NOTIFY dpScaleFactorChanged)

    Q_PROPERTY(Densitie densitie READ densitie NOTIFY densitieChanged)

public:
    explicit Sizing(QObject* parent = 0);

    float mmScaleFactor() { return m_mmScaleFactor; }
    float dpScaleFactor() { return m_dpScaleFactor; }

    Densitie densitie() { return m_densitie; };

    void setMmScaleFactor(float value);
    void setDpScaleFactor();

    Q_INVOKABLE float dp(float value);
    Q_INVOKABLE float mm(float value);

signals:
    void mmScaleFactorChanged();
    void dpScaleFactorChanged();
    void densitieChanged();
    void screenDPIChanged();

private slots:
    void physicalDotsPerInchChanged(qreal dpi);
    void physicalSizeChanged(const QSizeF& size);

private:
    QSizeF m_physicalScreenSize;
    QSize m_screenSize;

    float m_mmScaleFactor;
    float m_dpScaleFactor;

    qreal m_screenDPI;
    Densitie m_densitie;

    bool m_forceDpiScaleFactor;
};

#endif // SIZING_H
