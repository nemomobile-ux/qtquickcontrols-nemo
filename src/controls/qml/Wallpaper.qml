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
    color: Theme.backgroundColor

    property double maxX: Screen.width*0.1
    property double maxY: Screen.height*0.1

    ConfigurationValue {
        id: wallpaperSource
        key: "/home/glacier/homeScreen/wallpaperImage"
        defaultValue: "/usr/share/lipstick-glacier-home-qt5/qml/images/wallpaper-portrait-bubbles.png"
    }

    ConfigurationValue {
        id: enableParallax
        key: "/home/glacier/homeScreen/enableParallax"
        defaultValue: true
        onValueChanged: {
            if(value && root.size === Screen.size) {
                accelerometer.active = true
            } else {
                accelerometer.active = false
            }
        }
    }

    Accelerometer {
        id: accelerometer
        active: (enableParallax.value === true && root.size === Screen.size)
        skipDuplicates: true

        onReadingChanged: {
            var calculateX = -maxX+maxX*accelerometer.reading.x*0.1
            var calculateY = -maxY+maxY*accelerometer.reading.y*0.1
            if(calculateX > maxX) {
                calculateX = maxX
            } else if  (calculateX < -maxX) {
                calculateX = -maxX
            }

            if(calculateY > maxY) {
                calculateY = maxY
            } else if  (calculateY < -maxY) {
                calculateX = -maxY
            }

            wallpaperImage.x = calculateX
            wallpaperImage.y = calculateY
        }
    }

    Image {
        id:wallpaperImage
        width: root.width+maxX*4
        height: root.height+maxY*4

        visible: root.size === Screen.size

        x: -maxX
        y: -maxY

        source: wallpaperSource.value
        fillMode: Image.PreserveAspectCrop

        Behavior on x {
            NumberAnimation { duration: 200 }
        }

        Behavior on y {
            NumberAnimation { duration: 200 }
        }
    }

    FastBlur {
        id: wallpaperBlur
        anchors.fill: wallpaperImage

        visible: root.size === Screen.size

        source: wallpaperImage
        radius: 90
    }

    Rectangle {
        id: wallpaperDimmer
        anchors.fill: parent
        color: Theme.backgroundColor
        opacity: 0.35
        visible: root.size === Screen.size
    }
}