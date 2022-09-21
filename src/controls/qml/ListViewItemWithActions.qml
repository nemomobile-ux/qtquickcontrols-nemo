/****************************************************************************************
**
** Copyright (C) 2017-2022 Chupligin Sergey <neochapay@gmail.com>
** All rights reserved.
**
** You may use this file under the terms of BSD license as follows:
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the author nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
** ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************************/

import QtQuick 2.15
import QtQuick.Controls.Nemo 1.0

import QtGraphicalEffects 1.0

Item {
    id: root
    width: parent ? parent.width : 0
    height: Theme.itemHeightLarge

    property string label: ""

    property string description: ""
    property string subdescription: ""
    property string icon: ""
    property Component iconDelegate: NemoIcon{
            id: itemIcon
            width: parent.width
            height: parent.height

            colorized: iconColorized
            sourceSize.width: width
            sourceSize.height: height
            source: (icon != "") ? icon : iconVisible ? "images/listview-icon-template-s.svg" : ""
            fillMode: Image.PreserveAspectFit
        }


    property bool showNext: true
    property bool iconVisible: true
    property bool iconColorized: true
    property bool selected: false

    property bool showActions: true

    property list<Item> actions

    signal clicked

    function hideAllActions() {
        if(actions && root.ListView.view) {
            root.ListView.view.hideAllActions(index)
        }
    }

    Connections {
        target: root.ListView.view
        function onHideAllActions(hideIndex) {
            if (hideIndex != index) {
                listArea.x = 0
            }
        }
    }

    // The effect which shows the pressed state
    Rectangle{
        id: background
        anchors.fill: parent
        color: "transparent"
        clip: true

        RadialGradient {
            x: mouse.mouseX - width/2 + listArea.x
            y: mouse.mouseY - height/2
            width: visible ? Theme.itemWidthSmall : 0
            height: visible ? Theme.itemWidthSmall : 0
            visible: mouse.pressed

            gradient: Gradient {
                GradientStop {
                    position: 0.29
                    color: Theme.accentColor
                }
                GradientStop {
                    position: 0.5;
                    color: "transparent"
                }
            }

            Behavior on width {
                NumberAnimation { duration: 200 }
            }

            Behavior on height {
                NumberAnimation { duration: 200 }
            }
        }
    }

    Rectangle{
        id: actionsArea
        color: Theme.fillColor

        anchors.right: listArea.left

        height: listArea.height
        width: actionsRow.childrenRect.width

        Row {
            id: actionsRow
            width: actionsArea.width
            height: actionsArea.height

            children: actions
        }

        Component.onCompleted: {
            if(actions.length > 3) {
                console.warn("Use more 3 actions is not good idea!")
            }
        }
    }

    Rectangle{
        id: listArea
        width: root.width
        height: root.height
        color: selected ? Theme.accentColor :"transparent"

        Behavior on x{
            NumberAnimation { duration: 200}
        }

        Rectangle{
            id: actionIndicator
            height: parent.height
            width: Theme.itemSpacingSmall/4-Theme.itemSpacingSmall/4*listArea.x/actionsArea.width
            color: Theme.accentColor
            visible: (height*actions.length > 0 && showActions)
        }

        Rectangle {
            anchors.fill: parent
            color: "#11ffffff"
            visible: mouse.pressed
        }

        Loader{
            id: iconLoader
            height: iconVisible ? parent.height-Theme.itemSpacingMedium : 0
            width: height
            anchors{
                left: parent.left
                leftMargin: Theme.itemSpacingLarge
                verticalCenter:parent.verticalCenter
            }
            visible: iconVisible
            sourceComponent: iconDelegate

        }

        Rectangle{
            id: dataArea
            width: parent.width-iconLoader.width-Theme.itemHeightLarge - (showNext ? arrowItem.width : 0)
            height: labelItem.height+(description != "" ? descriptionItem.height : 0)+(subdescription != "" ? subDescriptionItem.height : 0)
            clip: true

            anchors{
                left: iconVisible ? iconLoader.right : parent.left
                leftMargin: Theme.itemSpacingLarge
                verticalCenter: iconVisible ? iconLoader.verticalCenter : parent.verticalCenter
            }
            color: "transparent"

            Label {
                id: labelItem
                color: Theme.textColor
                text: label
                anchors{
                    left: parent.left
                    right: parent.right
                }
                font.pixelSize: Theme.fontSizeMedium
                clip: true
            }

            Label {
                id: descriptionItem
                color: Theme.textColor
                text: description
                anchors{
                    left: parent.left
                    right: parent.right
                    top: labelItem.bottom
                }
                font.pixelSize: Theme.fontSizeTiny
                clip: true
                visible: description != ""
            }

            Label {
                id: subDescriptionItem
                color: Theme.textColor
                text: subdescription
                anchors{
                    left: parent.left
                    right: parent.right
                    top: descriptionItem.bottom
                }
                font.pixelSize: Theme.fontSizeTiny
                clip: true
                visible: subdescription != ""
            }

            Item{
                width: Theme.itemHeightExtraSmall / 2
                height: parent.height
                anchors{
                    top: parent.top
                    right: parent.right
                }
                visible: showNext ? !mouse.pressed : false
            }
        }

        NemoIcon {
            id: arrowItem
            height: parent.height- Theme.itemSpacingMedium
            width: height

            anchors{
                right: parent.right
                rightMargin: Theme.itemSpacingLarge
                verticalCenter: parent.verticalCenter
            }

            sourceSize.width: width
            sourceSize.height: height

            source: "images/listview-icon-arrow.svg"
            visible: showNext
        }

        MouseArea {
            id: mouse
            anchors.fill: parent
            onClicked: {
                //if actions is hide
                if(listArea.x === 0) {
                    root.clicked()
                } else {
                    listArea.x = 0
                }
            }

            onPressed: {
                hideAllActions()
            }

            onPressAndHold: {
                if (actions.length > 0 && showActions) {
                    listArea.x = actionsArea.width
                }
            }
        }
    }
}
