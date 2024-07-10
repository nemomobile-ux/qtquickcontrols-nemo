/*
 * Copyright (C) 2013 Andrea Bernabei <and.bernabei@gmail.com>
 * Copyright (C) 2018-2022 Chupligin Sergey (NeoChapay) <neochapay@gmail.com>
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

#include "nemopage.h"
#include "logging.h"

NemoPage::NemoPage(QQuickItem* parent)
    : QQuickItem(parent)
    , m_allowedOrientations(Qt::PrimaryOrientation) //- The value 0 means Page's allowedOrientations will be ignored
//- The value 0 can't be set from QML on purpose (see Hacks::isOrientationMaskValid impl.),
//  so that we can use the value 0 to know that the app developer has not touched this value
//  (in fact, as just said, once it's changed from QML, the app dev can't set it back to 0 from QML)
{
}

Qt::ScreenOrientations NemoPage::allowedOrientations() const
{
    return m_allowedOrientations;
}

void NemoPage::setAllowedOrientations(Qt::ScreenOrientations allowed)
{
    // This way no invalid values can get assigned to allowedOrientations
    if (m_allowedOrientations != allowed) {
        if (isOrientationMaskValid(allowed)) {
            m_allowedOrientations = allowed;
            emit allowedOrientationsChanged();
        } else {
            qCDebug(lcNemoControlsControlsLog) << "NemoPage: invalid allowedOrientation!";
        }
    }
}

bool NemoPage::isOrientationMaskValid(Qt::ScreenOrientations orientations)
{
    // README: This is needed because otherwise you could assign it
    // things like (Qt.PortraitOrientation | 444) from QML,
    // and it would still appear as a valid Qt::ScreenOrientations in c++
    Qt::ScreenOrientations max = (Qt::PortraitOrientation | Qt::LandscapeOrientation
        | Qt::InvertedPortraitOrientation | Qt::InvertedLandscapeOrientation);

    return (orientations <= max && orientations > 0);
}
