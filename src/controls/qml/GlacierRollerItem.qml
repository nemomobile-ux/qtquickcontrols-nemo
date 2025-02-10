/*
 * Copyright (C) 2018-2023 Chupligin Sergey <neochapay@gmail.com>
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
        source: "images/glacierroller-icon-arrow-down.svg"
        height: parent.height / 3
        sourceSize.width: width
        sourceSize.height: height

        visible: glacierRollerItem.parent.showRow
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

    MouseArea{
        anchors.fill: parent
        onClicked: {
            if(!glacierRollerItem.parent.parent.activated)
            {
                glacierRollerItem.parent.parent.activated = true;
            }
            else
            {
                glacierRollerItem.parent.parent.currentIndex = index
                glacierRollerItem.parent.parent.activated = false
            }
        }
    }
}
