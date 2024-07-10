/*
 * Copyright (C) 2018-2024 Chupligin Sergey <neochapay@gmail.com>
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
#include "logging.h"

#include <MGConfItem>
#include <QGuiApplication>
#include <QScreen>
#include <math.h>

Sizing::Sizing(QObject* parent)
    : QObject(parent)
    , m_mmScaleFactor(10)
    , m_dpScaleFactor(1)
    , m_screenDPI(0)
{
    // All sizes we get from LipstickSettings::exportScreenProperties()
    MGConfItem* physicalDotsPerInchConf = new MGConfItem("/lipstick/screen/primary/physicalDotsPerInch");
    connect(physicalDotsPerInchConf, &MGConfItem::valueChanged, this, &Sizing::recalcConstants);
    if (physicalDotsPerInchConf->value().isNull()) {
        QScreen* primaryScreen = QGuiApplication::primaryScreen();
        physicalDotsPerInchConf->set(primaryScreen->physicalDotsPerInch());
        physicalDotsPerInchConf->sync();
    }

    recalcConstants();
}

void Sizing::setDpScaleFactor()
{
    MGConfItem* dpScaleFactorValue = new MGConfItem(QStringLiteral("/nemo/apps/libglacier/dpScaleFactor"));
    float value = dpScaleFactorValue->value("0").toFloat();

    if (value != m_dpScaleFactor && value != 0) {
        m_dpScaleFactor = value;
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
    return value * m_mmScaleFactor;
}

void Sizing::recalcConstants()
{
    qreal dpi = MGConfItem("/lipstick/screen/primary/physicalDotsPerInch").value().toReal();

    if (dpi == m_screenDPI) {
        return;
    }

    qCDebug(lcNemoControlsCoreLog) << "Screen DPI is: " << dpi;

    float dpScaleFactor;

    if (dpi < 200) {
        dpScaleFactor = 1;
    } else if (dpi >= 200 && dpi < 300) {
        dpScaleFactor = 1.5;
    } else if (dpi >= 300 && dpi < 450) {
        dpScaleFactor = 2;
    } else {
        dpScaleFactor = 2.5;
    }

    m_screenDPI = dpi;
    emit screenDPIChanged();

    if (dpScaleFactor != m_dpScaleFactor) {
        m_dpScaleFactor = dpScaleFactor;
        emit dpScaleFactorChanged();
    }

    float pixelsInMM = dpi / 2.45 / 10;
    if (pixelsInMM != m_mmScaleFactor) {
        m_mmScaleFactor = pixelsInMM;
        emit mmScaleFactorChanged();
    }
}
