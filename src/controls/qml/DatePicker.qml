/****************************************************************************************
**
** Copyright (C) 2017-2025 Chupligin Sergey <neochapay@gmail.com>
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

import Nemo
import Nemo.Controls
import Nemo.Models

Item {
    id: datePicker

    width: parent ? parent.width : implicitWidth
    implicitWidth: Theme.itemWidthLarge + Theme.itemWidthSmall
    implicitHeight: header.height + Theme.itemSpacingSmall + weekDays.height + Theme.itemSpacingSmall + daysGrid.height
    height: implicitHeight

    property date currentDate: new Date()
    property bool showForwardButton: true
    property bool showBackButton: true
    property alias dayDelegate: daysGrid.delegate
    property alias weekDaysDelegate: weekendListView.delegate
    property alias selectedDate: calendarModel.selectedDate

    property var monthNames: [qsTr("January"), qsTr("February"), qsTr("March"), qsTr("April"), qsTr("May"), qsTr("June"), qsTr("July"), qsTr("August"), qsTr("September"), qsTr("October"), qsTr("November"), qsTr("December")]

    signal monthChanged()
    signal dateSelect(var date)

    Item {
        id: header
        width: parent.width
        height: Theme.itemHeightLarge
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
        }

        Image{
            id: leftArrow
            width: Theme.itemHeightMedium
            height: width
            visible: showBackButton

            anchors{
                left: parent.left
                leftMargin: (Theme.itemHeightLarge-Theme.itemHeightMedium)/2
                top: parent.top
                topMargin: (Theme.itemHeightLarge-Theme.itemHeightMedium)/2
            }
            source: "image://theme/caret-left"

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    var d = new Date(calendarModel.selectedDate);
                    calendarModel.selectedDate = new Date(d.setMonth(d.getMonth()-1))
                }
            }
        }

        Label{
            id: monthLabel
            anchors.centerIn: parent
            font.pixelSize: Theme.fontSizeLarge
            color: Theme.textColor
            text: monthNames[calendarModel.selectedDate.getMonth()]
        }

        Image{
            id: rightArrow
            width: Theme.itemHeightMedium
            height: width
            visible: showForwardButton

            anchors{
                right: parent.right
                rightMargin: (Theme.itemHeightLarge-Theme.itemHeightMedium)/2
                top: parent.top
                topMargin: (Theme.itemHeightLarge-Theme.itemHeightMedium)/2
            }
            source: "image://theme/caret-right"

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    var d = new Date(calendarModel.selectedDate);
                    calendarModel.selectedDate = new Date(d.setMonth(d.getMonth()+1))
                }
            }
        }
    }

    Item{
        id: weekDays
        width: datePicker.width
        height: Math.max(Theme.itemHeightSmall, width / 7)

        anchors{
            top: header.bottom
            topMargin: Theme.itemSpacingSmall
            left: parent.left
            right: parent.right
        }

        ListModel{
            id: weekendModel
            ListElement{
                label: qsTr("Mon")
                isWeekEnd: false
            }
            ListElement{
                label: qsTr("Tue")
                isWeekEnd: false
            }
            ListElement{
                label: qsTr("Wed")
                isWeekEnd: false
            }
            ListElement{
                label: qsTr("Thu")
                isWeekEnd: false
            }
            ListElement{
                label: qsTr("Fri")
                isWeekEnd: false
            }
            ListElement{
                label: qsTr("Sat")
                isWeekEnd: true
            }
            ListElement{
                label: qsTr("Sun")
                isWeekEnd: true
            }
        }

        ListView{
            id: weekendListView
            width: weekDays.width
            height: weekDays.height
            model: weekendModel
            orientation: ListView.Horizontal
            interactive: false
            clip: true
            delegate: Item{
                height: ListView.view ? ListView.view.height : 0
                width: height
                clip: true

                Label{
                    text: label
                    anchors.centerIn: parent
                    color: isWeekEnd ? Theme.accentColor : Theme.textColor
                    font.pixelSize: (parent.height * 0.45 < Theme.fontSizeLarge) ? parent.height * 0.45 : Theme.fontSizeLarge
                }
            }
        }
    }

    GridView {
        id: daysGrid
        width: datePicker.width
        height: cellHeight * Math.max(1, Math.ceil(count / 7))
        clip: true
        interactive: false

        anchors {
            top: weekDays.bottom
            topMargin: Theme.itemSpacingSmall
            left: parent.left
            right: parent.right
        }

        cellWidth: width / 7
        cellHeight: cellWidth

        model: calendarModel

        delegate: Item{
            id: dayCell

            width: daysGrid.cellWidth
            height: daysGrid.cellHeight

            property bool isOtherMonthDay: false
            property bool isCurrentDay: false
            property bool isSelectedDay: false
            property bool hasEventDay: false

            property date dateOfDay

            function setColor(modelData)
            {
                var color = Theme.textColor;
                /*If weekend*/
                if (modelData.dateOfDay.getDay() === 0 || modelData.dateOfDay.getDay() === 6)
                {
                    if (modelData.isCurrentDay || Qt.formatDate(modelData.dateOfDay, "yyMMdd") == Qt.formatDate(datePicker.currentDate, "yyMMdd"))
                    {
                        color = Theme.textColor
                    }
                    else
                    {
                        color = Theme.accentColor
                    }
                }

                if (modelData.isOtherMonthDay)
                {
                    color = Theme.fillDarkColor
                }
                return color;
            }

            Rectangle{
                anchors.fill: parent
                color: Theme.accentColor
                visible: Qt.formatDate(model.dateOfDay, "yyMMdd") == Qt.formatDate(datePicker.currentDate, "yyMMdd")
            }

            Label{
                text: model.dateOfDay.getDate()
                anchors.centerIn: parent
                color: dayCell.setColor(model)
                font.pixelSize: (dayCell.height * 0.45 < Theme.fontSizeLarge) ? dayCell.height * 0.45 : Theme.fontSizeLarge
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    datePicker.dateSelect(model.dateOfDay)
                }
            }
        }
    }

    CalendarModel{
        id: calendarModel
        onSelectedDateChanged: {
            datePicker.monthChanged()
        }
    }
}

