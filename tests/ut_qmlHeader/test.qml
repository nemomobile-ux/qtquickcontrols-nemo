import QtQuick
import QtQuick.Controls
import Nemo
import Nemo.Controls

Header{
    appWindow: Item {
        property var pageStack: StackView{}
        property bool isUiPortrait: true
    }
}
