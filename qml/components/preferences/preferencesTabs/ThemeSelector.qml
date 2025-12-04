import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

Item {
    id: root
    implicitHeight: content.height
    
    Column {
        id: content
        width: parent.width
        spacing: 15
        topPadding: 20
        
        Text {
            text: "Theme Selector"
            font.pixelSize: ThemeManager.fontSizeTitle
            font.bold: true
            color: ThemeManager.text
        }
        
        Text {
            text: "Select a pre-built theme for your application"
            font.pixelSize: ThemeManager.fontSizeMedium
            color: ThemeManager.textSecondary
        }
        
        Flow {
            id: themeFlow
            width: parent.width
            spacing: 15
            
            // Propriété pour forcer le rafraîchissement
            property int refreshCounter: 0
            
            Repeater {
                model: ThemeManager.availableThemes
                
                ThemeOption {
                    themeName: modelData
                    isSelected: ThemeManager.currentTheme === modelData
                    refreshTrigger: themeFlow.refreshCounter
                    onClicked: ThemeManager.currentTheme = modelData
                }
            }
            
            // Écouter les changements de propriétés du thème
            Connections {
                target: ThemeManager
                function onThemePropertiesChanged() {
                    themeFlow.refreshCounter++
                }
            }
        }
    }

    // Theme Option Component
    component ThemeOption: Rectangle {
        id: themeOptionRoot
        property string themeName: ""
        property bool isSelected: false
        property int refreshTrigger: 0
        signal clicked()
        
        width: 140
        height: 110
        radius: ThemeManager.radius
        border.width: isSelected ? 3 : ThemeManager.borderWidth
        border.color: isSelected ? ThemeManager.accent : ThemeManager.border
        
        color: {
            var dummy = refreshTrigger;
            return ThemeManager.getThemePreviewBackground(themeName)
        }
        
        Behavior on border.width {
            NumberAnimation { duration: ThemeManager.animationDuration }
        }
        
        Behavior on color {
            ColorAnimation { duration: ThemeManager.animationDuration }
        }
        
        Column {
            anchors.centerIn: parent
            spacing: 10
            
            Rectangle {
                width: 50
                height: 50
                radius: 25
                anchors.horizontalCenter: parent.horizontalCenter
                
                color: {
                    var dummy = themeOptionRoot.refreshTrigger;
                    return ThemeManager.getThemePreviewPrimary(themeOptionRoot.themeName)
                }
                
                Behavior on color {
                    ColorAnimation { duration: ThemeManager.animationDuration }
                }
            }
            
            Text {
                text: themeOptionRoot.themeName.charAt(0).toUpperCase() + themeOptionRoot.themeName.slice(1).replace(/_/g, ' ')
                anchors.horizontalCenter: parent.horizontalCenter
                color: {
                    var dummy = themeOptionRoot.refreshTrigger;
                    var bg = ThemeManager.getThemePreviewBackground(themeOptionRoot.themeName)
                    var luminance = (0.299 * bg.r + 0.587 * bg.g + 0.114 * bg.b)
                    return luminance > 0.5 ? "#1e1e1e" : "#ffffff"
                }
                font.pixelSize: ThemeManager.fontSizeMedium
                font.bold: themeOptionRoot.isSelected
            }
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: themeOptionRoot.clicked()
        }
    }
}