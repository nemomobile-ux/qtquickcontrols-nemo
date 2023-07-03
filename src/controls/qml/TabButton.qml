import QtQuick
import QtQuick.Controls

import Nemo

TabButton {
    id: control

    background: Rectangle{
        anchors.fill: parent
        color: Theme.backgroundColor

        Rectangle {
            anchors{
                left: parent.left
            }
            width: size.dp(1)
            height: parent.height
            color: Theme.fillDarkColor
        }

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
