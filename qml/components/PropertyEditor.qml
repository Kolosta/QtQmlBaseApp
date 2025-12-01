import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQmlBaseApp.Core

Rectangle {
    id: root
    height: 45
    color: "transparent"
    
    property string propertyKey: ""
    property string propertyLabel: ""
    property var propertyValue
    property string propertyType: "string"
    
    // Cache local de l'état "modifié" - ne se recalcule que sur demande
    property bool isModified: false
    
    signal valueChanged(var newValue)
    signal resetRequested()
    
    // Fonction pour mettre à jour le statut "modifié"
    function updateModifiedStatus() {
        isModified = ThemeManager.isPropertyModified(propertyKey)
    }
    
    // Mettre à jour seulement au chargement du composant
    Component.onCompleted: {
        updateModifiedStatus()
    }
    
    RowLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 10
        
        // Label
        Text {
            Layout.preferredWidth: 150
            text: root.propertyLabel
            color: root.isModified ? ThemeManager.accent : ThemeManager.text
            font.pixelSize: ThemeManager.fontSizeMedium
            font.bold: root.isModified
            elide: Text.ElideRight
        }
        
        // Editor based on type
        Loader {
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            
            sourceComponent: {
                switch(root.propertyType) {
                    case "color": return colorEditor
                    case "number": return numberEditor
                    case "boolean": return booleanEditor
                    default: return stringEditor
                }
            }
        }
        
        // Reset button
        Button {
            Layout.preferredWidth: 30
            Layout.preferredHeight: 30
            text: "↺"
            visible: root.isModified
            
            background: Rectangle {
                color: parent.hovered ? ThemeManager.surfaceHover : ThemeManager.surface
                border.width: ThemeManager.borderWidth
                border.color: ThemeManager.border
                radius: ThemeManager.radiusSmall
            }
            
            contentItem: Text {
                text: parent.text
                color: ThemeManager.text
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: ThemeManager.fontSizeLarge
            }
            
            onClicked: {
                root.resetRequested()
                root.updateModifiedStatus()
            }
        }
    }
    
    // Color editor
    Component {
        id: colorEditor
        
        Row {
            spacing: 5
            
            Rectangle {
                id: colorPreview
                width: 60
                height: 30
                color: root.propertyValue || "#000000"
                border.width: ThemeManager.borderWidth
                border.color: ThemeManager.border
                radius: ThemeManager.radiusSmall
                
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        customColorPicker.currentColor = root.propertyValue || "#000000"
                        customColorPicker.open(colorPreview)
                    }
                }
            }
            
            TextField {
                width: 100
                height: 30
                text: root.propertyValue ? root.propertyValue.toString() : ""
                font.pixelSize: ThemeManager.fontSizeSmall
                
                background: Rectangle {
                    color: ThemeManager.surface
                    border.width: ThemeManager.borderWidth
                    border.color: ThemeManager.border
                    radius: ThemeManager.radiusSmall
                }
                
                color: ThemeManager.text
                
                onEditingFinished: {
                    if (text.match(/^#[0-9A-Fa-f]{6}$/)) {
                        root.valueChanged(text)
                        root.updateModifiedStatus()
                    }
                }
            }
            
            CustomColorPicker {
                id: customColorPicker
                
                // Preview en temps réel pendant l'édition (pas de check isModified)
                Connections {
                    target: customColorPicker
                    function onCurrentColorChanged() {
                        if (customColorPicker.visible) {
                            root.valueChanged(customColorPicker.currentColor.toString())
                        }
                    }
                }
                
                // Vérifier isModified seulement à la validation finale
                onColorAccepted: function(finalColor) {
                    root.updateModifiedStatus()
                }
                
                onClosed: {
                    if (!accepted) {
                        // Annulation : restaurer la couleur initiale
                        root.valueChanged(initialColor.toString())
                    }
                    // Toujours mettre à jour le statut après fermeture
                    root.updateModifiedStatus()
                }
            }
        }
    }
    
    // Number editor
    Component {
        id: numberEditor
        
        SpinBox {
            from: 0
            to: 1000
            value: root.propertyValue || 0
            editable: true
            
            background: Rectangle {
                color: ThemeManager.surface
                border.width: ThemeManager.borderWidth
                border.color: ThemeManager.border
                radius: ThemeManager.radiusSmall
            }
            
            contentItem: TextInput {
                text: parent.value
                color: ThemeManager.text
                font.pixelSize: ThemeManager.fontSizeMedium
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                readOnly: !parent.editable
                validator: parent.validator
                inputMethodHints: Qt.ImhDigitsOnly
            }
            
            onValueModified: {
                root.valueChanged(value)
                root.updateModifiedStatus()
            }
        }
    }
    
    // Boolean editor
    Component {
        id: booleanEditor
        
        CheckBox {
            checked: root.propertyValue || false
            
            indicator: Rectangle {
                implicitWidth: 20
                implicitHeight: 20
                radius: ThemeManager.radiusSmall
                border.width: ThemeManager.borderWidth
                border.color: ThemeManager.border
                color: ThemeManager.surface
                
                Rectangle {
                    width: 12
                    height: 12
                    anchors.centerIn: parent
                    radius: ThemeManager.radiusSmall
                    color: ThemeManager.accent
                    visible: parent.parent.checked
                }
            }
            
            contentItem: Text {
                text: parent.checked ? "Yes" : "No"
                color: ThemeManager.text
                leftPadding: parent.indicator.width + 5
                verticalAlignment: Text.AlignVCenter
            }
            
            onToggled: {
                root.valueChanged(checked)
                root.updateModifiedStatus()
            }
        }
    }
    
    // String editor
    Component {
        id: stringEditor
        
        TextField {
            text: root.propertyValue || ""
            font.pixelSize: ThemeManager.fontSizeMedium
            
            background: Rectangle {
                color: ThemeManager.surface
                border.width: ThemeManager.borderWidth
                border.color: ThemeManager.border
                radius: ThemeManager.radiusSmall
            }
            
            color: ThemeManager.text
            
            onEditingFinished: {
                root.valueChanged(text)
                root.updateModifiedStatus()
            }
        }
    }
    
    // Separator
    Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
        color: ThemeManager.border
        opacity: 0.3
    }
}