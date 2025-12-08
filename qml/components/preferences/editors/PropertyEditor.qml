import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

RowLayout {
    id: root
    
    property string label: ""
    property var targetObject: null      // L'objet à modifier (ex: ThemeManager.color.primary)
    property string targetProperty: ""   // La propriété à modifier (ex: "defaultColor")
    property var defaultValue: null      // Valeur par défaut du preset
    property string editorType: "color"  // "color", "int", "slider"
    
    spacing: ThemeManager.spacing.gap.md.scaled
    height: 40
    
    // Valeur actuelle (lecture directe depuis l'objet cible)
    readonly property var currentValue: targetObject ? targetObject[targetProperty] : null
    
    // Label
    Text {
        Layout.preferredWidth: 180
        text: root.label
        font.family: ThemeManager.font.family.primary
        font.pixelSize: ThemeManager.font.size.text.md.scaled
        color: ThemeManager.color.text.primary.defaultColor
        verticalAlignment: Text.AlignVCenter
    }
    
    // Editor
    Loader {
        Layout.fillWidth: true
        Layout.preferredHeight: 36
        
        sourceComponent: {
            switch (root.editorType) {
                case "color": return colorEditor
                case "int": return intEditor
                case "slider": return sliderEditor
                default: return null
            }
        }
    }
    
    // Reset Button
    Button {
        Layout.preferredWidth: 32
        Layout.preferredHeight: 32
        
        enabled: root.defaultValue !== null && root.currentValue !== root.defaultValue
        visible: root.defaultValue !== null
        
        text: "↺"
        
        ToolTip.visible: hovered && enabled
        ToolTip.text: "Reset to default (" + (root.defaultValue || "") + ")"
        
        background: Rectangle {
            color: parent.enabled ? 
                (parent.hovered ? ThemeManager.color.surface.hover.defaultColor : ThemeManager.color.surface.primary.defaultColor) :
                ThemeManager.color.surface.disabled.defaultColor
            border.width: ThemeManager.border.width.thin.scaled
            border.color: parent.enabled ?
                ThemeManager.color.border.defaultColor.defaultColor :
                ThemeManager.color.border.disabled.defaultColor
            radius: ThemeManager.border.radius.sm.scaled
            
            Behavior on color {
                ColorAnimation { duration: ThemeManager.transition.duration.fast }
            }
        }
        
        contentItem: Text {
            text: parent.text
            font.family: ThemeManager.font.family.primary
            font.pixelSize: ThemeManager.font.size.text.lg.scaled
            font.weight: ThemeManager.font.weight.bold
            color: parent.enabled ? 
                ThemeManager.color.text.primary.defaultColor : 
                ThemeManager.color.text.disabled.defaultColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        
        onClicked: {
            if (root.targetObject && root.defaultValue !== null) {
                root.targetObject[root.targetProperty] = root.defaultValue
                ThemeManager.saveCurrentThemeChanges()
            }
        }
    }
    
    // ========== COLOR EDITOR ==========
    Component {
        id: colorEditor
        
        Row {
            spacing: ThemeManager.spacing.gap.sm.scaled
            
            Rectangle {
                width: 36
                height: 36
                color: root.currentValue || "#000000"
                border.width: ThemeManager.border.width.thin.scaled
                border.color: ThemeManager.color.border.defaultColor.defaultColor
                radius: ThemeManager.border.radius.sm.scaled
                
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("Color picker not implemented yet for:", root.label)
                    }
                }
            }
            
            TextField {
                id: colorField
                width: 120
                height: 36
                text: root.currentValue ? root.currentValue.toString() : "#000000"
                font.family: ThemeManager.font.family.mono
                font.pixelSize: ThemeManager.font.size.text.sm.scaled
                color: ThemeManager.color.text.primary.defaultColor
                
                background: Rectangle {
                    color: ThemeManager.color.surface.primary.defaultColor
                    border.width: ThemeManager.border.width.thin.scaled
                    border.color: parent.activeFocus ? 
                        ThemeManager.color.border.focus.defaultColor : 
                        ThemeManager.color.border.defaultColor.defaultColor
                    radius: ThemeManager.border.radius.sm.scaled
                }
                
                onEditingFinished: {
                    if (root.targetObject) {
                        root.targetObject[root.targetProperty] = text
                        ThemeManager.saveCurrentThemeChanges()
                    }
                }
            }
        }
    }
    
    // ========== INT EDITOR ==========
    Component {
        id: intEditor
        
        SpinBox {
            id: intSpinBox
            from: 0
            to: 999
            value: root.currentValue || 0
            editable: true
            
            onValueModified: {
                if (root.targetObject) {
                    root.targetObject[root.targetProperty] = value
                    ThemeManager.saveCurrentThemeChanges()
                }
            }
            
            background: Rectangle {
                color: ThemeManager.color.surface.primary.defaultColor
                border.width: ThemeManager.border.width.thin.scaled
                border.color: parent.activeFocus ? 
                    ThemeManager.color.border.focus.defaultColor : 
                    ThemeManager.color.border.defaultColor.defaultColor
                radius: ThemeManager.border.radius.sm.scaled
            }
            
            contentItem: TextInput {
                text: parent.textFromValue(parent.value, parent.locale)
                font.family: ThemeManager.font.family.primary
                font.pixelSize: ThemeManager.font.size.text.md.scaled
                color: ThemeManager.color.text.primary.defaultColor
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                readOnly: !parent.editable
                validator: parent.validator
                inputMethodHints: Qt.ImhFormattedNumbersOnly
            }
        }
    }
    
    // ========== SLIDER EDITOR (pour scale) ==========
    Component {
        id: sliderEditor
        
        RowLayout {
            spacing: ThemeManager.spacing.gap.sm.scaled
            
            Slider {
                id: scaleSlider
                Layout.fillWidth: true
                
                from: 0.5
                to: 3.0
                stepSize: 0.05
                value: root.currentValue || 1.0
                
                onMoved: {
                    if (root.targetObject) {
                        root.targetObject[root.targetProperty] = value
                        ThemeManager.saveCurrentThemeChanges()
                    }
                }
                
                background: Rectangle {
                    x: scaleSlider.leftPadding
                    y: scaleSlider.topPadding + scaleSlider.availableHeight / 2 - height / 2
                    width: scaleSlider.availableWidth
                    height: 4
                    radius: 2
                    color: ThemeManager.color.surface.primary.defaultColor
                    
                    Rectangle {
                        width: scaleSlider.visualPosition * parent.width
                        height: parent.height
                        color: ThemeManager.color.primary.defaultColor
                        radius: parent.radius
                    }
                }
                
                handle: Rectangle {
                    x: scaleSlider.leftPadding + scaleSlider.visualPosition * (scaleSlider.availableWidth - width)
                    y: scaleSlider.topPadding + scaleSlider.availableHeight / 2 - height / 2
                    width: 18
                    height: 18
                    radius: 9
                    color: scaleSlider.pressed ? 
                        ThemeManager.color.primary.pressed : 
                        ThemeManager.color.primary.defaultColor
                    border.width: ThemeManager.border.width.thin.scaled
                    border.color: ThemeManager.color.border.defaultColor.defaultColor
                }
            }
            
            Text {
                Layout.preferredWidth: 60
                text: (root.currentValue || 1.0).toFixed(2) + "x"
                font.family: ThemeManager.font.family.mono
                font.pixelSize: ThemeManager.font.size.text.md.scaled
                color: ThemeManager.color.text.primary.defaultColor
                horizontalAlignment: Text.AlignRight
            }
        }
    }
}