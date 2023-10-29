/****************************************************************************************
**
** Copyright (c) 2017, Eetu Kahelin
** Copyright (C) 2021-2023 Chupligin Sergey <neochapay@gmail.com>
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
    font.family: localFont.font.family
    font.styleName: localFont.font.styleName
    placeholderTextColor: Theme.fillColor

    FontLoader {
        id: localFont
        source: Theme.fontPath
    }

    onActiveFocusChanged: {
        if(activeFocus) {
            NemoFocus.nemoregister(this)
        } else {
            NemoFocus.nemoregister(null)
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
            source: "images/disabled-overlay-inverse.png"
            fillMode: Image.Tile
        }
        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: size.dp(2)
            width: parent.width
            color: control.readOnly ? Theme.fillDarkColor : Theme.accentColor
        }
    }
}
