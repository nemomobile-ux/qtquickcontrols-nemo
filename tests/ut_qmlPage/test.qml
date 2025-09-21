import QtQuick
import QtQuick.Controls
import Nemo
import Nemo.Controls

Page{
    property var pageStack: StackView{
        property bool orientationTransitionRunning: false
    }
}
