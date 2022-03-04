import QtQuick.Window 2.2
import QtQuick 2.6
import QtQuick.Controls 1.0

import Nemo.Configuration 1.0

Rectangle {
    id: backgroundWallpaper
    anchors.fill: parent
    visible: width != Screen.width || height != Screen.height || wallpaperSource.value == ""
    color: Theme.backgroundColor


    ConfigurationValue {
        id: wallpaperSource
        key: "/home/glacier/homeScreen/wallpaperImage"
        defaultValue: ""
    }
}
