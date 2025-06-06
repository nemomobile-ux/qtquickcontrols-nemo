import QtQuick
import QtQuick.Controls
import Nemo

CheckBox {
    id: control

    property int fontSize: Theme.fontSizeSmall

    property bool indeterminate: false

    indicator: Rectangle {
        id: background
        color: "transparent"
        implicitWidth: Theme.itemWidthExtraSmall
        implicitHeight: Theme.itemHeightExtraSmall
        y: parent.height / 2 - height / 2

        Rectangle {
            id: bgArea
            implicitWidth: Theme.itemWidthExtraSmall
            implicitHeight: Theme.itemHeightExtraSmall
            color: control.checked ? Theme.accentColor : Theme.fillDarkColor
            anchors.centerIn: parent
            radius: width/2

            Rectangle {
                id: checkedIndicator
                width: Theme.itemSpacingExtraSmall*0.2
                height: Theme.itemHeightExtraSmall/2
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
                x: Theme.itemWidthExtraSmall*0.2 - width/2 + ball.padding
                radius: width/2
            }

            Rectangle {
                id: uncheckedIndicator
                width: 2 * Math.round(Theme.itemHeightExtraSmall/5)
                height: width
                color: "#c9c9c9"
                anchors.verticalCenter: parent.verticalCenter
                x: Theme.itemWidthExtraSmall*0.8 - width/2 - ball.padding
                radius: width/2

                Rectangle {
                    width: 2 * Math.round((parent.width*0.6)/2)
                    height: width
                    anchors.centerIn: parent
                    radius: width/2
                    color: Theme.fillDarkColor
                }
            }
        }


        Rectangle {
            id: ball
            width: 2 * Math.round((Theme.itemHeightExtraSmall*0.8)/2)
            height: 2 * Math.round((Theme.itemHeightExtraSmall*0.8)/2)
            radius: width/2
            anchors.verticalCenter: parent.verticalCenter
            clip: true
            property int padding: (bgArea.height - ball.height)/2
            property int checkedX: background.width - ball.width - padding
            property int uncheckedX: padding
            x: control.checked ? checkedX : uncheckedX
            color: Theme.backgroundColor
        }

        Connections {
            target: control
            function onCheckedChanged() {
                if(!indeterminate) {
                    if (control.checked) {
                        checkAnimation.restart()
                    } else {
                        unCheckAnimation.restart()
                    }
                }
            }

            function onIndeterminateChanged() {
                indeterminateAnimation.stop()
                if(indeterminate) {
                    indeterminateAnimation.start()
                } else {
                    indeterminateAnimation.stop()
                    bgArea.color = control.checked ? Theme.accentColor : Theme.fillDarkColor
                }
            }
        }

        Component.onCompleted: {
            if(control.indeterminate){
                indeterminateAnimation.start()
            }
        }

        ParallelAnimation {
            id: checkAnimation
            running: false
            NumberAnimation {
                target: ball
                property: "x"
                from: ball.uncheckedX
                to: ball.checkedX
                duration: 250
                easing.type: Easing.InCubic
            }
            PropertyAnimation {
                target: bgArea
                property: "color"
                from: Theme.fillDarkColor
                to: Theme.accentColor
                duration: 250
                easing.type: Easing.InCubic
            }
        }

        ParallelAnimation {
            id: unCheckAnimation
            running: false
            NumberAnimation {
                target: ball
                property: "x"
                from: ball.checkedX
                to: ball.uncheckedX
                duration: 250
                easing.type: Easing.InCubic
            }
            PropertyAnimation {
                target: bgArea
                property: "color"
                from: Theme.accentColor
                to: Theme.fillDarkColor
                duration: 250
                easing.type: Easing.InCubic
            }
        }

        SequentialAnimation{
            id: indeterminateAnimation
            running: false

            loops: Animation.Infinite

            PropertyAnimation {
                target: bgArea
                property: "color"
                to: control.checked ? Theme.fillDarkColor : Theme.accentColor
                duration: 500
            }

            PropertyAnimation {
                target: bgArea
                property: "color"
                to: control.checked ? Theme.accentColor : Theme.fillDarkColor
                duration: 500
            }
        }
    }

    contentItem: Label {
        text: control.text
        color: Theme.textColor
        font.pixelSize:control.fontSize
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }

    spacing: Theme.itemSpacingSmall
}
