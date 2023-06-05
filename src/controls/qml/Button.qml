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
        anchors.fill: control
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

        Shape{
            id: radialShape
            anchors.fill: parent
            visible: control.pressed

            ShapePath {
                strokeWidth: 0
                strokeColor: "transparent"
                // The effect which shows the pressed state
                fillGradient: RadialGradient {
                    centerX: control.pressX
                    centerY: control.pressY

                    centerRadius: Math.min(radialShape.width, radialShape.height)
                    focalX: centerX; focalY: centerY

                    GradientStop {
                        position: 0
                        color: control.primary ? Theme.backgroundAccentColor
                                               : Theme.accentColor
                    }
                    GradientStop {
                        position: 1;
                        color: control.primary ? Theme.accentColor
                                               : "transparent"
                    }
                }
                fillColor: Theme.accentColor
                strokeStyle: ShapePath.SolidLine
                dashPattern: [ 1, 4 ]
                startX: 0
                startY: 0
                PathLine {
                    x: radialShape.width
                    y: 0
                }
                PathLine {
                    x: radialShape.width
                    y: radialShape.height
                }
                PathLine {
                    x: 0
                    y: radialShape.height
                }
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
