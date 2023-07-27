/****************************************************************************************
**
** Copyright (C) 2018-2021 Chupligin Sergey <neochapay@gmail.com>
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
import Nemo.Controls

Item{
    id: timePicker
    width: 400
    height: width

    property date currentTime: new Date()

    property alias minutesLineWidth: minutes.lineWidth
    property alias hoursLineWidth: hours12.lineWidth
    property real gaugesSpacing: Theme.itemSpacingSmall

    property bool readOnly: true

    Item{
        id: clockWidget
        width: parent.width
        height: parent.width

        RingIndicator{
            id: hours12
            anchors.centerIn: parent

            width: parent.width - (2 * minutes.lineWidth + timePicker.gaugesSpacing)
            height: parent.height - (2 * minutes.lineWidth + timePicker.gaugesSpacing)

            startAngle: 0
            stopAngle: 360

            lineWidth: Theme.itemHeightSmall
            color: Theme.accentColor
            opacity: (currentTime.getHours() >= 12) ? 0.6 : 0.1
        }

        RingIndicator{
            id: hours
            anchors.centerIn: parent

            width: hours12.width
            height: hours12.height

            startAngle: 0
            stopAngle: 360/12*currentTime.getHours()

            lineWidth: hours12.lineWidth
            color: Theme.accentColor

            Label{
                id: hourLabel
                text: currentTime.getHours()
                font.pixelSize: hours.lineWidth
                font.bold: true

                anchors{
                    top: hours.top
                    topMargin: -hours.lineWidth/4
                    right: hours.horizontalCenter
                    rightMargin: hours.lineWidth/4
                }
            }
        }

        RingIndicator{
            id: minutes
            anchors.centerIn: parent

            width: parent.width
            height: parent.height

            startAngle: 0
            stopAngle: 360/60*currentTime.getMinutes()

            lineWidth: Theme.itemHeightExtraSmall/2
            color: Theme.accentColor

            Label{
                id: minuteLabel
                text: currentTime.getMinutes()
                font.pixelSize: minutes.lineWidth
                font.bold: true

                anchors{
                    top: minutes.top
                    topMargin: -minutes.lineWidth/4
                    right: minutes.horizontalCenter
                    rightMargin: minutes.lineWidth/4
                }
            }
        }
    }

    MouseArea{
        anchors.fill: parent
        enabled: !timePicker.readOnly
        hoverEnabled: true
        onPositionChanged: {
            if (!pressed) {
                return
            }

            mousePositionToTime();
        }
        onClicked: mousePositionToTime();

        function mousePositionToTime() {
            var minute_radius_max = clockWidget.width/2;
            var minute_radius_min = minute_radius_max - ( minutes.lineWidth + timePicker.gaugesSpacing/2) ;
//            var hour_radius_max = minute_radius_min - 1;
            var hour_radius_min = minute_radius_min - (hours.lineWidth + timePicker.gaugesSpacing);

            var click_radius = Math.sqrt(Math.pow((mouseX-clockWidget.width/2),2)+Math.pow((mouseY-clockWidget.width/2),2))

            if (click_radius <= minute_radius_max && click_radius >= hour_radius_min) {

                var ang = getAngle(mouseX,mouseY)
                var d = new Date(currentTime);
                if (click_radius >= minute_radius_min) {

                    currentTime =  new Date(d.setMinutes(Math.round(60*ang/360)))

                } else {

                    if (currentTime.getHours() >= 12) {
                        currentTime =  new Date(d.setHours(Math.round(12*ang/360)+12))
                    } else {
                        currentTime =  new Date(d.setHours(Math.round(12*ang/360)))
                    }
                }
            }
        }
    }

    function getAngle(x,y)
    {
        var a = (Math.atan((y - clockWidget.width/2)/(x - clockWidget.width/2)) * 180) / Math.PI + 90
        if (x < clockWidget.width/2)
        {
            a += 180
        }
        return a
    }
}
