import QtQuick 2.6

import Nemo.Controls

Item {
    id: shell
    anchors.fill: parent
    signal accepted()
    signal canceled()
    signal selected()
    property alias cancelText: cancel.text
    property alias acceptText: accept.text
    property alias acceptEnabled: accept.enabled
    property alias headingText: heading.text
    property alias subLabelText: subLabel.text
    property alias iconColorized: icon.colorized
    property list<Item> content;

    property real bgOpacity: 1;

    y: visible ? 0 : parent.height

    Behavior on y {
        NumberAnimation {
            duration: 200
        }
    }

    z: 999

    property string icon: ""
    property bool inline: true

    function open(){
        shell.visible = true
    }

    function close(){
        shell.visible = false
    }

    Rectangle {
        id: shadow
        width: parent.width
        height: inline ? (parent.height-cancel.height)/2 : parent.height-cancel.height
        opacity: shell.bgOpacity
        color: Theme.backgroundColor
        anchors.bottom: cancel.top
    }

    Column {
        anchors.fill: inline ? shadow : parent
        anchors.margins: Theme.itemSpacingMedium
        spacing: inline ? Theme.itemSpacingSmall : Theme.itemSpacingHuge

        Item {
            width: parent.width
            height: Theme.itemSpacingHuge
            visible: icon.visible

            NemoIcon{
                id: icon
                source: shell.icon
                color: Theme.textColor
                width: Theme.itemHeightMedium
                height: width
                anchors{
                    horizontalCenter: parent.horizontalCenter
                }
                visible: shell.icon != "" && !inline
                fillMode: Image.PreserveAspectCrop
            }
        }

        Label {
            id: heading
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.weight: Theme.fontWeightLarge
            font.pixelSize:  inline ? Theme.fontSizeTiny : Theme.fontSizeSmall
            wrapMode: Text.Wrap
        }

        Label {
            id:subLabel
            width: parent.width
            wrapMode: Text.Wrap
            font.weight: Theme.fontWeightMedium
            font.pixelSize:  inline ? Theme.fontSizeTiny : Theme.fontSizeSmall
            horizontalAlignment: Text.AlignHCenter
        }

        Item {
            children: content
            width: parent.width
            height: childrenRect.height
        }

    }

    Button {
        id: cancel
        height: Theme.itemHeightLarge
        width: parent.width/2
        anchors {
            left: parent.left
            bottom: parent.bottom
        }
        onClicked: {
            shell.canceled()
            shell.selected()
            close()
        }
    }
    Button {
        id: accept
        height: Theme.itemHeightLarge
        width: parent.width/2
        primary: true
        anchors {
            left: cancel.right
            bottom: parent.bottom
        }
        onClicked: {
            shell.accepted()
            shell.selected()
            close();
        }
    }


}
