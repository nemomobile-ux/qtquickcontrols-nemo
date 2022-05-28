/*
 * Copyright (C) 2013 Andrea Bernabei <and.bernabei@gmail.com>
 * Copyright (C) 2021-2022 Chupligin Sergey <neochapay@gmail.com>
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

#include "nemowindow.h"
#include "nemopage.h"
#include <QDebug>

NemoWindow::NemoWindow(QWindow *parent) :
    QQuickWindow(parent),
    m_defaultAllowedOrientations(Qt::PortraitOrientation | Qt::LandscapeOrientation)
    , m_sensorOrientation(Qt::PrimaryOrientation)
{
    m_allowedOrientations = m_defaultAllowedOrientations;
    m_filter = new EditFilter();
    m_orientationSensor = new QOrientationSensor(this);

    this->installEventFilter(m_filter);

    connect(m_orientationSensor, &QOrientationSensor::readingChanged, this, &NemoWindow::setScreenOrientationFromSensor);

    if (!m_orientationSensor->connectToBackend()) {
        qWarning() << "Could not connect to the orientation sensor backend";
    } else {
        if (!m_orientationSensor->start()) {
            qWarning() << "Could not start the orientation sensor";
        }
    }
}

Qt::ScreenOrientations NemoWindow::allowedOrientations() const
{
    return m_allowedOrientations;
}

const Qt::ScreenOrientations NemoWindow::defaultAllowedOrientations() const
{
    return m_defaultAllowedOrientations;
}

void NemoWindow::setAllowedOrientations(Qt::ScreenOrientations allowed)
{
    //This way no invalid values can get assigned to allowedOrientations
    if (m_allowedOrientations != allowed) {
        if (NemoPage::isOrientationMaskValid(allowed)) {
            m_allowedOrientations = allowed;
            emit allowedOrientationsChanged();
        } else {
            qWarning() << "NemoWindow: invalid allowedOrientation!";
        }
    }
}

void NemoWindow::setScreenOrientationFromSensor()
{
    QOrientationReading* reading = m_orientationSensor->reading();

    Qt::ScreenOrientations sensorOrientation = m_sensorOrientation;
    switch (reading->orientation()) {
    case QOrientationReading::TopUp:
        sensorOrientation = Qt::PortraitOrientation;
        break;
    case QOrientationReading::TopDown:
        sensorOrientation = Qt::InvertedPortraitOrientation;
        break;
    case QOrientationReading::LeftUp:
        sensorOrientation = Qt::InvertedLandscapeOrientation;
        break;
    case QOrientationReading::RightUp:
        sensorOrientation = Qt::LandscapeOrientation;
        break;
    case QOrientationReading::FaceUp:
    case QOrientationReading::FaceDown:
        /* Keep screen orientation at previous state */
        break;
    case QOrientationReading::Undefined:
    default:
        sensorOrientation = Qt::PrimaryOrientation;
        break;
    }

    if (sensorOrientation != m_sensorOrientation) {
        m_sensorOrientation = sensorOrientation;
        emit sensorOrientationChanged();
    }
}
