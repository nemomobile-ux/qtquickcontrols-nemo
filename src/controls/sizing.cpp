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

#include "sizing.h"

#include <MGConfItem>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <math.h>

const qreal refHeight = 1440; // HD
const qreal refWidth = 720; // HD

Sizing::Sizing(QObject* parent)
    : QObject(parent)
    , m_physicalScreenSize(QSize(67, 136))
    , m_screenSize(QSize(refWidth, refHeight))
    , m_mmScaleFactor(10)
    , m_dpScaleFactor(1)
    , m_screenDPI(0)
    , m_densitie(mdpi)
    , m_forceDpiScaleFactor(false)
{
    qreal physicalScreenHeight = qEnvironmentVariableIntValue("QT_QPA_EGLFS_PHYSICAL_HEIGHT");
    qreal physicalScreenWidth = qEnvironmentVariableIntValue("QT_QPA_EGLFS_PHYSICAL_WIDTH");

    MGConfItem* dpScaleFactorValue = new MGConfItem(QStringLiteral("/nemo/apps/libglacier/dpScaleFactor"));
    if (dpScaleFactorValue->value("0").toFloat() != 0) {
        m_forceDpiScaleFactor = true;
        m_dpScaleFactor = dpScaleFactorValue->value().toFloat();
    }
    connect(dpScaleFactorValue, &MGConfItem::valueChanged, this, &Sizing::setDpScaleFactor);

    QScreen* primaryScreen = QGuiApplication::primaryScreen();

    /*If we dont have everoment of physical size try get it from screen*/
    if (physicalScreenHeight == 0 || physicalScreenWidth == 0) {
        physicalScreenHeight = primaryScreen->physicalSize().height();
        physicalScreenWidth = primaryScreen->physicalSize().width();
    }

    connect(primaryScreen, &QScreen::physicalDotsPerInchChanged, this, &Sizing::physicalDotsPerInchChanged);
    connect(primaryScreen, &QScreen::physicalSizeChanged, this, &Sizing::physicalSizeChanged);

    if (QGuiApplication::screens().count() == 0) {
        qWarning() << "Qt not see any screens. Use defaults values";
    }

    physicalSizeChanged(QSizeF(physicalScreenHeight, physicalScreenWidth));

    /*Calculate dpi bacuse wayland compositor return aways is 100*/
    qreal calcDPI = primaryScreen->size().height() * 2.54 / physicalScreenHeight * 10;

    physicalDotsPerInchChanged(calcDPI);
}

void Sizing::setDpScaleFactor()
{
    MGConfItem* dpScaleFactorValue = new MGConfItem(QStringLiteral("/nemo/apps/libglacier/dpScaleFactor"));
    float value = dpScaleFactorValue->value("0").toFloat();

    if (value != m_dpScaleFactor && value != 0) {
        m_dpScaleFactor = value;
        m_forceDpiScaleFactor = true;
        emit dpScaleFactorChanged();
    }
}

void Sizing::setMmScaleFactor(float value)
{
    if (value != m_mmScaleFactor && value != 0) {
        m_mmScaleFactor = value;
        emit mmScaleFactorChanged();
    }
}

float Sizing::dp(float value)
{
    return value * m_dpScaleFactor;
}

float Sizing::mm(float value)
{
    qWarning("Dont use size.mm(value)! Use value*size.mmScaleFactor");
    return value * m_mmScaleFactor;
}

void Sizing::physicalDotsPerInchChanged(qreal dpi)
{
    if (dpi == m_screenDPI) {
        return;
    }

    qDebug() << "Screen DPI is: " << dpi;

    Densitie densitie;
    qreal dpScaleFactor;

    if (dpi < 200) {
        densitie = ldpi;
        dpScaleFactor = 1;
    } else if (dpi >= 200 && dpi < 300) {
        densitie = hdpi;
        dpScaleFactor = 1.5;
    } else if (dpi >= 300 && dpi < 450) {
        densitie = xhdpi;
        dpScaleFactor = 2;
    } else if (dpi >= 450 && dpi < 600) {
        densitie = xxhdpi;
        dpScaleFactor = 2.5;
    } else {
        densitie = xxxhdpi;
        dpScaleFactor = 3;
    }

    m_screenDPI = dpi;
    emit screenDPIChanged();

    if (densitie != m_densitie) {
        m_densitie = densitie;
        emit densitieChanged();
    }

    if (dpScaleFactor != m_dpScaleFactor && !m_forceDpiScaleFactor) {
        m_dpScaleFactor = dpScaleFactor;
        emit dpScaleFactorChanged();
    }
}

void Sizing::physicalSizeChanged(const QSizeF& size)
{
    if (size != m_physicalScreenSize) {
        m_physicalScreenSize = size;
        float mmScaleFactor = m_screenSize.width() / size.width();

        if (mmScaleFactor != m_mmScaleFactor) {
            emit mmScaleFactorChanged();
        }
    }
}
