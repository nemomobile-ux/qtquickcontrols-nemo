/*
 * Copyright (C) 2021-2023 Chupligin Sergey <neochapay@gmail.com>
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

import QtQuick
import QtQuick.Controls

import Nemo

Slider {
    id: control
    property bool showValue: false
    property int valueFontSize: Theme.fontSizeTiny
    property bool useSpecSlider: Theme.desktopMode ? false : true
    property bool alwaysUp: false
    height: Theme.itemHeightExtraSmall * 1.2

    background: Rectangle {
        x: control.leftPadding
        implicitWidth: Theme.itemWidthLarge + Theme.itemWidthSmall - Theme.itemHeightExtraSmall*0.4
        implicitHeight: Theme.itemHeightExtraSmall / 2
        width: control.availableWidth
        height: implicitHeight
        color: Theme.fillDarkColor
        clip: true
        anchors{
            verticalCenter: control.verticalCenter
        }

        Rectangle {
            width: control.visualPosition * parent.width
            height: parent.height
            color: Theme.accentColor
        }

        Image {
            id: disabledImg
            anchors.fill: parent
            visible: !control.enabled
            source: "images/disabled-overlay.png"
            fillMode: Image.Tile
        }
    }

    handle: Rectangle {
        x: control.leftPadding + control.visualPosition * (control.availableWidth - width) + Theme.itemHeightExtraSmall*0.2
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: Theme.itemHeightExtraSmall
        implicitHeight: Theme.itemHeightExtraSmall
        radius: implicitHeight / 2
        color: Theme.backgroundColor
        border.color: Theme.textColor
        border.width: Theme.itemSpacingExtraSmall/4

        scale: control.pressed ? 1.2 : 1

        Text{
            id: valueLabel
            anchors.centerIn: parent
            text: parseInt(control.value)
            visible: control.showValue
            color: Theme.textColor
            font.pixelSize: control.valueFontSize
        }
    }
}
