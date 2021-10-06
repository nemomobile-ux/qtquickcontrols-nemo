/****************************************************************************************
**
** Copyright (C) 2017-2021 Chupligin Sergey <neochapay@gmail.com>
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
import QtQuick.Controls 1.0 //needed for the Stack attached property
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import Nemo.Notifications 1.0

Page {
    id: root

    headerTools: HeaderToolsLayout {
        showBackButton: true;
        title: qsTr("Notifications")
    }
    allowedOrientations: Qt.PortraitOrientation | Qt.LandscapeOrientation | Qt.InvertedLandscapeOrientation | Qt.InvertedPortraitOrientation


    Notification{
        id: simpleNotify
        category: "x-nemo.example"
        itemCount: 1
        remoteActions: [ {
            "name": "default",
                "service": "org.nemomobile.notify",
                "path": "/org/nemomobile/notify",
                "iface": "org.nemomobile.notify",
                "method": "activateApp",
                "arguments": [ "Hello Nemo! You have a notification" ]
        }]
    }

    Notification{
        id: criticalNotify
        category: "x-nemo.critical"
        itemCount: 1
        urgency: Notification.Critical
        remoteActions: [ {
            "name": "default",
                "service": "org.nemomobile.notify",
                "path": "/org/nemomobile/notify",
                "iface": "org.nemomobile.notify",
                "method": "activateApp",
                "arguments": [ "Hello Nemo! You have a critical notification" ]
        }]
    }

    Notification{
        id: progressNotify
        category: "x-nemo.critical"
        itemCount: 1
        progress: 0
        remoteActions: [ {
            "name": "default",
                "service": "org.nemomobile.notify",
                "path": "/org/nemomobile/notify",
                "iface": "org.nemomobile.notify",
                "method": "activateApp",
                "arguments": [ "Hello Nemo! You have a critical notification" ]
        }]
    }

    Column {
        spacing: 40
        anchors.centerIn: parent
        Button {
            text: qsTr("Simple notification")
            onClicked:{
                simpleNotify.summary = "Hello Nemo! You have a notification"
                simpleNotify.publish()
            }
        }

        Button {
            text: qsTr("Critical notification")
            onClicked:{
                criticalNotify.summary = "Hello Nemo! You have a critical notification"
                criticalNotify.publish()
            }
        }

        Button {
            text: qsTr("Progress notification")
            onClicked:{
                progressNotify.summary = "Hello Nemo! You have a progress notification"
                progressNotify.publish()
                progressTimer.start()
            }
        }
    }

    Timer{
        id: progressTimer
        interval:1000
        repeat: true
        onTriggered: {
            if(progressNotify.progress == 1) {
                progressTimer.stop();
            } else {
                progressNotify.progress = progressNotify.progress + 0.1
            }
        }
    }
}
