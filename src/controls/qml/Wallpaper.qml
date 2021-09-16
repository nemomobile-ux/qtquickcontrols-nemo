import QtQuick.Window 2.2
import QtQuick 2.6
import QtQuick.Controls 1.0

import QtGraphicalEffects 1.0
import QtSensors 5.2

import Nemo.Configuration 1.0

import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

Rectangle {
    id: backgroundWallpaper
    anchors.fill: parent
    visible: width != Screen.width || height != Screen.height
    color: Theme.backgroundColor
}
