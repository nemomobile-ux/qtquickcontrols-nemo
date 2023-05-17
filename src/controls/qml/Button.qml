/*
 * Copyright (C) 2013 Andrea Bernabei <and.bernabei@gmail.com>
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

import QtQuick 2.6
import QtQuick.Controls

import QtQuick.Shapes 1.5

import Nemo

Button {
    id: control

    // A primary button is the main button of a view, and it is styled accordingly.
    property bool primary: false

    background: Rectangle {
        implicitWidth: Theme.itemWidthMedium
        implicitHeight: Theme.itemHeightMedium
        clip: true
        color: control.primary ? Theme.accentColor
                               : Theme.fillColor
        Image {
            id: disabledImg
            anchors.fill: parent
            visible: !control.enabled
            source: "images/disabled-overlay.png"
            fillMode: Image.Tile
        }

        // The effect which shows the pressed state
        RadialGradient {
            focalX: control.pressX - width/2
            focalY: control.pressY - height/2

            GradientStop {
                position: 0.29
                color: control.primary ? Theme.backgroundAccentColor
                                       : Theme.accentColor
            }
            GradientStop {
                position: 0.5;
                color: control.primary ? Theme.accentColor
                                       : "transparent"
            }
        }
    }

    // The label of the button.
    contentItem: Text {
        renderType: Text.NativeRendering
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: control.text
        color: Theme.textColor
        font.family: Theme.fontFamily
        font.pixelSize: Theme.fontSizeMedium
        font.weight: control.primary ? Theme.fontWeightLarge : Theme.fontWeightMedium
        opacity: control.enabled ? 1.0 : 0.3
    }
}


