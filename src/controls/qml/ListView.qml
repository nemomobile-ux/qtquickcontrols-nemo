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

import QtQuick 2.6
import QtQuick.Controls

ListView {
    id: listView

    signal hideAllActions(int hideIndex)
    property color delegateColor: "transparent"
    property color bottomGradientColor: Theme.backgroundColor

    section.criteria: ViewSection.FullString
    section.delegate: Component{
        id: sectionHeading
        Rectangle {
            width: listView.width
            height: Theme.itemHeightMedium
            color: delegateColor

            Text {
                id: sectionText
                text: section
                FontLoader {
                    id: localFont
                    source: Theme.fontPath
                }
                font.family: localFont.font.family
                font.styleName: localFont.font.styleName
                font.capitalization: Font.AllUppercase
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.textColor
                anchors{
                    left: parent.left
                    leftMargin: Theme.itemSpacingSmall
                    verticalCenter: parent.verticalCenter
                }
            }

            Rectangle{
                id: line
                height: size.dp(1)
                color: Theme.textColor
                width: listView.width-sectionText.width-Theme.itemHeightExtraSmall
                anchors{
                    left: sectionText.right
                    leftMargin: Theme.itemSpacingSmall
                    verticalCenter: sectionText.verticalCenter
                }
            }
        }
    }

    Item{
        id: bottom
        width: parent.width
        height: Theme.itemHeightExtraSmall
        anchors.bottom: parent.bottom

        visible: listView.contentHeight > listView.height
    }
}

