import QtQuick 2.6
import QtQuick.Controls

ListView {
    id: listView

    signal hideAllActions(int hideIndex)
    property color delegateColor: "transparent"
    property color bottomGradientColor: Theme.backgroundColor

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
    }
}

