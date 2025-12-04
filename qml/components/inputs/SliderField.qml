import QtQuick
import QtQuick.Controls
import QtQmlBaseApp.Core

// Composant réutilisable : Slider avec label et valeur intégrés
Rectangle {
    id: root
    height: 30
    color: ThemeManager.surface
    border.width: ThemeManager.borderWidth
    border.color: ThemeManager.border
    radius: ThemeManager.radiusSmall
    
    property string label: "Property"
    property real value: 0.0
    property real minValue: 0.0
    property real maxValue: 1.0
    property int decimals: 3
    
    signal valueModified(real newValue)
    
    // Partie remplie (primary)
    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: parent.border.width
        width: Math.max(0, (parent.width - 2 * parent.border.width) * ((root.value - root.minValue) / (root.maxValue - root.minValue)))
        color: ThemeManager.primary
        radius: ThemeManager.radiusSmall
        
        Behavior on width {
            NumberAnimation { duration: 50 }
        }
    }
    
    // Label à gauche
    Text {
        id: labelText
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        text: root.label
        color: ThemeManager.text
        font.pixelSize: ThemeManager.fontSizeSmall
        visible: !valueInput.visible
    }
    
    // Valeur à droite
    Text {
        id: valueText
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        text: root.value.toFixed(root.decimals)
        color: ThemeManager.text
        font.pixelSize: ThemeManager.fontSizeSmall
        visible: !valueInput.visible
    }
    
    // Champ de texte en plein écran (quand édition)
    TextField {
        id: valueInput
        anchors.fill: parent
        anchors.margins: parent.border.width
        visible: false
        horizontalAlignment: Text.AlignCenter
        font.pixelSize: ThemeManager.fontSizeSmall
        color: ThemeManager.text
        selectByMouse: true
        
        background: Rectangle {
            color: ThemeManager.surfaceHover
            border.width: ThemeManager.borderWidth
            border.color: ThemeManager.accent
            radius: ThemeManager.radiusSmall
        }
        
        validator: DoubleValidator {
            bottom: root.minValue
            top: root.maxValue
            decimals: root.decimals
            notation: DoubleValidator.StandardNotation
        }
        
        onEditingFinished: {
            var newValue = parseFloat(text)
            if (!isNaN(newValue)) {
                newValue = Math.max(root.minValue, Math.min(root.maxValue, newValue))
                root.value = newValue
                root.valueModified(newValue)
            }
            visible = false
        }
        
        Keys.onEscapePressed: {
            visible = false
            event.accepted = true
        }
        
        Keys.onReturnPressed: {
            editingFinished()
        }
    }
    
    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        
        function updateValue(mouse) {
            if (valueInput.visible) return
            
            var ratio = Math.max(0, Math.min(1, mouse.x / width))
            var newValue = root.minValue + ratio * (root.maxValue - root.minValue)
            root.value = newValue
            root.valueModified(newValue)
        }
        
        onPressed: function(mouse) { updateValue(mouse) }
        onPositionChanged: function(mouse) { if (pressed) updateValue(mouse) }
        
        onDoubleClicked: {
            valueInput.text = root.value.toFixed(root.decimals)
            valueInput.visible = true
            valueInput.forceActiveFocus()
            valueInput.selectAll()
        }
    }
}