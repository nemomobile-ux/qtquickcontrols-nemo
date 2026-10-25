/*
 * Copyright (C) 2013 Andrea Bernabei <and.bernabei@gmail.com>
 * Copyright (C) 2025 Chupligin Sergey <neochapay@gmail.com>
 * Copyright (C) 2026 Timo Könnecke <github.com/moWerk>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

import Nemo
import QtQuick
import QtQuick.Controls

/*!
    \qmltype Button
    \inqmlmodule Nemo.Controls
    \inherits QtQuick.Controls::Button

    \brief A push button in the Glacier style: a raised, rounded pill with
    a vertical gradient, a hairline border and a soft drop shadow.

    Graphic design of the button elements by Greg Goncharov (gregguh).

    Every size is a ratio of the button height, which is
    \c Theme.itemHeightMedium, so the button scales with the theme's dp
    factor. Every colour comes from the Theme: the variant colour is the top
    of the gradient and the other stops are derived from it.

    \section1 Variants

    \table
    \header \li Variant \li How to get it \li Look
    \row \li Normal \li default
         \li light gradient from \c Theme.backgroundAccentColor, dark label
    \row \li Primary \li \c primary, \c highlighted or \c checked
         \li gradient starting at \c Theme.accentColor, light label
    \row \li Destructive \li \c destructive
         \li red gradient, light label; for actions that discard or delete
    \row \li Backgrounded \li \c backgrounded
         \li flat \c Theme.backgroundColor, light label, no gradient
    \endtable

    \section1 States

    \list
    \li \b Pressed: the gradient deepens, a dark overlay is laid on top, a
        light label dims and the drop shadow disappears, so the button reads
        as pushed in.
    \li \b Disabled: a light dark overlay is laid on top and the label is
        muted. This applies to every variant.
    \endlist

    \section1 Content

    The label uses the template's \c text, and the icon uses the
    template's \c icon.source, drawn with \l NemoIcon in the label colour;
    \c icon.name is not used. \c display chooses between
    \c AbstractButton.TextOnly, \c AbstractButton.IconOnly and
    \c AbstractButton.TextBesideIcon. An icon-only button keeps the full
    height and becomes almost square.

    Here is a short example: a dialog's button row with a destructive and
    a primary action, and an icon-only button beside them.

    \qml
    import Nemo
    import Nemo.Controls
    import QtQuick
    import QtQuick.Controls

    Row {
        spacing: Theme.itemSpacingSmall

        Button {
            text: qsTr("Cancel")
            destructive: true
            onClicked: dialog.reject()
        }
        Button {
            text: qsTr("Save")
            primary: true
            onClicked: dialog.accept()
        }
        Button {
            icon.source: "image://theme/gear"
            display: AbstractButton.IconOnly
            enabled: false
        }
    }
    \endqml
*/
Button {
    id: control

    /*!
        \qmlproperty bool Button::primary
        The main button of a view. Draws the accent gradient. The template's
        \c highlighted and \c checked properties select the same look.
    */
    property bool primary: false
    /*!
        \qmlproperty bool Button::backgrounded
        Draws a flat button in \c Theme.backgroundColor instead of a
        gradient, for buttons placed on a coloured surface.
    */
    property bool backgrounded: false
    /*!
        \qmlproperty bool Button::destructive
        Marks an action that discards or deletes. Draws the red gradient.
        Takes precedence over \c primary.
    */
    property bool destructive: false
    /*!
        \internal
        Resolved variant flags.
    */
    readonly property bool _accent: !destructive && (primary || highlighted || checked)
    readonly property bool _lightLabel: _accent || destructive || backgrounded
    readonly property bool _showIcon: icon.source != "" && display !== AbstractButton.TextOnly
    readonly property real _unit: Math.max(1, Math.round(implicitHeight * geometry.shadowOffset))

    implicitHeight: Theme.itemHeightMedium
    implicitWidth: display === AbstractButton.IconOnly ? Math.round(implicitHeight * geometry.iconOnlyWidth) : Math.max(implicitHeight, implicitContentWidth + leftPadding + rightPadding)
    leftPadding: display === AbstractButton.IconOnly ? 0 : _showIcon ? Math.round(implicitHeight * geometry.iconInset) : Math.round(implicitHeight * geometry.sidePadding)
    rightPadding: display === AbstractButton.IconOnly ? 0 : Math.round(implicitHeight * geometry.sidePadding)
    topPadding: 0
    bottomPadding: 0

    /*!
        \internal
        Proportions of the button as fractions of its height, on a grid of
        30 units.
    */
    QtObject {
        id: geometry

        readonly property real radius: 0.4
        readonly property real sidePadding: 20 / 30
        readonly property real iconSize: 16 / 30
        readonly property real iconInset: 10 / 30
        readonly property real iconGap: 8 / 30
        readonly property real iconOnlyWidth: 1.2
        readonly property real shadowOffset: 1 / 30
    }

    /*!
        \internal
        Colours, derived from the Theme. A coloured gradient starts at the
        variant colour; its other stops scale the HSL saturation and
        lightness of that colour. The destructive red is the one colour
        without a Theme token.
    */
    QtObject {
        id: colors

        readonly property real bottomSaturation: 1.095
        readonly property real bottomLightness: 0.612
        readonly property real pressedSaturation: 1.35
        readonly property real pressedTopLightness: 0.917
        readonly property real pressedBottomLightness: 0.356
        readonly property real lightBottom: 1.09
        readonly property real lightBottomDisabled: 1.04
        readonly property color destructive: "#e13535"
        readonly property color variant: control.destructive ? destructive : Theme.accentColor
        readonly property color light: Theme.backgroundAccentColor
        readonly property color shade: Theme.fillDarkColor
        // Light buttons run from light to slightly darker light. Coloured
        // buttons start at the variant colour, or at a deeper, more saturated
        // tone of it while pressed.
        readonly property color top: !control._lightLabel ? light : control.down ? derive(variant, pressedSaturation, pressedTopLightness) : variant
        readonly property color bottom: !control._lightLabel ? Qt.darker(light, control.enabled ? lightBottom : lightBottomDisabled) : control.down ? derive(variant, pressedSaturation, pressedBottomLightness) : derive(variant, bottomSaturation, bottomLightness)
        // Outline: from halfway between light and shade down to shade; a
        // pressed button uses shade down to a darker shade.
        readonly property color outlineTop: control.down ? shade : Qt.rgba((light.r + shade.r) / 2, (light.g + shade.g) / 2, (light.b + shade.b) / 2, 1)
        readonly property color outlineBottom: control.down ? Qt.darker(shade, 1.33) : shade
        readonly property real outlineOpacity: 0.25
        // Dark label on light buttons; light label on coloured ones, dimmed
        // while pressed.
        readonly property color label: !control._lightLabel ? shade : control.down ? Qt.darker(Theme.textColor, 1.5) : Theme.textColor

        function derive(c, saturation, lightness) {
            return Qt.hsla(c.hslHue, Math.min(1, c.hslSaturation * saturation), c.hslLightness * lightness, 1);
        }

    }

    background: Item {
        implicitWidth: Theme.itemHeightMedium
        implicitHeight: Theme.itemHeightMedium

        Rectangle {
            id: dropShadow

            width: parent.width
            height: parent.height
            y: control._unit
            radius: pill.radius
            color: colors.shade
            opacity: 0.2
            visible: !control.down && !control.backgrounded
        }

        Rectangle {
            id: pill

            anchors.fill: parent
            radius: Math.round(height * geometry.radius)
            color: control.backgrounded ? Theme.backgroundColor : "transparent"
            gradient: control.backgrounded ? null : outline

            // The pill holds the fill tinted with the translucent outline;
            // the face repeats the plain fill one unit inset, so the outline
            // shows as a ring along the inside edge.
            Gradient {
                id: outline

                GradientStop {
                    position: 0
                    color: Qt.tint(colors.top, Qt.rgba(colors.outlineTop.r, colors.outlineTop.g, colors.outlineTop.b, colors.outlineOpacity))
                }

                GradientStop {
                    position: 1
                    color: Qt.tint(colors.bottom, Qt.rgba(colors.outlineBottom.r, colors.outlineBottom.g, colors.outlineBottom.b, colors.outlineOpacity))
                }

            }

            Rectangle {
                id: face

                anchors.fill: parent
                anchors.margins: control._unit
                radius: parent.radius - control._unit
                visible: !control.backgrounded

                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: colors.top
                    }

                    GradientStop {
                        position: 1
                        color: colors.bottom
                    }

                }

            }

            Rectangle {
                id: stateOverlay

                anchors.fill: parent
                radius: parent.radius
                color: colors.shade
                opacity: control.down ? 0.33 : !control.enabled ? 0.1 : 0
            }

        }

    }

    contentItem: Item {
        implicitWidth: content.implicitWidth
        implicitHeight: content.implicitHeight

        // Centred, so a button wider than its content keeps icon and label
        // in the middle.
        Row {
            id: content

            anchors.centerIn: parent
            spacing: Math.round(control.implicitHeight * geometry.iconGap)

            NemoIcon {
                id: iconItem

                visible: control._showIcon
                source: control.icon.source
                width: Math.round(control.implicitHeight * geometry.iconSize)
                height: width
                sourceSize.width: width
                sourceSize.height: height
                color: colors.label
                opacity: label.opacity
                // Not an anchor: anchors round to whole pixels, which lifts
                // the icon half a pixel when its height and the row's differ
                // in parity.
                y: (parent.height - height) / 2
            }

            Item {
                id: labelBox

                visible: control.text !== "" && control.display !== AbstractButton.IconOnly
                implicitWidth: label.implicitWidth
                implicitHeight: label.implicitHeight
                anchors.verticalCenter: parent.verticalCenter

                Text {
                    id: labelShadow

                    y: control._unit
                    text: label.text
                    font: label.font
                    color: Qt.rgba(0, 0, 0, 0.11)
                    visible: control.enabled
                }

                Text {
                    id: label

                    text: control.text
                    color: colors.label
                    opacity: control.enabled ? 1 : control._lightLabel ? 0.5 : 0.33

                    // No styleName: Theme.fontStyleName would override the weight.
                    font {
                        pixelSize: Theme.fontSizeLarge
                        weight: Font.DemiBold
                        family: Theme.fontFamily
                    }

                }

            }

        }

    }

}
