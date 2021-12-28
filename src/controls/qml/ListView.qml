import QtQuick 2.6
import QtQuick.Controls 1.0
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles.Nemo 1.0
import QtQuick.Window 2.6

ListView {
    id: listView

    signal hideAllActions(int hideIndex)

    flickableDirection: Flickable.HorizontalAndVerticalFlick
    property color delegateColor: "transparent"
    property color bottomGradientColor: Theme.backgroundColor

    property double prevContentY: contentY
    property double prevContentX: contentX

    onContentYChanged: {
        if (Window.window.isUiPortrait) {
            if (contentY < 0) {
                Window.window.header.y -= contentY - originY;
                contentY = originY;
            } else {
                if (Window.window.header.y > Window.window.header.closedY) {
                    Window.window.header.y += (prevContentY - originY) - (contentY - originY);
                    if (Window.window.header.y < Window.window.header.closedY) 
                        Window.window.header.y = Window.window.header.closedY
                    contentY = prevContentY;
                }
            }
        }
        prevContentY = contentY;
    }

    onContentXChanged: {
        if (!Window.window.isUiPortrait) {
            if (contentX < 0) {
                Window.window.header.x -= contentX - originX;
                contentX = originX;
            } else {
                if (Window.window.header.x > Window.window.header.closedX) {
                    Window.window.header.x += (prevContentX - originX) - (contentX - originX);
                    contentX = prevContentX;
                }
            }
        }
        prevContentX = contentX;
    }

    onMovementEnded: {
        Window.window.header.endSwipe()
    }

    onMovementStarted: {
        if (Window.window.isUiPortrait) {
            Window.window.header.startCoord = Window.window.header.y;
        } else {
            Window.window.header.startCoord = Window.window.header.x;
        }
    }

    section.criteria: ViewSection.FullString
    section.delegate: Component{
        id: sectionHeading
        Rectangle {
            width: listView.width
            height: Theme.itemHeightMedium
            color: delegateColor

            Text {
                id: sectionText
                text: section
                font.capitalization: Font.AllUppercase
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.textColor
                anchors{
                    left: parent.left
                    leftMargin: Theme.itemSpacingSmall
                    verticalCenter: parent.verticalCenter
                }
            }

            Rectangle{
                id: line
                height: size.dp(1)
                color: Theme.textColor
                width: listView.width-sectionText.width-Theme.itemHeightExtraSmall
                anchors{
                    left: sectionText.right
                    leftMargin: Theme.itemSpacingSmall
                    verticalCenter: sectionText.verticalCenter
                }
            }
        }
    }

    Item{
        id: bottom
        width: parent.width
        height: Theme.itemHeightExtraSmall
        anchors.bottom: parent.bottom

        visible: listView.contentHeight > listView.height

        LinearGradient{
            anchors.fill: parent
            start: Qt.point(0, 0)
            end: Qt.point(0, Theme.itemHeightExtraSmall)
            gradient: Gradient {
                GradientStop { position: 0.0; color: "transparent" }
                GradientStop { position: 1.0; color: bottomGradientColor }
            }

        }
    }
}

