/*
 * Copyright (C) 2013 Andrea Bernabei <and.bernabei@gmail.com>
 * Copyright (C) 2013 Jolla Ltd.
 * Copyright (C) 2017 Eetu Kahelin
 * Copyright (C) 2021-2023 Chupligin Sergey (NeoChapay) <neochapay@gmail.com>
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
import QtQuick.Controls

import Nemo
import Nemo.Controls

NemoWindow {
    id: applicationWindow

    property alias header: toolBar
    /*! \internal */
    default property alias data: contentArea.data

    property alias pageStack: stackView
    property alias initialPage: stackView.initialItem
    property bool isUiPortrait: applicationWindow.width < applicationWindow.height

    property alias mainMenu: mainMenuArea.sourceComponent
    property int mainMenuWidth: Theme.itemWidthExtraLarge

    color: Theme.backgroundColor

    onGoBack: {
        pageStack.pop()
    }

    //Safety version of pageStack.push - if we can't load component - show error page page with
    //error message and back button

    function push(url, params) {
        if(!params){
            params = {}
        }
        var component = Qt.createComponent(url)
        if (component.status === Component.Ready) {
            if(mainMenuArea.width != applicationWindow.width && mainMenuArea.width != 0) {
                pageStack.replace(component.createObject(pageStack, params))
            } else {
                pageStack.push(component.createObject(pageStack, params))
            }
        } else {
            console.warn("Error loading component", url, component.errorString())
            pageStack.push(Qt.resolvedUrl("ErrorStackPage.qml"), {error: component.errorString()})
        }
    }

    function pop() {
        pageStack.pop()
    }

    function replace(url, params) {
        if(!params){
            params = {}
        }

        var component = Qt.createComponent(url)
        if (component.status === Component.Ready) {
            pageStack.push(component.createObject(pageStack, params))
        } else {
            console.warn("Error loading component", url, component.errorString())
            pageStack.push(Qt.resolvedUrl("ErrorStackPage.qml"), {error: component.errorString()})
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
        target: pageStack
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

    function fallbackToAnAllowedOrientation()
    {
        var orientations = [Qt.PortraitOrientation, Qt.LandscapeOrientation,
                            Qt.InvertedPortraitOrientation, Qt.InvertedLandscapeOrientation]

        //TODO: use a better algo to fall back to the *closest* UI orientation
        //example: don't go from InvertedLandscape to Landscape, but to InvertedPortrait/Portrait, if allowed
        for (var i=0; i<orientations.length; i++) {
            if (isOrientationAllowed(orientations[i])) {
                contentArea.filteredOrientation = orientations[i]
                break
            }
        }
    }

    function isOrientationAllowed(orientationToBeChecked)
    {
        var allowedOrientations = applicationWindow.allowedOrientations

        //use Page's allowed orientations if available
        if (stackView._isCurrentItemNemoPage() && stackView.currentItem.allowedOrientations) {
            allowedOrientations = stackView.currentItem.allowedOrientations
        }

        //check if orientation is part of the allowed orientations mask
        //bit-by-bit AND
        //NOTE: this also returns false if orientationToBeChecked == 0,
        //so we don't need additional checks for that
        return (orientationToBeChecked & allowedOrientations)
    }

    Item {
        id: backgroundItem
        anchors.fill: parent

        Item {
            id: clipping

            z: 1
            width: parent.width - (!isUiPortrait ? stackView.panelSize : 0)
            height: parent.height - (isUiPortrait ? stackView.panelSize : 0)
            clip: stackView.panelSize > 0


            //This is the rotating item
            Item {
                id: contentArea
                anchors.centerIn: parent

                transform: Scale {
                    id: contentScale
                    property bool animationRunning: xAnim.running || yAnim.running
                    Behavior on xScale { NumberAnimation { id: xAnim; duration: 100 } }
                    Behavior on yScale { NumberAnimation { id: yAnim; duration: 100 } }
                }

                property int _horizontalDimension: parent ? parent.width : 0
                property int _verticalDimension: parent ? parent.height : 0

                property alias defaultOrientationTransition: orientationState.defaultTransition

                // This is used for states switching
                property int filteredOrientation

                //this is the reliable value which changes during the orientation transition
                property int uiOrientation

                property bool orientationTransitionRunning: false

                Loader{
                    id: mainMenuArea
                    height: parent.height
                    clip: true
                    visible: width != 0
                    width: if(sourceComponent === null) {
                               return 0
                           } else if (applicationWindow.isUiPortrait) {
                               if(stackView.depth == 1) {
                                   return parent.width
                               } else {
                                   return 0
                               }

                           } else {
                               return applicationWindow.mainMenuWidth
                           }

                    anchors{
                        top: applicationWindow.isUiPortrait ? toolBar.bottom : parent.top
                        left: applicationWindow.isUiPortrait ? parent.left : toolBar.right
                    }
                }


                StackView {
                    id: stackView
                    anchors.top: mainMenuArea.top
                    anchors.right: parent.right
                    anchors.left: mainMenuArea.right
                    anchors.bottom: parent.bottom

                    property real panelSize: 0
                    property real previousImSize: 0
                    property real imSize: !Qt.application.active ? 0 : (isUiPortrait ? (applicationWindow._transpose ? Qt.inputMethod.keyboardRectangle.width
                                                                                                        : Qt.inputMethod.keyboardRectangle.height)
                                                                                     : (applicationWindow._transpose ? Qt.inputMethod.keyboardRectangle.height
                                                                                                        : Qt.inputMethod.keyboardRectangle.width))


                    //  TODO: fix on landscape and inverted landscape
                    onImSizeChanged: {
                        if (imSize <= 0 && previousImSize > 0) {
                            imShowAnimation.stop()
                            imHideAnimation.start()
                        } else if (imSize > 0 && previousImSize <= 0) {
                            imHideAnimation.stop()
                            imShowAnimation.to = imSize
                            imShowAnimation.start()
                        } else {
                            panelSize = imSize
                        }

                        previousImSize = imSize
                    }
                    clip: true
                    Component.onCompleted: {
                        stackInitialized = true
                    }
                    //IMPORTANT: this property makes it so that at app startup we wait for the initial page to be pushed
                    //before determining the initial ui orientation (see the states logic below)
                    //If we don't use this, the orientation will change first time based on NemoWindow's allowedOrientation,
                    //and the second time based on the allowedOrientations of the initialItem of the stack.
                    //Using this property avoids that, and make the UI directly start in the correct orientation
                    //TODO: find a cleaner way to do it (if there's any)
                    property bool stackInitialized: false
                    onStackInitializedChanged: if (stackInitialized) {
                                                   //set Screen.orientation as default, if allowed
                                                   if (applicationWindow.isOrientationAllowed(applicationWindow.orientation)) {
                                                       contentArea.filteredOrientation = applicationWindow.orientation
                                                   } else {
                                                       //let the window handle it, it will fall back to an allowed orientation
                                                       applicationWindow.fallbackToAnAllowedOrientation()
                                                   }
                                               }

                    //this has to be a function, property won't work inside onCurrentItemChanged, as the property binding hasn't been updated yet there
                    //(hence we'd be using the old currentItem)
                    function _isCurrentItemNemoPage()
                    {
                        return currentItem && currentItem.hasOwnProperty("__isNemoPage")
                    }

                    //update orientation constraints when a Page is pushed/popped
                    onCurrentItemChanged: {
                        if (_isCurrentItemNemoPage()) {
                            applicationWindow.fallbackToAnAllowedOrientation()
                        }
                    }

                    //This properties are accessible for free by the Page via Stack.view.<property>
                    readonly property int orientation: contentArea.uiOrientation
                    property alias orientationTransitionRunning: contentArea.orientationTransitionRunning

                    Connections {
                        id: pageConn
                        target: stackView._isCurrentItemNemoPage() ? stackView.currentItem : null
                        function onAllowedOrientationsChanged() { applicationWindow.fallbackToAnAllowedOrientation() }
                    }

                    SequentialAnimation {
                        id: imHideAnimation
                        PauseAnimation {
                            duration:  200
                        }
                        NumberAnimation {
                            target: stackView
                            property: 'panelSize'
                            to: 0
                            duration:200
                            easing.type: Easing.InOutQuad
                        }
                    }

                    NumberAnimation {
                        id: imShowAnimation
                        target: stackView
                        property: 'panelSize'
                        duration:  200
                        easing.type: Easing.InOutQuad
                    }

                }

                Header {
                    id: toolBar
                    stackView: applicationWindow.pageStack
                    appWindow: applicationWindow
                }

                Item {
                    id: orientationState

                    state: 'Unanimated'

                    states: [
                        State {
                            name: 'Unanimated'
                            when: !stackView || !stackView.stackInitialized
                        },
                        State {
                            name: 'Portrait'
                            when: contentArea.filteredOrientation === Qt.PortraitOrientation && stackView.stackInitialized
                            PropertyChanges {
                                target: contentArea
                                restoreEntryValues: false
                                width: _horizontalDimension
                                height: _verticalDimension
                                rotation: 0
                                uiOrientation: Qt.PortraitOrientation
                            }
                            AnchorChanges {
                                target: clipping
                                anchors.top: parent.top
                                anchors.left: parent.left
                                anchors.right: undefined
                                anchors.bottom: undefined
                            }
                        },
                        State {
                            name: 'Landscape'
                            when: contentArea.filteredOrientation === Qt.LandscapeOrientation && stackView.stackInitialized
                            PropertyChanges {
                                target: contentArea
                                restoreEntryValues: false
                                width: _verticalDimension
                                height: _horizontalDimension
                                rotation: 270
                                uiOrientation: Qt.LandscapeOrientation
                            }
                            AnchorChanges {
                                target: clipping
                                anchors.top: undefined
                                anchors.left: undefined
                                anchors.right: parent.right
                                anchors.bottom: parent.bottom
                            }
                        },
                        State {
                            name: 'PortraitInverted'
                            when: contentArea.filteredOrientation === Qt.InvertedPortraitOrientation && stackView.stackInitialized
                            PropertyChanges {
                                target: contentArea
                                restoreEntryValues: false
                                width: _horizontalDimension
                                height: _verticalDimension
                                rotation: 180
                                uiOrientation: Qt.InvertedPortraitOrientation
                            }
                            AnchorChanges {
                                target: clipping
                                anchors.top: undefined
                                anchors.left: undefined
                                anchors.right: parent.right
                                anchors.bottom: parent.bottom
                            }
                        },
                        State {
                            name: 'LandscapeInverted'
                            when: contentArea.filteredOrientation === Qt.InvertedLandscapeOrientation && stackView.stackInitialized
                            PropertyChanges {
                                target: contentArea
                                restoreEntryValues: false
                                width: _verticalDimension
                                height: _horizontalDimension
                                rotation: 90
                                uiOrientation: Qt.InvertedLandscapeOrientation
                            }
                            AnchorChanges {
                                target: clipping
                                anchors.top: undefined
                                anchors.left: parent.left
                                anchors.right: undefined
                                anchors.bottom: parent.bottom
                            }
                        }
                    ]

                    property Transition defaultTransition: Transition {
                        to: 'Portrait,Landscape,PortraitInverted,LandscapeInverted'
                        from: 'Portrait,Landscape,PortraitInverted,LandscapeInverted'
                        SequentialAnimation {
                            PropertyAction {
                                target: contentArea
                                property: 'orientationTransitionRunning'
                                value: true
                            }
                            NumberAnimation {
                                target: contentArea
                                property: 'opacity'
                                to: 0
                                duration: 150
                            }
                            PropertyAction {
                                target: contentArea
                                properties: 'width,height,rotation,uiOrientation'
                            }
                            AnchorAnimation {
                                duration: 0
                            }
                            NumberAnimation {
                                target: contentArea
                                property: 'opacity'
                                to: 1
                                duration: 150
                            }
                            PropertyAction {
                                target: contentArea
                                property: 'orientationTransitionRunning'
                                value: false
                            }
                        }
                    }

                    Component.onCompleted: {
                        if (transitions.length === 0) {
                            transitions = [ defaultTransition ]
                        }
                    }
                }
            }
        }
    }
}
