import QtQuick
import QtQuick.Layouts
import QtQmlBaseApp.Core

Item {
    id: valueBar
    property real hue: 0.0
    property real saturation: 1.0
    property real value: 1.0

    signal valueUpdated(real newValue)

    Layout.preferredWidth: 30
    Layout.preferredHeight: 180

    Rectangle {
        anchors.fill: parent
        radius: ThemeManager.radiusSmall
        border.width: ThemeManager.borderWidth
        border.color: ThemeManager.border

        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.hsva(valueBar.hue, valueBar.saturation, 1.0, 1) }
            GradientStop { position: 1.0; color: Qt.hsva(valueBar.hue, valueBar.saturation, 0.0, 1) }
        }

        Rectangle {
            width: parent.width
            height: 4
            y: (1 - valueBar.value) * (parent.height - height)
            color: "white"
            border.width: 1
            border.color: "black"
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent

            function updateValue(mouse) {
                var ratio = 1 - Math.max(0, Math.min(1, mouse.y / height))
                valueBar.value = ratio
                valueBar.valueUpdated(ratio) // Émettre le signal renommé
            }

            onPressed: updateValue(mouse)
            onPositionChanged: if (pressed) updateValue(mouse)
        }
    }
}