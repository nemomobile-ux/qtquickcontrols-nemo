/*
 * Copyright (C) 2013 Andrea Bernabei <and.bernabei@gmail.com>
 * Copyright (C) 2013 Jolla Ltd.
 * Copyright (C) 2017 Eetu Kahelin
 * Copyright (C) 2021-2022 Chupligin Sergey (NeoChapay) <neochapay@gmail.com>
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

import QtQuick.Window 2.2
import QtQuick 2.6
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

NemoWindow {
    id: applicationWindow

    property alias header: toolBar
    property alias pageStack: stackView
    property alias initialPage: stackView.initialItem

    readonly property bool isUiPortrait: contentArea.filteredOrientation === Qt.PortraitOrientation || contentArea.filteredOrientation === Qt.InvertedPortraitOrientation
/*because if sensor not work we have Qt.PrimaryOrientation */
    readonly property bool isSensorPortrait: sensorOrientation === Qt.PortraitOrientation || sensorOrientation === Qt.InvertedPortraitOrientation
    readonly property bool isSensorLandscape: sensorOrientation === Qt.LandscapeOrientation || sensorOrientation === Qt.InvertedLandscapeOrientation


    function push(url, params) {
        if(!params){
            params = {}
        }

        var component = Qt.createComponent(url)
        if (component.status === Component.Ready) {
            pageStack.push(component.createObject(pageStack, params))
        } else {
            pageStack.push(Qt.resolvedUrl("ErrorStackPage.qml"), {error: component.errorString()})
        }
    }

    function isOrientationAllowed(orientationToBeChecked)
    {
        var allowedOrientations = applicationWindow.allowedOrientations

        //use Page's allowed orientations if available
        if (stackView._isCurrentItemNemoPage && stackView.currentItem.allowedOrientations) {
            allowedOrientations = stackView.currentItem.allowedOrientations
        }

        //check if orientation is part of the allowed orientations mask
        //bit-by-bit AND
        //NOTE: this also returns false if orientationToBeChecked == 0,
        //so we don't need additional checks for that
        return (orientationToBeChecked & allowedOrientations)
    }

    function filterToAllowedOrientation(orient)
    {
        var orientations = [Qt.PortraitOrientation, Qt.LandscapeOrientation,
                            Qt.InvertedPortraitOrientation, Qt.InvertedLandscapeOrientation]

        if(isOrientationAllowed(orient)) {
            return orient;
        }

        for (var i=0; i<orientations.length; i++) {
            if (isOrientationAllowed(orientations[i])) {
                return orientations[i]
            }
        }
    }

    function orientationConstraintsChanged()
    {
        if (stackView.stackInitialized) {
            if(sensorOrientation === Qt.PrimaryOrientation) {
                contentArea.filteredOrientation = filterToAllowedOrientation(Screen.orientation);
            } else {
/*
If sensors is use allways into Portrant and rotate on sensors
*/
                contentArea.filteredOrientation = Qt.PortraitOrientation
                contentArea.filteredSensorOrientation = filterToAllowedOrientation(sensorOrientation)
            }
        }
    }

    SystemPalette {id: syspal}
    Wallpaper {id: wallpaper}

    Item{
        id: contentArea
        anchors.fill: parent

        property int filteredOrientation
        property int filteredSensorOrientation

        Header {
            id: toolBar
            stackView: stackView
            appWindow: applicationWindow
        }

        StackView {
            id: stackView
            anchors.top: applicationWindow.isUiPortrait ? toolBar.bottom : parent.top
            anchors.right: parent.right
            anchors.left: applicationWindow.isUiPortrait ? parent.left : toolBar.right

            height: applicationWindow.isUiPortrait ? contentArea.height - Qt.inputMethod.keyboardRectangle.height - toolBar.height - toolBar.y : parent.height
            width: applicationWindow.isUiPortrait ? parent.width : contentArea.width - Qt.inputMethod.keyboardRectangle.width - toolBar.width - toolBar.x


            clip: true
            property bool stackInitialized: false
            readonly property bool _isCurrentItemNemoPage: currentItem && currentItem.hasOwnProperty("__isNemoPage")
            //FIXME
            property int orientationTransitionRunning: 0

            Component.onCompleted: {
                stackInitialized = true
            }

            onStackInitializedChanged: {
                if(stackInitialized) {
                    var orientation;
                    if(sensorOrientation === Qt.PrimaryOrientation) {
                        orientation = Screen.orientation
                    } else {
                        orientation = sensorOrientation
                    }

                    //set Screen.orientation as default, if allowed
                    if (applicationWindow.isOrientationAllowed(orientation)) {
                        contentArea.filteredOrientation = orientation
                    } else {
                        //let the window handle it, it will fall back to an allowed orientation
                        applicationWindow.fallbackToAnAllowedOrientation()
                    }
                }
            }
            //update orientation constraints when a Page is pushed/popped
            onCurrentItemChanged: {
                if (_isCurrentItemNemoPage) {
                    applicationWindow.orientationConstraintsChanged()
                }
            }
        }
    }

    Timer {
        id: _errorTimer
        property string errorString
        interval: 50
        repeat: false
        onTriggered: {
            pageStack.replace(Qt.resolvedUrl("ErrorStackPage.qml"), {error: errorString})
            errorString = ""
        }
    }

    Connections {
        target: stackView
        function onBusyChanged(busy) {
            if (_errorTimer.errorString && !pageStack.busy) {
                _errorTimer.start()
            }
        }

        function onCurrentItemChanged(currentItem) {
            var qmltype = pageStack.currentItem.toString()
            if (qmltype.slice(0, 10) === "QQuickText") {
                _errorTimer.errorString = pageStack.currentItem.text
            }
        }
    }

    Connections {
        target: stackView._isCurrentItemNemoPage ? stackView.currentItem : null
        function onAllowedOrientationsChanged() {
            applicationWindow.orientationConstraintsChanged()
        }
    }

    onAllowedOrientationsChanged: orientationConstraintsChanged()
    Screen.onOrientationChanged: orientationConstraintsChanged()

    onSensorOrientationChanged: orientationConstraintsChanged()
}
