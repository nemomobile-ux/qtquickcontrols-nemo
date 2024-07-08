/*
 * Copyright (C) 2017-2024 Chupligin Sergey <neochapay@gmail.com>
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
import QtQuick.Window
import Nemo.Controls

ApplicationWindow {
    id: appWindow

    initialPage: Page {
        id: root

        headerTools: HeaderToolsLayout {
            id: tools
            title: qsTr("Size view application")
        }

        Component.onCompleted: {
            console.log("Theme.itemWidthLarge: "+Theme.itemWidthLarge)
            console.log("Theme.itemWidthMedium: "+Theme.itemWidthMedium)
            console.log("Theme.itemWidthSmall: "+Theme.itemWidthSmall)
            console.log("Theme.itemWidthExtraSmall: "+Theme.itemWidthExtraSmall)

            console.log("Theme.itemHeightHuge: "+Theme.itemHeightHuge)
            console.log("Theme.itemHeightExtraLarge: "+Theme.itemHeightExtraLarge)
            console.log("Theme.itemHeightLarge: "+Theme.itemHeightLarge)
            console.log("Theme.itemHeightMedium: "+Theme.itemHeightMedium)
            console.log("Theme.itemHeightSmall: "+Theme.itemHeightSmall)
            console.log("Theme.itemHeightExtraSmall: "+Theme.itemHeightExtraSmall)

            console.log("Theme.itemSpacingHuge: "+Theme.itemSpacingHuge)
            console.log("Theme.itemSpacingLarge: "+Theme.itemSpacingLarge)
            console.log("Theme.itemSpacingMedium: "+Theme.itemSpacingMedium)
            console.log("Theme.itemSpacingSmall: "+Theme.itemSpacingSmall)
            console.log("Theme.itemSpacingExtraSmall: "+Theme.itemSpacingExtraSmall)

            console.log("Theme.fontSizeExtraLarge: "+Theme.fontSizeExtraLarge)
            console.log("Theme.fontSizeLarge: "+Theme.fontSizeLarge)
            console.log("Theme.fontSizeMedium: "+Theme.fontSizeMedium)
            console.log("Theme.fontSizeSmall: "+Theme.fontSizeSmall)
            console.log("Theme.fontSizeTiny: "+Theme.fontSizeTiny)

            console.log("Theme.fontWeightLarge: "+Theme.fontWeightLarge)
            console.log("Theme.fontWeightMedium: "+Theme.fontWeightMedium)

            console.log("Theme.fontFamily: "+Theme.fontFamily)

            console.log("Theme.accentColor: "+Theme.accentColor)
            console.log("Theme.fillColor: "+Theme.fillColor)
            console.log("Theme.fillDarkColor: "+Theme.fillDarkColor)
            console.log("Theme.textColor: "+Theme.textColor)
            console.log("Theme.backgroundColor: "+Theme.backgroundColor)
            console.log("Theme.backgroundAccentColor: "+Theme.backgroundAccentColor)
        }

        Flickable{
            id: mainArea
            height: parent.height-tools.height
            width: parent.width

            contentHeight: content.height

            Column {
                id: content
                width: parent.width - Theme.itemSpacingLarge*2
                spacing: Theme.itemSpacingLarge

                anchors{
                    left: parent.left
                    leftMargin: Theme.itemSpacingLarge
                }

                Label{
                    text: "DP Scale factor: " + size.dpScaleFactor;
                }


                Label{
                    text: "MM Scale factor: " + size.mmScaleFactor;
                }

                Rectangle{
                    color: Theme.accentColor
                    width: size.mm(10)
                    height: size.mm(10)

                    Label{
                        anchors.centerIn: parent
                        text: "1 cm"
                    }
                }

                Rectangle{
                    color: Theme.accentColor
                    width: Theme.itemWidthLarge
                    height: Theme.itemHeightMedium

                    Label{
                        text: "Theme.itemWidthLarge"
                    }
                }

                Rectangle{
                    color: Theme.accentColor
                    width: Theme.itemWidthMedium
                    height: Theme.itemHeightMedium

                    Label{
                        text: "Theme.itemWidthMedium"
                    }
                }
                Rectangle{
                    color: Theme.accentColor
                    width: Theme.itemWidthSmall
                    height: Theme.itemHeightMedium

                    Label{
                        text: "Theme.itemWidthSmall"
                    }
                }
                Rectangle{
                    color: Theme.accentColor
                    width: Theme.itemWidthExtraSmall
                    height: Theme.itemHeightMedium

                    Label{
                        text: "Theme.itemWidthExtraSmall"
                    }
                }
                Rectangle{
                    color: Theme.accentColor
                    width: Theme.itemWidthMedium
                    height: Theme.itemHeightHuge

                    Label{
                        text: "Theme.itemHeightHuge"
                    }
                }
                Rectangle{
                    color: Theme.accentColor
                    width: Theme.itemWidthMedium
                    height: Theme.itemHeightExtraLarge

                    Label{
                        text: "Theme.itemHeightExtraLarge"
                    }
                }
                Rectangle{
                    color: Theme.accentColor
                    width: Theme.itemWidthMedium
                    height: Theme.itemHeightLarge

                    Label{
                        text: "Theme.itemHeightLarge"
                    }
                }
                Rectangle{
                    color: Theme.accentColor
                    width: Theme.itemWidthMedium
                    height: Theme.itemHeightMedium

                    Label{
                        text: "Theme.itemHeightMedium"
                    }
                }
                Rectangle{
                    color: Theme.accentColor
                    width: Theme.itemWidthMedium
                    height: Theme.itemHeightSmall

                    Label{
                        text: "Theme.itemHeightSmall"
                    }
                }
                Rectangle{
                    color: Theme.accentColor
                    width: Theme.itemWidthMedium
                    height: Theme.itemHeightExtraSmall

                    Label{
                        text: "Theme.itemHeightExtraSmall"
                    }
                }
                Row{
                    Rectangle{
                        width: Theme.itemSpacingHuge
                        height: parent.height
                        color: Theme.accentColor
                    }
                    Label{
                        text: "Theme.itemSpacingHuge"
                    }
                }
                Row{
                    Rectangle{
                        width: Theme.itemSpacingLarge
                        height: parent.height
                        color: Theme.accentColor
                    }
                    Label{
                        text: "Theme.itemSpacingLarge"
                    }
                }

                Row{
                    Rectangle{
                        width: Theme.itemSpacingMedium
                        height: parent.height
                        color: Theme.accentColor
                    }
                    Label{
                        text: "Theme.itemSpacingMedium"
                    }
                }

                Row{
                    Rectangle{
                        width: Theme.itemSpacingSmall
                        height: parent.height
                        color: Theme.accentColor
                    }
                    Label{
                        text: "Theme.itemSpacingSmall"
                    }
                }

                Row{
                    Rectangle{
                        width: Theme.itemSpacingExtraSmall
                        height: parent.height
                        color: Theme.accentColor
                    }
                    Label{
                        text: "Theme.itemSpacingExtraSmall"
                    }
                }

                Label{
                    text: "fontSizeExtraLarge"
                    font.pixelSize: Theme.fontSizeExtraLarge
                }

                Label{
                    text: "fontSizeLarge"
                    font.pixelSize: Theme.fontSizeLarge
                }

                Label{
                    text: "fontSizeMedium"
                    font.pixelSize: Theme.fontSizeMedium
                }

                Label{
                    text: "fontSizeSmall"
                    font.pixelSize: Theme.fontSizeSmall
                }

                Label{
                    text: "fontSizeTiny"
                    font.pixelSize: Theme.fontSizeTiny
                }

                Row {
                    spacing: Theme.itemSpacingMedium
                    Rectangle {
                        radius: parent.height*0.5
                        width: height
                        height: Theme.itemHeightHuge
                        color: Theme.accentColor;
                    }
                    Label{
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Theme.accentColor: "  + Theme.accentColor
                        font.pixelSize: Theme.fontSizeMedium
                    }
                }

                Row {
                    spacing: Theme.itemSpacingMedium
                    Rectangle {
                        radius: parent.height*0.5
                        width: height
                        height: Theme.itemHeightHuge
                        color: Theme.fillColor;
                    }
                    Label{
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Theme.fillColor: " + Theme.fillColor
                        font.pixelSize: Theme.fontSizeMedium
                    }
                }

                Row {
                    spacing: Theme.itemSpacingMedium
                    Rectangle {
                        radius: parent.height*0.5
                        width: height
                        height: Theme.itemHeightHuge
                        color: Theme.fillDarkColor;
                    }
                    Label{
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Theme.fillDarkColor: " + Theme.fillDarkColor
                        font.pixelSize: Theme.fontSizeMedium
                    }
                }

                Row {
                    spacing: Theme.itemSpacingMedium
                    Rectangle {
                        radius: parent.height*0.5
                        width: height
                        height: Theme.itemHeightHuge
                        color: Theme.textColor;
                    }
                    Label{
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Theme.textColor: " + Theme.textColor
                        font.pixelSize: Theme.fontSizeMedium
                    }
                }

                Row {
                    spacing: Theme.itemSpacingMedium
                    Rectangle {
                        radius: parent.height*0.5
                        width: height
                        height: Theme.itemHeightHuge
                        color: Theme.backgroundColor;
                        border.width: 1
                        border.color: Theme.backgroundAccentColor
                    }
                    Label{
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Theme.backgroundColor: " + Theme.backgroundColor
                        font.pixelSize: Theme.fontSizeMedium
                    }
                }

                Row {
                    spacing: Theme.itemSpacingMedium
                    Rectangle {
                        radius: parent.height*0.5
                        width: height
                        height: Theme.itemHeightHuge
                        color: Theme.backgroundAccentColor;
                    }
                    Label{
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Theme.backgroundAccentColor: " + Theme.backgroundAccentColor
                        font.pixelSize: Theme.fontSizeMedium
                    }
                }

            }
        }
    }
}
