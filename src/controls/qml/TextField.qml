/****************************************************************************************
**
** Copyright (c) 2017, Eetu Kahelin
** Copyright (C) 2021-2025 Chupligin Sergey <neochapay@gmail.com>
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

import QtQuick
import QtQuick.Controls

import Nemo

TextField {
    id: control
    color: Theme.textColor
    selectedTextColor: Theme.textColor
    selectionColor: Theme.accentColor
    font.pixelSize: Theme.fontSizeMedium
    font.family: Theme.fontFamily
    font.styleName: Theme.fontStyleName
    placeholderTextColor: Theme.fillColor
    selectByMouse: true
    persistentSelection: true

    onActiveFocusChanged: {
        if(activeFocus) {
            NemoFocus.nemoregister(control)
        } else if (NemoFocus.edit === control) {
            NemoFocus.nemoregister(null)
        }
    }

    TapHandler {
        id: editMenuHandler
        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchScreen
        acceptedButtons: Qt.RightButton | Qt.LeftButton
        onLongPressed: {
            control.forceActiveFocus()
            var pos = control.positionAt(editMenuHandler.point.position.x, editMenuHandler.point.position.y)
            var atSelection = control.selectedText.length > 0
                && pos >= control.selectionStart
                && pos <= control.selectionEnd
            if (!atSelection) {
                control.cursorPosition = pos
                control.selectWord()
            }
            if (control.selectedText.length === 0 && control.text.length > 0)
                control.selectAll()
        }
        onTapped: function(eventPoint, button) {
            if (button === Qt.RightButton) {
                control.forceActiveFocus()
                editMenu.popup()
                return
            }

            if (button === Qt.LeftButton && control.selectedText.length > 0) {
                var pos = control.positionAt(eventPoint.position.x, eventPoint.position.y)
                if (pos >= control.selectionStart && pos <= control.selectionEnd) {
                    var selStart = control.selectionStart
                    var selEnd = control.selectionEnd
                    editMenu.popup()
                    Qt.callLater(function() { control.select(selStart, selEnd) })
                }
            }
        }
    }

    Menu {
        id: editMenu
        modal: false
        dim: false
        closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape
        topPadding: Theme.itemSpacingExtraSmall
        bottomPadding: Theme.itemSpacingExtraSmall

        background: Rectangle {
            implicitWidth: Theme.itemWidthMedium
            color: Theme.backgroundColor
            border.color: Theme.fillDarkColor
            border.width: 1
            radius: Theme.dp(4)
        }

        delegate: MenuItem {
            id: menuItem
            visible: enabled
            implicitWidth: Theme.itemWidthMedium
            implicitHeight: enabled ? Theme.itemHeightSmall : 0
            height: implicitHeight
            leftPadding: Theme.itemSpacingMedium
            rightPadding: Theme.itemSpacingMedium

            contentItem: Text {
                text: menuItem.text
                font.pixelSize: Theme.fontSizeMedium
                font.family: Theme.fontFamily
                color: menuItem.enabled ? Theme.textColor : Theme.fillColor
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                color: menuItem.highlighted ? Theme.fillDarkColor : "transparent"
            }
        }

        Action {
            text: qsTr("Cut")
            enabled: control.selectedText.length > 0 && !control.readOnly
            onTriggered: control.cut()
        }
        Action {
            text: qsTr("Copy")
            enabled: control.selectedText.length > 0
            onTriggered: control.copy()
        }
        Action {
            text: qsTr("Paste")
            enabled: control.canPaste && !control.readOnly
            onTriggered: control.paste()
        }
        Action {
            text: qsTr("Select all")
            enabled: control.text.length > 0
            onTriggered: control.selectAll()
        }
    }

    Rectangle {
        id: selectionStartHandle
        visible: control.activeFocus && control.selectedText.length > 0
        width: Theme.itemSpacingSmall
        height: Theme.itemSpacingSmall
        radius: width / 2
        color: Theme.accentColor
        z: 10
        x: control.positionToRectangle(control.selectionStart).x - width / 3
        y: control.positionToRectangle(control.selectionStart).y + control.positionToRectangle(control.selectionStart).height

        MouseArea {
            anchors.fill: parent
            anchors.margins: -Theme.itemSpacingSmall
            preventStealing: true
            onPressed: function(mouse) { mouse.accepted = true; control.forceActiveFocus() }
            onPositionChanged: function(mouse) {
                var p = selectionStartHandle.mapToItem(control, mouse.x, mouse.y)
                var textY = control.positionToRectangle(control.selectionStart).y
                    + control.positionToRectangle(control.selectionStart).height / 2
                var pos = Math.max(0, Math.min(control.positionAt(p.x, textY), control.selectionEnd - 1))
                if (pos !== control.selectionStart)
                    control.select(pos, control.selectionEnd)
            }
        }
    }

    Rectangle {
        id: selectionEndHandle
        visible: control.activeFocus && control.selectedText.length > 0
        width: Theme.itemSpacingSmall
        height: Theme.itemSpacingSmall
        radius: width / 2
        color: Theme.accentColor
        z: 10
        x: control.positionToRectangle(control.selectionEnd).x
        y: control.positionToRectangle(control.selectionEnd).y + control.positionToRectangle(control.selectionEnd).height

        MouseArea {
            anchors.fill: parent
            anchors.margins: -Theme.itemSpacingSmall
            preventStealing: true
            onPressed: function(mouse) { mouse.accepted = true; control.forceActiveFocus() }
            onPositionChanged: function(mouse) {
                var p = selectionEndHandle.mapToItem(control, mouse.x, mouse.y)
                var textY = control.positionToRectangle(control.selectionEnd).y
                    + control.positionToRectangle(control.selectionEnd).height / 2
                var pos = Math.max(control.selectionStart + 1, Math.min(control.positionAt(p.x, textY), control.text.length))
                if (pos !== control.selectionEnd)
                    control.select(control.selectionStart, pos)
            }
        }
    }

    background: Item {
        anchors{
            leftMargin: Theme.itemSpacingMedium
            rightMargin: Theme.itemSpacingMedium
        }

        implicitHeight: Theme.itemHeightSmall
        implicitWidth: Theme.itemWidthLarge
        opacity: control.enabled ? 1 : 0.6
        Image {
            anchors.fill: parent
            visible: !control.enabled
            source: "qrc:///images/disabled-overlay-inverse.png"
            fillMode: Image.Tile
        }
        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: Theme.dp(2)
            width: parent.width
            color: control.readOnly ? Theme.fillDarkColor : Theme.accentColor
        }
    }
}
