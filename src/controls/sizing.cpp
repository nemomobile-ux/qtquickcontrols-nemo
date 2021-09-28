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

Sizing::Sizing(QObject *parent)
    : QObject(parent)
    , m_physicalScreenWidth(67)
    , m_physicalScreenHeight(136)
    , m_screenWidth(720)
    , m_screenHeight(1440)
    , m_mmScaleFactor(10)
    , m_dpScaleFactor(1.5)
    , m_densitie(mdpi)
{
    qreal refHeight =  1440; //HD
    qreal refWidth = 720; //HD

    m_physicalScreenHeight = qEnvironmentVariableIntValue("QT_QPA_EGLFS_PHYSICAL_HEIGHT");
    m_physicalScreenWidth = qEnvironmentVariableIntValue("QT_QPA_EGLFS_PHYSICAL_WIDTH");
    m_screenDPI = qEnvironmentVariableIntValue("QT_WAYLAND_FORCE_DPI");

    if(QGuiApplication::screens().count() == 0) {
        qWarning() << "Qt not see any screens. Use defaults values";
    } else {
        QScreen *screen = QGuiApplication::primaryScreen();

        /*If we dont have everoment of physical size try get it from screen*/
        if (m_physicalScreenHeight == 0 || m_physicalScreenWidth == 0) {
            qWarning("QT_QPA_EGLFS_PHYSICAL_WIDTH or QT_QPA_EGLFS_PHYSICAL_HEIGHT is not set! \n"
                     "Trying to use QScreenSize");

            m_physicalScreenHeight = screen->physicalSize().height();
            m_physicalScreenWidth = screen->physicalSize().width();
        }

        m_screenHeight = qMax(screen->size().width(), screen->size().height());
        m_screenWidth = qMin(screen->size().width(), screen->size().height());

        if (m_screenDPI == 0) {
            m_screenDPI = screen->physicalDotsPerInch();
        } else {
            qInfo() << "Use DPI from QT_WAYLAND_FORCE_DPI enveroment = " << m_screenDPI;
        }
    }

    m_scaleRatio = qMin((qreal)m_screenHeight/refHeight, (qreal)m_screenWidth/refWidth);
    m_fontRatio = floor(m_scaleRatio*10)/10;

    if (m_screenDPI < 140) {
        m_densitie = ldpi;
        m_dpScaleFactor = 0.5;
    } else if (m_screenDPI >= 140 && m_screenDPI < 200) {
        //~160dpi
        m_densitie = mdpi;
        m_dpScaleFactor = 0.6;
    } else if (m_screenDPI >= 200 && m_screenDPI < 300) {
        //~240dpi
        m_densitie = hdpi;
        m_dpScaleFactor = 1;
    } else if(m_screenDPI >= 300 && m_screenDPI < 420) {
        //~320dpi
        m_densitie = xhdpi;
        m_dpScaleFactor = 1.5;
    } else if(m_screenDPI >= 420 && m_screenDPI < 560) {
        //~480dpi
        m_densitie = xxhdpi;
        m_dpScaleFactor = 2;
    } else {
        m_densitie = xxxhdpi;
        m_dpScaleFactor = 2.5;
    }

    if (m_physicalScreenHeight > 0 && m_physicalScreenWidth > 0) {
        m_mmScaleFactor = (float)m_screenWidth/(float)m_physicalScreenWidth;
    } else {
        if (m_physicalScreenHeight == 0) {
            qWarning("QT_QPA_EGLFS_PHYSICAL_HEIGHT is not set!");
        }

        if (m_physicalScreenWidth == 0) {
            qWarning("QT_QPA_EGLFS_PHYSICAL_WIDTH is not set!");
        }
    }

    qDebug() << "Screen size: " << m_screenHeight << " x " << m_screenWidth;
    qDebug() << "Screen physical size: " << m_physicalScreenHeight << " x " << m_physicalScreenWidth;
    qDebug() << "Scale ratio: " << m_scaleRatio;
    qDebug() << "Font scale ratio: " << m_fontRatio;
    qDebug() << "DPI is " << m_screenDPI;
    qDebug() << "DP scale factor is " << m_dpScaleFactor;
    qDebug() << "MM scale factor is " << m_mmScaleFactor;
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

void Sizing::setScaleRatio(qreal scaleRatio) {
    if(m_scaleRatio != scaleRatio && scaleRatio != 0) {
        m_scaleRatio = scaleRatio;
        emit scaleRatioChanged();

        float fontRatio = floor(m_scaleRatio*10)/10;
        if(fontRatio != m_fontRatio) {
            m_fontRatio = floor(m_scaleRatio*10)/10;
            emit fontRatioChanged();
        }
    }
}

void Sizing::setFontRatio(qreal fontRatio) {
    if(m_fontRatio != fontRatio && fontRatio !=0 ) {
        m_fontRatio = fontRatio;
        emit fontRatioChanged();
    }
}

float Sizing::dp(float value) {
    qWarning("Dont use size.dp(value)! Use value*size.dpScaleFactor");
    return value*m_dpScaleFactor;
}

float Sizing::mm(float value) {
    qWarning("Dont use size.mm(value)! Use value*size.mmScaleFactor");
    return value*m_mmScaleFactor;
}
