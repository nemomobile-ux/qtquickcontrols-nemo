/*
 * Copyright (C) 2018-2022 Chupligin Sergey <neochapay@gmail.com>
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

import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls

import Nemo

Rectangle{
    id: toolsIndicator
    color: Theme.accentColor

    property bool started: false

    SequentialAnimation {
        id: indicateToolsAnimation
        running: false
        loops: 2

        PropertyAnimation {
            to: Theme.backgroundColor
            target: toolsIndicator
            property: "color"
            duration: 1000
        }

        PropertyAnimation {
            to: Theme.accentColor
            target: toolsIndicator
            property: "color"
            duration: 1000
        }

         onStopped: {
            toolsIndicator.started = true
        }
    }

    Component.onCompleted: {
        if(visible && !started) {
            indicateToolsAnimation.start()
        }
    }

    onVisibleChanged: {
        if(visible && !started) {
            indicateToolsAnimation.start()
        }
    }

    Connections{
        target: pageStack
        function onDepthChanged() {
            toolsIndicator.started = false
        }
    }
}
