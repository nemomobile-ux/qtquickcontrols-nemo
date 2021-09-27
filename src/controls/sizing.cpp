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
    , m_valid(false)
    , m_mm_factor(10)
    , m_dp_factor(1.5)
    , m_densitie(mdpi)
{
    qreal refHeight =  1440; //HD
    qreal refWidth = 720; //HD

    m_p_height = qEnvironmentVariableIntValue("QT_QPA_EGLFS_PHYSICAL_HEIGHT");
    m_p_width = qEnvironmentVariableIntValue("QT_QPA_EGLFS_PHYSICAL_WIDTH");
    m_dpi = qEnvironmentVariableIntValue("QT_WAYLAND_FORCE_DPI");

    QScreen *screen = QGuiApplication::primaryScreen();

    /*If we dont have everoment of physical size try get it from screen*/
    if (m_p_height == 0 || m_p_width == 0) {
        qWarning("QT_QPA_EGLFS_PHYSICAL_WIDTH or QT_QPA_EGLFS_PHYSICAL_HEIGHT is not set! \n"
                 "Trying to use QScreenSize");

        m_p_height = screen->physicalSize().height();
        m_p_width = screen->physicalSize().width();
        qInfo() << "Set size to " <<  m_p_height  <<  " x " << m_p_width;
    }

    m_height = qMax(screen->size().width(), screen->size().height());
    m_width = qMin(screen->size().width(), screen->size().height());

    if (m_dpi == 0) {
        m_dpi = screen->physicalDotsPerInch();
    } else {
        qInfo() << "Use QPI from QT_WAYLAND_FORCE_DPI enveroment = " << m_dpi;
    }

    m_scaleRatio = qMin(m_height/refHeight, m_width/refWidth);
    m_fontRatio = floor(m_scaleRatio*10)/10;

    if (m_dpi < 140) {
        m_densitie = ldpi;
        m_dp_factor = 0.5;
    } else if (m_dpi >= 140 && m_dpi < 200) {
        //~160dpi
        m_densitie = mdpi;
        m_dp_factor = 0.6;
    } else if (m_dpi >= 200 && m_dpi < 300) {
        //~240dpi
        m_densitie = hdpi;
        m_dp_factor = 1;
    } else if(m_dpi >= 300 && m_dpi < 420) {
        //~320dpi
        m_densitie = xhdpi;
        m_dp_factor = 1.5;
    } else if(m_dpi >= 420 && m_dpi < 560) {
        //~480dpi
        m_densitie = xxhdpi;
        m_dp_factor = 2;
    } else {
        m_densitie = xxxhdpi;
        m_dp_factor = 2.5;
    }

    if (m_p_height > 0 && m_p_width > 0) {
        m_valid = true;
        m_mm_factor = m_width/m_p_width;
    } else {
        if (m_p_height == 0) {
            qWarning("QT_QPA_EGLFS_PHYSICAL_HEIGHT is not set!");
        }

        if (m_p_width == 0) {
            qWarning("QT_QPA_EGLFS_PHYSICAL_WIDTH is not set!");
        }
        qWarning("Device mm sizing don`t work");
    }

    qDebug() << "Height: " << m_height << "Width: " << m_width;
    qDebug() << "Scale ratio: " << m_scaleRatio << " Font: " << m_fontRatio;
    qDebug() << "DPI is " << m_dpi;
    qDebug() << "DP scale factor is " << m_dp_factor;
    qDebug() << "MM scale factor is " << m_mm_factor;
}

void Sizing::setDpScaleFactor(float value)
{
    if(value != m_dp_factor && value != 0) {
        m_dp_factor = value;
        emit dpScaleFactorChanged();
    }
}

void Sizing::setMmScaleFactor(float value)
{
    if(value != m_mm_factor && value != 0) {
        m_mm_factor = value;
        emit mmScaleFactorChanged();
    }
}


void Sizing::setScaleRatio(qreal scaleRatio)
{
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

void Sizing::setFontRatio(qreal fontRatio)
{
    if(m_fontRatio != fontRatio && fontRatio !=0 ) {
        m_fontRatio = fontRatio;
        emit fontRatioChanged();
    }
}

float Sizing::dp(float value)
{
    qWarning("Dont use size.dp(value)! Use value*size.dpScaleFactor");
    return value*m_dp_factor;
}

float Sizing::mm(float value)
{
    qWarning("Dont use size.mm(value)! Use value*size.mmScaleFactor");
    return value*m_mm_factor;
}
