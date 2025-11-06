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

import QtQuick 2.6
import QtQuick.Shapes 1.5

import Nemo
import Nemo.Controls

Item {
    id: toolsLayoutItem

    anchors.fill: parent

    property alias title: titleTxt.text
    //these have to be initialized when the HeaderToolsLayout is instantiated
    property Header header
    property list<Item> tools
    //we'll get rid of this once we'll have the appWindow accessible everywhere
    property bool isUiPortrait: header && header.appWindow.isUiPortrait

    property bool showBackButton: false
    property int toolMeasure: Theme.itemHeightSmall
    height: toolMeasure
    Item {
        id: backButton
        width: opacity ? backButton.height : 0
        height: toolsLayoutItem.height

        anchors{
            leftMargin: Theme.itemSpacingLarge
            //check if Stack.view has already been initialized as well
            verticalCenter: parent.verticalCenter
        }

        rotation: isUiPortrait ? 0 : 90
        visible: showBackButton && applicationWindow.pageStack.depth > 1

        Image {
            anchors.centerIn: parent
            height: toolMeasure
            width: height
            fillMode: Image.PreserveAspectFit
            sourceSize.width: width
            sourceSize.height: height
            source: "image://theme/chevron-left?" + Theme.textColor
        }

        MouseArea {
            id: backmouse
            anchors.fill: parent
            anchors.margins: -Theme.itemSpacingSmall
            onClicked: header && header.stackView && header.stackView.pop()
        }
    }

    Label {
        id: titleTxt
        FontLoader {
            id: localFont
            source: "file://"+Theme.fontPath
        }
        anchors{
            right: toolButtonsContainer.left
            left: backButton.visible ? backButton.right : parent.left
            verticalCenter: parent.verticalCenter
            leftMargin: backButton.visible ? 0 : Theme.itemSpacingLarge
        }
        clip: true
        font.pixelSize: Theme.fontSizeLarge
        font.weight: Font.Bold
    }


    Item {
        id: toolButtonsContainer
        anchors{
            right: parent.right
            verticalCenter: parent.verticalCenter
        }

        width: tools ? (toolsLayoutItem.height * Math.min(maxNumberOfToolButtons, tools.length)) : 0
        height: toolsLayoutItem.height

        property int maxNumberOfToolButtons: 3

        Row {
            id: toolsRow
            anchors.centerIn: parent
            height: toolButtonsContainer.height
            children: tools
        }
    }
}
