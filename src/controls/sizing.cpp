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

#include <QScreen>
#include <QDebug>
#include <QGuiApplication>
#include <math.h>

const qreal refHeight =  1440; //HD
const qreal refWidth = 720; //HD

Sizing::Sizing(QObject *parent)
    : QObject(parent)
    , m_physicalScreenSize(QSize(67,136))
    , m_screenSize(QSize(refWidth, refHeight))
    , m_mmScaleFactor(10)
    , m_dpScaleFactor(1)
    , m_screenDPI(0)
    , m_densitie(mdpi)
{
    int physicalScreenHeight = qEnvironmentVariableIntValue("QT_QPA_EGLFS_PHYSICAL_HEIGHT");
    int physicalScreenWidth = qEnvironmentVariableIntValue("QT_QPA_EGLFS_PHYSICAL_WIDTH");
    qreal screenDPI = qEnvironmentVariableIntValue("QT_WAYLAND_FORCE_DPI");

    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    connect(primaryScreen, &QScreen::physicalDotsPerInchChanged, this, &Sizing::physicalDotsPerInchChanged);
    connect(primaryScreen, &QScreen::physicalSizeChanged, this, &Sizing::physicalSizeChanged);

    if(QGuiApplication::screens().count() == 0) {
        qWarning() << "Qt not see any screens. Use defaults values";
    } else {
        /*If we dont have everoment of physical size try get it from screen*/
        if (physicalScreenHeight == 0 || physicalScreenWidth == 0) {
            qWarning("QT_QPA_EGLFS_PHYSICAL_WIDTH or QT_QPA_EGLFS_PHYSICAL_HEIGHT is not set! \n"
                     "Trying to use QScreenSize");
            physicalSizeChanged(primaryScreen->physicalSize());
        } else {
            physicalSizeChanged(QSizeF(physicalScreenHeight, physicalScreenWidth));
        }


        if (screenDPI == 0) {
            screenDPI = primaryScreen->physicalDotsPerInch();
        } else {
            qInfo() << "Use DPI from QT_WAYLAND_FORCE_DPI enveroment = " << screenDPI;
        }

        physicalDotsPerInchChanged(screenDPI);
    }
}

void Sizing::setDpScaleFactor(float value) {
    if(value != m_dpScaleFactor && value != 0) {
        m_dpScaleFactor = value;
        emit dpScaleFactorChanged();
    }
}

void Sizing::setMmScaleFactor(float value) {
    if(value != m_mmScaleFactor && value != 0) {
        m_mmScaleFactor = value;
        emit mmScaleFactorChanged();
    }
}

float Sizing::dp(float value) {
    return value*m_dpScaleFactor;
}

float Sizing::mm(float value) {
    qWarning("Dont use size.mm(value)! Use value*size.mmScaleFactor");
    return value*m_mmScaleFactor;
}

void Sizing::physicalDotsPerInchChanged(qreal dpi)
{
    if(dpi == m_screenDPI) {
        return;
    }

    qDebug() << "Screen DPI is: " << dpi;

    Densitie densitie;
    qreal dpScaleFactor;

    if (dpi < 100) {
        densitie = ldpi;
        dpScaleFactor = 1;
    } else if (dpi >= 100 && dpi < 200) {
        densitie = mdpi;
        dpScaleFactor = 1.5;
    } else if (dpi >= 200 && dpi < 300) {
        densitie = hdpi;
        dpScaleFactor = 2;
    } else if(dpi >= 300 && dpi < 450) {
        densitie = xhdpi;
        dpScaleFactor = 2.5;
    } else if(dpi >= 450 && dpi < 600) {
        densitie = xxhdpi;
        dpScaleFactor = 3;
    } else {
        densitie = xxxhdpi;
        dpScaleFactor = 3.5;
    }

    m_screenDPI = dpi;
    emit screenDPIChanged();

    if(densitie != m_densitie) {
        m_densitie = densitie;
        emit densitieChanged();
    }

    if(dpScaleFactor != m_dpScaleFactor) {
        m_dpScaleFactor = dpScaleFactor;
        emit dpScaleFactorChanged();
    }
}

void Sizing::physicalSizeChanged(const QSizeF &size)
{
    if(size != m_physicalScreenSize) {
        m_physicalScreenSize = size;
        float mmScaleFactor = m_screenSize.width()/size.width();

        if(mmScaleFactor != m_mmScaleFactor) {
            emit mmScaleFactorChanged();
        }
    }
}
