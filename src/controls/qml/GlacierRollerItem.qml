/*
 * Copyright (C) 2018-2025 Chupligin Sergey <neochapay@gmail.com>
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

Rectangle{
    id: glacierRollerItem
    color: "transparent"
    width: parent.width
    height: parent.itemHeight

    property alias cWidth: dataLine.width

    default property alias contentItem: dataLine.children
    Rectangle{
        id: dataLine
        width: childrenRect.width
        height: parent.height
        color: "transparent"
        anchors.verticalCenter: glacierRollerItem.verticalCenter
    }

    Image{
        id: arrowDown
        source: "qrc:///images/glacierroller-icon-arrow-down.svg"
        height: parent.height / 3
        sourceSize.width: width
        sourceSize.height: height

        visible: glacierRollerItem.parent.showRow == undefined ? false : glacierRollerItem.parent.showRow
        fillMode: Image.PreserveAspectFit
        anchors{
            verticalCenter: glacierRollerItem.verticalCenter
            left: dataLine.right
            leftMargin: width
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                glacierRollerItem.parent.parent.activated = true
            }
        }
    }

    TapHandler {
        onTapped: {
            var roller = glacierRollerItem.parent.parent
            var tappedIndex = index
            if(!roller.activated)
            {
                roller.activated = true;
            }
            else
            {
                roller.currentIndex = tappedIndex
                roller.activated = false
            }
        }
    }
}
