import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQmlBaseApp.Core

Item {
    id: root
    implicitHeight: content.height
    
    Column {
        id: content
        width: parent.width
        spacing: 0
        topPadding: 20
        
        // ===== HEADER =====
        RowLayout {
            width: parent.width - 40
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            
            Text {
                Layout.fillWidth: true
                text: "Theme Editor - " + ThemeManager.currentTheme
                font.pixelSize: ThemeManager.font.size.xlarge
                font.weight: ThemeManager.font.weight.bold
                color: ThemeManager.font.color.primary
            }
            
            Button {
                text: "Reset"
                onClicked: ThemeManager.resetToDefaults()
                
                background: Rectangle {
                    color: parent.pressed ? "#c62828" : 
                           parent.hovered ? "#e53935" : 
                           ThemeManager.surface.color.primary
                    border.width: ThemeManager.border.width.thin
                    border.color: ThemeManager.border.color.primary
                    radius: ThemeManager.surface.radius.medium
                }
                
                contentItem: Text {
                    text: parent.text
                    color: ThemeManager.font.color.primary
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: ThemeManager.font.size.medium
                }
            }
            
            Button {
                text: "Export JSON"
                onClicked: exportDialog.open()
                
                background: Rectangle {
                    color: parent.pressed ? ThemeManager.color.accent : 
                           parent.hovered ? Qt.lighter(ThemeManager.color.accent, 1.2) : 
                           ThemeManager.surface.color.primary
                    border.width: ThemeManager.border.width.thin
                    border.color: ThemeManager.border.color.primary
                    radius: ThemeManager.surface.radius.medium
                }
                
                contentItem: Text {
                    text: parent.text
                    color: ThemeManager.font.color.primary
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: ThemeManager.font.size.medium
                }
            }
            
            Button {
                text: "Import JSON"
                onClicked: importDialog.open()
                
                background: Rectangle {
                    color: parent.hovered ? ThemeManager.surface.color.primary : "transparent"
                    border.width: ThemeManager.border.width.thin
                    border.color: ThemeManager.border.color.primary
                    radius: ThemeManager.surface.radius.medium
                }
                
                contentItem: Text {
                    text: parent.text
                    color: ThemeManager.font.color.primary
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: ThemeManager.font.size.medium
                }
            }
        }
        
        Item { width: 1; height: 20 }
        
        // ===== SCALE SLIDER =====
        ComponentSection {
            title: "Resolution Scale"
            collapsed: false
            
            Column {
                width: parent.width
                spacing: ThemeManager.surface.spacing.medium
                
                Row {
                    width: parent.width
                    spacing: 10
                    
                    Text {
                        text: "Scale: " + (ThemeManager.scale * 100).toFixed(0) + "%"
                        color: ThemeManager.font.color.primary
                        font.pixelSize: ThemeManager.font.size.medium
                    }
                }
                
                Slider {
                    id: scaleSlider
                    width: parent.width
                    from: 0.5
                    to: 3.0
                    value: ThemeManager.scale
                    stepSize: 0.05
                    
                    onMoved: {
                        ThemeManager.scale = value
                    }
                    
                    background: Rectangle {
                        x: scaleSlider.leftPadding
                        y: scaleSlider.topPadding + scaleSlider.availableHeight / 2 - height / 2
                        width: scaleSlider.availableWidth
                        height: 4
                        radius: 2
                        color: ThemeManager.surface.color.primary
                        
                        Rectangle {
                            width: scaleSlider.visualPosition * parent.width
                            height: parent.height
                            color: ThemeManager.color.accent
                            radius: 2
                        }
                    }
                    
                    handle: Rectangle {
                        x: scaleSlider.leftPadding + scaleSlider.visualPosition * (scaleSlider.availableWidth - width)
                        y: scaleSlider.topPadding + scaleSlider.availableHeight / 2 - height / 2
                        width: 20
                        height: 20
                        radius: 10
                        color: scaleSlider.pressed ? Qt.darker(ThemeManager.color.accent, 1.2) : ThemeManager.color.accent
                        border.color: ThemeManager.border.color.primary
                        border.width: ThemeManager.border.width.thin
                    }
                }
            }
        }
        
        Item { width: 1; height: 20 }
        
        // ===== BASE COLORS =====
        ComponentSection {
            title: "Base Colors"
            collapsed: false
            
            Column {
                width: parent.width
                spacing: ThemeManager.surface.spacing.small
                
                ColorPropertyRow {
                    label: "Primary"
                    color: ThemeManager.color.primary
                    onColorChanged: function(newColor) {
                        ThemeManager.color.primary = newColor
                    }
                }
                
                ColorPropertyRow {
                    label: "Secondary"
                    color: ThemeManager.color.secondary
                    onColorChanged: function(newColor) {
                        ThemeManager.color.secondary = newColor
                    }
                }
                
                ColorPropertyRow {
                    label: "Tertiary"
                    color: ThemeManager.color.tertiary
                    onColorChanged: function(newColor) {
                        ThemeManager.color.tertiary = newColor
                    }
                }
                
                ColorPropertyRow {
                    label: "Accent"
                    color: ThemeManager.color.accent
                    onColorChanged: function(newColor) {
                        ThemeManager.color.accent = newColor
                    }
                }
            }
        }
        
        // ===== TEXT COLORS =====
        ComponentSection {
            title: "Text Colors"
            
            Column {
                width: parent.width
                spacing: ThemeManager.surface.spacing.small
                
                ColorPropertyRow {
                    label: "Primary Text"
                    color: ThemeManager.color.textPrimary
                    onColorChanged: function(newColor) {
                        ThemeManager.color.textPrimary = newColor
                    }
                }
                
                ColorPropertyRow {
                    label: "Secondary Text"
                    color: ThemeManager.color.textSecondary
                    onColorChanged: function(newColor) {
                        ThemeManager.color.textSecondary = newColor
                    }
                }
                
                ColorPropertyRow {
                    label: "Tertiary Text"
                    color: ThemeManager.color.textTertiary
                    onColorChanged: function(newColor) {
                        ThemeManager.color.textTertiary = newColor
                    }
                }
                
                ColorPropertyRow {
                    label: "Disabled Text"
                    color: ThemeManager.color.textDisabled
                    onColorChanged: function(newColor) {
                        ThemeManager.color.textDisabled = newColor
                    }
                }
            }
        }
        
        // ===== STATUS COLORS =====
        ComponentSection {
            title: "Status Colors"
            
            Column {
                width: parent.width
                spacing: ThemeManager.surface.spacing.small
                
                ColorPropertyRow {
                    label: "Success"
                    color: ThemeManager.color.success
                    onColorChanged: function(newColor) {
                        ThemeManager.color.success = newColor
                    }
                }
                
                ColorPropertyRow {
                    label: "Warning"
                    color: ThemeManager.color.warning
                    onColorChanged: function(newColor) {
                        ThemeManager.color.warning = newColor
                    }
                }
                
                ColorPropertyRow {
                    label: "Error"
                    color: ThemeManager.color.error
                    onColorChanged: function(newColor) {
                        ThemeManager.color.error = newColor
                    }
                }
                
                ColorPropertyRow {
                    label: "Info"
                    color: ThemeManager.color.info
                    onColorChanged: function(newColor) {
                        ThemeManager.color.info = newColor
                    }
                }
            }
        }
        
        Item { width: 1; height: 40 }
    }
    
    // ===== COLOR PROPERTY ROW =====
    component ColorPropertyRow: Rectangle {
        property string label
        property color color
        signal colorChanged(color newColor)
        
        width: parent.width
        height: 40
        color: "transparent"
        
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 15
            anchors.rightMargin: 15
            spacing: 10
            
            Text {
                Layout.preferredWidth: 150
                text: parent.parent.label
                color: ThemeManager.font.color.primary
                font.pixelSize: ThemeManager.font.size.medium
            }
            
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 30
                color: parent.parent.color
                border.width: ThemeManager.border.width.thin
                border.color: ThemeManager.border.color.primary
                radius: ThemeManager.surface.radius.small
                
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        colorDialog.selectedColor = parent.parent.parent.color
                        colorDialog.open()
                    }
                }
                
                ColorDialog {
                    id: colorDialog
                    onAccepted: {
                        parent.parent.parent.colorChanged(selectedColor)
                    }
                }
            }
            
            Text {
                Layout.preferredWidth: 80
                text: parent.parent.color
                color: ThemeManager.font.color.secondary
                font.pixelSize: ThemeManager.font.size.small
                font.family: "monospace"
            }
        }
    }
    
    // ===== DIALOGS =====
    FileDialog {
        id: exportDialog
        title: "Export Theme"
        fileMode: FileDialog.SaveFile
        defaultSuffix: "json"
        nameFilters: ["JSON files (*.json)"]
        
        onAccepted: {
            ThemeManager.exportToJson(selectedFile)
        }
    }
    
    FileDialog {
        id: importDialog
        title: "Import Theme"
        fileMode: FileDialog.OpenFile
        nameFilters: ["JSON files (*.json)"]
        
        onAccepted: {
            ThemeManager.importFromJson(selectedFile)
        }
    }
}