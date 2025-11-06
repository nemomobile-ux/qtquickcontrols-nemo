/*
 * Copyright (C) 2018-2025 Chupligin Sergey <neochapay@gmail.com>
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

Item {
    id: header
    width: toolBarRect.width
    height: parent.height

    //make sure the header is aligned properly
    Binding on y {
        restoreMode: Binding.RestoreBinding
        when: !appWindow.isUiPortrait
        value: 0
    }

    Binding on x {
        restoreMode: Binding.RestoreBinding
        when: appWindow.isUiPortrait
        value: 0
    }

    //Handle portrait/landscape orientation layout changes
    //Using states is better than having "anchors.left: appWindow.isUiPortrait ? portraitanchor : landscapeanchor"
    //because in the latter way when isUiPortrait changes, the order of reevaluation of the anchors bindings
    //(hence the resulting layout) cannot be predicted. Using States we avoid that source of issues
    states: [
        State {
            id: portraitState
            when: appWindow && appWindow.isUiPortrait
            AnchorChanges {
                target: toolBarRect;
                anchors.left: header.left
            }
            //having width/height as PropertyChanges avoids creating binding loops
            PropertyChanges {
                target: header
                width: parent ? parent.width : 0
                height: toolBarRect.height
            }
            //remember: the PropertyChanges handle bindings by default, unless "explicit: true" is set
            PropertyChanges {
                target: toolBarRect
                width: parent.width
                height: Theme.itemHeightLarge
            }
        },
        State {
            id: landscapeState
            when: appWindow && !appWindow.isUiPortrait
            AnchorChanges {
                target: toolBarRect;
                anchors.left: undefined
            }
            PropertyChanges {
                target: header
                width: toolBarRect.width
                height: parent ? parent.height : 0
            }
            PropertyChanges {
                target: toolBarRect
                width: Theme.itemHeightLarge
                height: parent.height
            }
        }
    ]

    //this is the value that will be used by toolBarContainer
    //please pretty please don't turn it into an alias to toolBarContainer.data,
    //because in that way you won't get change signals (.data doesn't have NOTIFY
    //and is a Q_PRIVATE_PROPERTY) and you won't be able to access the toolbarLayout
    //directly. So -> not a good idea :)
    property variant toolBarLayout

    property double speedBumpThreshold: 3/5

    //those properties are initialized when the header is created
    //(See ApplicationWindow source)
    property StackView stackView
    property variant appWindow

    //propagate header reference to headerTools which have the "header" property
    //used by the headerTools to know when it should display the back button
    //(i.e. to get header.stackView.depth value)
    Connections {
        target: stackView
        function onCurrentItemChanged() {
            if (changeToolsLayoutAnim.running) {
                changeToolsLayoutAnim.complete()
            }
            changeToolsLayoutAnim.start()
        }
    }

    function propagateHeaderReference() {
        if (toolBarLayout && toolBarLayout.hasOwnProperty("header")) {
            toolBarLayout.header = toolBar
        }
    }

    function updateHeaderTools() {
        header.toolBarLayout = stackView.currentItem ? stackView.currentItem.headerTools : undefined
    }

    SequentialAnimation {
        id: changeToolsLayoutAnim
        NumberAnimation { id: fadeOut; target: header; property: "opacity"; to: 0;
            duration: 250; easing.type: Easing.OutQuad; loops: !toolBarLayout ? 0 : 1 }
        //headerTools may change now, so we have to close the drawer
        ScriptAction { script: updateHeaderTools() }
        //tell the (maybe new) layout that we're its container
        ScriptAction { script: propagateHeaderReference() }
        NumberAnimation { id: fadeIn; target: header; property: "opacity"; to: 1;
            duration: 250; easing.type: Easing.OutQuad; loops: !toolBarLayout ? 0 : 1  }

    }

    NumberAnimation {
        id: slidingAnim
        target: header
        property: appWindow.isUiPortrait ? "y" : "x"
        from: appWindow.isUiPortrait ? header.y : header.x
        easing.type: Easing.OutExpo
    }

    //This item only resizes when UI rotates, while toolBarContainer is the one actually rotating
    Item {
        id: toolBarRect
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        //This is item which holds the toolbar and rotates with the UI
        Item {
            id: toolBarContainer
            //no anchors here, as we're using the rotation to change between portrait/landscape modes
            width: appWindow.isUiPortrait ? parent.width : parent.height
            height: appWindow.isUiPortrait ? parent.height : parent.width
            anchors.centerIn: parent
            data: toolBarLayout ? toolBarLayout : null
            rotation: appWindow.isUiPortrait ? 0 : -90
        }
    }
}
