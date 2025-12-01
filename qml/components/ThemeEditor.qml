import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQmlBaseApp.Core

ColumnLayout {
    id: root
    anchors.fill: parent
    spacing: 15
    
    // Fonction pour rafraîchir tous les PropertyEditor
    function refreshAllPropertyEditors() {
        // Parcourir tous les PropertyEditor et mettre à jour leur statut
        var items = [
            backgroundProp, surfaceProp, surfaceHoverProp, primaryProp, primaryHoverProp,
            textProp, textSecondaryProp, borderProp, accentProp,
            spacingSmallProp, spacingProp, spacingLargeProp,
            radiusSmallProp, radiusProp, radiusLargeProp,
            menuBarHeightProp, borderWidthProp
        ]
        
        for (var i = 0; i < items.length; i++) {
            if (items[i]) {
                items[i].updateModifiedStatus()
            }
        }
    }
    
    // Rafraîchir au montage du composant
    Component.onCompleted: {
        refreshAllPropertyEditors()
    }
    
    // Rafraîchir quand l'onglet devient visible
    onVisibleChanged: {
        if (visible) {
            refreshAllPropertyEditors()
        }
    }
    
    // Header with actions
    RowLayout {
        id: header
        Layout.fillWidth: true
        spacing: 10
        
        Text {
            Layout.fillWidth: true
            text: "Theme Editor - " + ThemeManager.currentTheme.charAt(0).toUpperCase() + ThemeManager.currentTheme.slice(1)
            font.pixelSize: ThemeManager.fontSizeTitle
            font.bold: true
            color: ThemeManager.text
        }
        
        Button {
            text: "Reset All"
            
            background: Rectangle {
                color: parent.pressed ? ThemeManager.primaryHover : 
                       parent.hovered ? ThemeManager.primary : ThemeManager.surface
                border.width: ThemeManager.borderWidth
                border.color: ThemeManager.border
                radius: ThemeManager.radius
            }
            
            contentItem: Text {
                text: parent.text
                color: ThemeManager.text
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: ThemeManager.fontSizeMedium
            }
            
            onClicked: resetAllDialog.open()
        }
        
        Button {
            text: "Import"
            
            background: Rectangle {
                color: parent.pressed ? ThemeManager.primaryHover : 
                       parent.hovered ? ThemeManager.primary : ThemeManager.surface
                border.width: ThemeManager.borderWidth
                border.color: ThemeManager.border
                radius: ThemeManager.radius
            }
            
            contentItem: Text {
                text: parent.text
                color: ThemeManager.text
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: ThemeManager.fontSizeMedium
            }
            
            onClicked: importFileDialog.open()
        }
        
        Button {
            text: "Export"
            
            background: Rectangle {
                color: parent.pressed ? ThemeManager.primaryHover : 
                       parent.hovered ? ThemeManager.primary : ThemeManager.surface
                border.width: ThemeManager.borderWidth
                border.color: ThemeManager.border
                radius: ThemeManager.radius
            }
            
            contentItem: Text {
                text: parent.text
                color: ThemeManager.text
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: ThemeManager.fontSizeMedium
            }
            
            onClicked: exportFileDialog.open()
        }
    }
    
    // Properties list in Flickable
    Rectangle {
        id: scrollContainer
        Layout.fillWidth: true
        Layout.fillHeight: true
        color: "transparent"

        Flickable {
            id: flick
            anchors.fill: parent
            contentWidth: parent.width
            contentHeight: column.height
            clip: true
            boundsBehavior: Flickable.StopAtBounds

            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AsNeeded
            }

            Column {
                id: column
                width: flick.width
                spacing: 0

                // Colors Section
                SectionHeader { text: "Colors" }

                PropertyEditor {
                    id: backgroundProp
                    width: parent.width
                    propertyKey: "background"
                    propertyLabel: "Background"
                    propertyValue: ThemeManager.background
                    propertyType: "color"
                    onValueChanged: function(newValue) {
                        ThemeManager.setProperty("background", newValue)
                    }
                    onResetRequested: function() {
                        ThemeManager.resetProperty("background")
                    }
                }

                PropertyEditor {
                    id: surfaceProp
                    width: parent.width
                    propertyKey: "surface"
                    propertyLabel: "Surface"
                    propertyValue: ThemeManager.surface
                    propertyType: "color"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("surface", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("surface") }
                }

                PropertyEditor {
                    id: surfaceHoverProp
                    width: parent.width
                    propertyKey: "surfaceHover"
                    propertyLabel: "Surface Hover"
                    propertyValue: ThemeManager.surfaceHover
                    propertyType: "color"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("surfaceHover", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("surfaceHover") }
                }

                PropertyEditor {
                    id: primaryProp
                    width: parent.width
                    propertyKey: "primary"
                    propertyLabel: "Primary"
                    propertyValue: ThemeManager.primary
                    propertyType: "color"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("primary", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("primary") }
                }

                PropertyEditor {
                    id: primaryHoverProp
                    width: parent.width
                    propertyKey: "primaryHover"
                    propertyLabel: "Primary Hover"
                    propertyValue: ThemeManager.primaryHover
                    propertyType: "color"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("primaryHover", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("primaryHover") }
                }

                PropertyEditor {
                    id: textProp
                    width: parent.width
                    propertyKey: "text"
                    propertyLabel: "Text"
                    propertyValue: ThemeManager.text
                    propertyType: "color"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("text", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("text") }
                }

                PropertyEditor {
                    id: textSecondaryProp
                    width: parent.width
                    propertyKey: "textSecondary"
                    propertyLabel: "Text Secondary"
                    propertyValue: ThemeManager.textSecondary
                    propertyType: "color"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("textSecondary", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("textSecondary") }
                }

                PropertyEditor {
                    id: borderProp
                    width: parent.width
                    propertyKey: "border"
                    propertyLabel: "Border"
                    propertyValue: ThemeManager.border
                    propertyType: "color"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("border", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("border") }
                }

                PropertyEditor {
                    id: accentProp
                    width: parent.width
                    propertyKey: "accent"
                    propertyLabel: "Accent"
                    propertyValue: ThemeManager.accent
                    propertyType: "color"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("accent", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("accent") }
                }

                // Spacing Section
                SectionHeader { text: "Spacing" }

                PropertyEditor {
                    id: spacingSmallProp
                    width: parent.width
                    propertyKey: "spacingSmall"
                    propertyLabel: "Small"
                    propertyValue: ThemeManager.spacingSmall
                    propertyType: "number"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("spacingSmall", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("spacingSmall") }
                }

                PropertyEditor {
                    id: spacingProp
                    width: parent.width
                    propertyKey: "spacing"
                    propertyLabel: "Normal"
                    propertyValue: ThemeManager.spacing
                    propertyType: "number"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("spacing", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("spacing") }
                }

                PropertyEditor {
                    id: spacingLargeProp
                    width: parent.width
                    propertyKey: "spacingLarge"
                    propertyLabel: "Large"
                    propertyValue: ThemeManager.spacingLarge
                    propertyType: "number"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("spacingLarge", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("spacingLarge") }
                }

                // Radius Section
                SectionHeader { text: "Border Radius" }

                PropertyEditor {
                    id: radiusSmallProp
                    width: parent.width
                    propertyKey: "radiusSmall"
                    propertyLabel: "Small"
                    propertyValue: ThemeManager.radiusSmall
                    propertyType: "number"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("radiusSmall", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("radiusSmall") }
                }

                PropertyEditor {
                    id: radiusProp
                    width: parent.width
                    propertyKey: "radius"
                    propertyLabel: "Normal"
                    propertyValue: ThemeManager.radius
                    propertyType: "number"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("radius", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("radius") }
                }

                PropertyEditor {
                    id: radiusLargeProp
                    width: parent.width
                    propertyKey: "radiusLarge"
                    propertyLabel: "Large"
                    propertyValue: ThemeManager.radiusLarge
                    propertyType: "number"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("radiusLarge", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("radiusLarge") }
                }

                // Other Dimensions
                SectionHeader { text: "Dimensions" }

                PropertyEditor {
                    id: menuBarHeightProp
                    width: parent.width
                    propertyKey: "menuBarHeight"
                    propertyLabel: "Menu Bar Height"
                    propertyValue: ThemeManager.menuBarHeight
                    propertyType: "number"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("menuBarHeight", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("menuBarHeight") }
                }

                PropertyEditor {
                    id: borderWidthProp
                    width: parent.width
                    propertyKey: "borderWidth"
                    propertyLabel: "Border Width"
                    propertyValue: ThemeManager.borderWidth
                    propertyType: "number"
                    onValueChanged: function(newValue) { ThemeManager.setProperty("borderWidth", newValue) }
                    onResetRequested: function() { ThemeManager.resetProperty("borderWidth") }
                }
            }
        }
    }

    
    // Section Header Component
    component SectionHeader: Rectangle {
        property string text: ""
        width: parent.width
        height: 35
        color: ThemeManager.surface
        
        Text {
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: parent.text
            font.pixelSize: ThemeManager.fontSizeMedium
            font.bold: true
            color: ThemeManager.primary
        }
        
        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: 1
            color: ThemeManager.border
        }
    }
    
    // Dialogs
    Dialog {
        id: resetAllDialog
        anchors.centerIn: parent
        title: "Reset All Properties"
        modal: true
        width: 350
        height: 150
        
        background: Rectangle {
            color: ThemeManager.surface
            border.width: ThemeManager.borderWidth
            border.color: ThemeManager.border
            radius: ThemeManager.radius
        }
        
        Column {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 20
            
            Text {
                text: "Are you sure you want to reset all theme properties to their original values?"
                color: ThemeManager.text
                wrapMode: Text.WordWrap
                width: parent.width
            }
            
            Row {
                anchors.right: parent.right
                spacing: 10
                
                Button {
                    text: "Cancel"
                    onClicked: resetAllDialog.close()
                    
                    background: Rectangle {
                        color: parent.pressed ? ThemeManager.surfaceHover : ThemeManager.surface
                        border.width: ThemeManager.borderWidth
                        border.color: ThemeManager.border
                        radius: ThemeManager.radiusSmall
                    }
                    
                    contentItem: Text {
                        text: parent.text
                        color: ThemeManager.text
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
                
                Button {
                    text: "Reset All"
                    onClicked: {
                        ThemeManager.resetAllProperties()
                        root.refreshAllPropertyEditors()
                        resetAllDialog.close()
                    }
                    
                    background: Rectangle {
                        color: parent.pressed ? ThemeManager.primaryHover : ThemeManager.primary
                        border.width: ThemeManager.borderWidth
                        border.color: ThemeManager.primary
                        radius: ThemeManager.radiusSmall
                    }
                    
                    contentItem: Text {
                        text: parent.text
                        color: "#ffffff"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }
    }
    
    FileDialog {
        id: importFileDialog
        title: "Import Theme"
        nameFilters: ["JSON files (*.json)"]
        fileMode: FileDialog.OpenFile
        onAccepted: {
            ThemeManager.importTheme(selectedFile.toString().replace("file://", ""))
            root.refreshAllPropertyEditors()
        }
    }
    
    FileDialog {
        id: exportFileDialog
        title: "Export Theme"
        nameFilters: ["JSON files (*.json)"]
        fileMode: FileDialog.SaveFile
        defaultSuffix: "json"
        onAccepted: {
            ThemeManager.exportTheme(selectedFile.toString().replace("file://", ""))
        }
    }
}