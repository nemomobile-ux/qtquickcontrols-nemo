/****************************************************************************************
**
** Copyright (C) 2023 Chupligin Sergey <neochapay@gmail.com>
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

ProgressBar {
    id: control

    background: Rectangle {
        implicitHeight: Theme.itemHeightSmall/2
        implicitWidth: Theme.itemWidthLarge + Theme.itemWidthSmall
        color: Theme.fillDarkColor
        radius: 1
    }

    contentItem: Rectangle {
        implicitHeight: Theme.itemHeightSmall/2
        implicitWidth: Theme.itemWidthLarge + Theme.itemWidthSmall

        width: control.visualPosition * parent.width
        height: parent.height

        color: Theme.accentColor

        Item {
            anchors.fill: parent
            anchors.margins: 1
            visible: control.indeterminate
            clip: true

            Row {
                Repeater {
                    Rectangle {
                        color: index % 2 ? Theme.fillDarkColor : Theme.accentColor
                        width: Theme.itemHeightExtraSmall/3
                        height: control.height*2
                        rotation: 40
                        y: -control.height/2
                    }
                    model: control.width/Theme.itemHeightExtraSmall*3+4
                }
                XAnimator on x {
                    from: -(Theme.itemHeightExtraSmall/3*2) ; to: 0
                    loops: Animation.Infinite
                    running: control.indeterminate
                }
            }
        }
    }
}
