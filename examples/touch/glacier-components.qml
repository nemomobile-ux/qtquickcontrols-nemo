/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Copyright (C) 2017-2026 Chupligin Sergey <neochapay@gmail.com>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick
import QtQuick.Controls
import QtQuick.Window

import Nemo
import Nemo.Controls

import "content"

ApplicationWindow {
    id: appWindow

    mainMenu: ListView {
        id: mainList
        model: pageModel
        anchors.fill: parent
        clip: true
        delegate: ListViewItemWithActions {
            iconVisible: false
            label: title
            onClicked: appWindow.push(Qt.resolvedUrl(page))
        }

        ScrollDecorator{
            flickable: mainList
        }
    }

    ListModel {
        id: pageModel
        ListElement {
            title: qsTr("Live-Coding Arena")
            page: "content/LiveCoding.qml"
        }
        ListElement {
            title: qsTr("Buttons (locked to portrait)")
            page: "content/ButtonPage.qml"
        }
        ListElement {
            title: qsTr("Sliders")
            page: "content/SliderPage.qml"
        }
        ListElement {
            title: qsTr("ProgressBar")
            page: "content/ProgressBarPage.qml"
        }
        ListElement {
            title: qsTr("DatePicker")
            page: "content/DatePickerPage.qml"
        }
        ListElement {
            title: qsTr("TimePicker")
            page: "content/TimePickerPage.qml"
        }
        ListElement {
            title: qsTr("Tabs")
            page: "content/TabBarPage.qml"
        }
        ListElement {
            title: qsTr("TextInput")
            page: "content/TextInputPage.qml"
        }
        ListElement {
            title: qsTr("Spinner")
            page: "content/SpinnerPage.qml"
        }
        ListElement {
            title: qsTr("Ring indicator")
            page: "content/RingIndicatorPage.qml"
        }
        ListElement {
            title: qsTr("SelectRoller")
            page: "content/SelectRollerPage.qml"
        }
        ListElement {
            title: qsTr("ListView")
            page: "content/ListViewPage.qml"
        }
        ListElement {
            title: qsTr("Labels (no orientation locks)")
            page: "content/LabelPage.qml"
        }
        ListElement {
            title: qsTr("Switches")
            page: "content/CheckboxPage.qml"
        }
        ListElement {
            title: qsTr("ButtonRow (locked to landscape)")
            page: "content/ButtonRowPage.qml"
        }
        ListElement {
            title: qsTr("Dialogs")
            page: "content/DialogsPage.qml"
        }
        ListElement {
            title: qsTr("Icon button")
            page: "content/IconPage.qml"
        }
        ListElement {
            title: qsTr("Nemo colorized icon")
            page: "content/NemoIconPage.qml"
        }
        ListElement {
            title: qsTr("Notifications")
            page: "content/NotificationsPage.qml"
        }
        ListElement {
            title: qsTr("Status icon")
            page: "content/StatusNotifyPage.qml"
        }
        ListElement {
            title: qsTr("Broken page")
            page: "content/BrokenPage.qml"
        }
    }

    initialPage: Page {
        id: pageItem
        allowedOrientations:  Qt.PortraitOrientation | Qt.LandscapeOrientation | Qt.InvertedLandscapeOrientation | Qt.InvertedPortraitOrientation

        headerTools: HeaderToolsLayout {
            id: tools

            title: qsTr("Nemo components gallery")
            tools: [
                ToolButton {
                    iconSource: "image://theme/cog"
                    showCounter: false
                },
                ToolButton {
                    id: editIcon
                    iconSource: "image://theme/edit"
                    showCounter: true
                    counterValue: 0

                    onClicked: {
                        editIcon.counterValue++
                    }

                    active: true
                },
                ToolButton {
                    iconSource: "image://theme/refresh"
                    showCounter: true
                    showZeroCounter: true
                }
            ]
        }
    }
}
