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
            implicitHeight: Theme.itemHeightExtraSmall - Theme.itemSpacingExtraSmall
            color: control.checked ? Theme.accentColor : Theme.fillDarkColor
            anchors.centerIn: parent
        }


        Rectangle {
            id: ball
            width: Theme.itemHeightExtraSmall
            height: Theme.itemHeightExtraSmall
            radius: width/2
            anchors.verticalCenter: parent.verticalCenter

            clip: true

            gradient: Gradient {
                GradientStop { position: 0.0; color: Theme.textColor }
                GradientStop { position: 1.0; color: Theme.fillDarkColor }
            }

            x: control.checked ? background.width - ball.width : 0
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
                to: background.width - ball.width
                duration: 400
            }
            PropertyAnimation {
                target: bgArea
                property: "color"
                to: Theme.accentColor
                duration: 400
            }
        }

        ParallelAnimation {
            id: unCheckAnimation
            running: false
            NumberAnimation {
                target: ball
                property: "x"
                to: 0
                duration: 400
            }
            PropertyAnimation {
                target: bgArea
                property: "color"
                to: Theme.fillDarkColor
                duration: 400
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
