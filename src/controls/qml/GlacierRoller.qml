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
import Nemo

Item {
    id: glacierRoller
    property alias model : view.model
    property alias label: label.text
    property alias delegate: view.delegate
    property int currentIndex: -1
    property int activateSize: 5
    property alias itemHeight: view.itemHeight
    property int labelLeftMargin: 0;
    property int viewLeftMargin: 0

    property bool activated: false

    signal clicked();
    signal select(int currentItem);

    width: parent.width
    height: childrenRect.height

    Label{
        id: label
        visible: label.text != ""
        font.pixelSize: Theme.fontSizeSmall
        color: Theme.textColor
        width: parent.width - anchors.leftMargin
        anchors{
            top: parent.top
            left: parent.left
            leftMargin: glacierRoller.labelLeftMargin
        }
    }

    Rectangle{
        id: topLine
        width: parent.width
        height: Theme.dp(1)
        color: Theme.backgroundAccentColor
        anchors.top: view.top
        z: 2
    }

    Rectangle{
        id: bottomLine
        width: parent.width
        height: Theme.dp(3)
        color: Theme.backgroundAccentColor
        anchors.bottom: view.bottom
        z: 2
    }

    PathView{
        id: view
        property int itemHeight: Theme.itemHeightLarge
        property bool showRow: false

        interactive: activated
        width: parent.width-Theme.itemWidthSmall
        height: Theme.itemHeightMedium
        clip: true

        anchors{
            top: label.bottom
            topMargin:Theme.itemSpacingLarge
            left: label.left
            leftMargin: glacierRoller.viewLeftMargin
        }

        pathItemCount: height/itemHeight
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        dragMargin: view.width

        path: Path {
            startX: view.width/2; startY: 0
            PathLine { x: view.width/2; y: view.pathItemCount*itemHeight }
        }

        snapMode: PathView.SnapToItem
    }

    InverseMouseArea {
        width: parent.width
        height: view.height
        anchors.centerIn: view
        enabled: activated
        parent:glacierRoller
        onPressed: {
            if(activated) activated = false
        }
    }

    Component.onCompleted: {
        if(activated)
        {
            view.showRow = false
            bottomLine.opacity = 1
            topLine.opacity = 1
            view.height = itemHeight*activateSize
        }
        else
        {
            view.showRow = true
            bottomLine.opacity = 0
            topLine.opacity = 0
            view.height = itemHeight
        }
    }

    onCurrentIndexChanged: {
        view.currentIndex = currentIndex
    }

    onActivatedChanged: {
        if(activated)
        {
            view.showRow = false
            activateAnimations.start()
        }
        else
        {
            deActivateAnimations.start()
            view.positionViewAtIndex(currentIndex,ListView.SnapPosition)
        }
    }

    ParallelAnimation {
        id: activateAnimations
        NumberAnimation{target: bottomLine; property: "opacity"; to: 1; duration: 150}
        NumberAnimation{target: topLine; property: "opacity"; to: 1; duration: 150}
        NumberAnimation{target: view; property: "height"; to: itemHeight*activateSize; duration: 150; easing.type: Easing.InCubic}
    }

    ParallelAnimation {
        id: deActivateAnimations
        NumberAnimation{target: bottomLine; property: "opacity"; to: 0; duration: 150}
        NumberAnimation{target: topLine; property: "opacity"; to: 0; duration: 150}
        NumberAnimation{target: view; property: "height"; to: itemHeight; duration: 150; easing.type: Easing.OutCubic}
        onStopped: {
            view.showRow = true
        }
    }
}
