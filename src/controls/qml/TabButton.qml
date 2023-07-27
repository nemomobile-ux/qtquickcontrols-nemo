import QtQuick
import QtQuick.Controls

import Nemo

TabButton {
    id: control
    implicitHeight: Theme.itemHeightMedium

    background: Rectangle{
        anchors.fill: parent
        color: Theme.backgroundColor

        Rectangle {
            visible: control.checked
            anchors{
                bottom: parent.bottom
            }
            width: parent.width
            height: size.dp(1)
            color: Theme.accentColor
        }
    }

    contentItem: Text {
        anchors.fill: parent
        color: (control.checked) ? Theme.accentColor : Theme.textColor
        text: control.text.toUpperCase()
        font.pixelSize: Theme.fontSizeTiny
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
