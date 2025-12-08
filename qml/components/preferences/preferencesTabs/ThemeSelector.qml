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
        spacing: ThemeManager.sizes.spacingMedium
        topPadding: ThemeManager.sizes.spacingLarge
        
        Text {
            text: "Theme Selector"
            font.pixelSize: ThemeManager.sizes.fontLarge
            font.bold: true
            color: ThemeManager.colors.textPrimary
        }
        
        Text {
            text: "Select a pre-built theme for your application"
            font.pixelSize: ThemeManager.sizes.fontMedium
            color: ThemeManager.colors.textSecondary
        }
        
        Flow {
            id: themeFlow
            width: parent.width
            spacing: ThemeManager.sizes.spacingMedium
            
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
            
            Connections {
                target: ThemeManager
                function onThemePropertiesChanged() {
                    themeFlow.refreshCounter++
                }
            }
        }
    }
    
    component ThemeOption: Rectangle {
        id: themeOptionRoot
        property string themeName: ""
        property bool isSelected: false
        property int refreshTrigger: 0
        signal clicked()
        
        width: 140
        height: 110
        radius: ThemeManager.sizes.radiusMedium
        border.width: isSelected ? 3 : ThemeManager.sizes.borderThin
        border.color: isSelected ? ThemeManager.colors.accentBase : ThemeManager.colors.borderPrimary
        
        color: {
            var dummy = refreshTrigger;
            return ThemeManager.getThemePreviewBackground(themeName)
        }
        
        Behavior on border.width {
            NumberAnimation { duration: ThemeManager.sizes.animNormal }
        }
        
        Behavior on color {
            ColorAnimation { duration: ThemeManager.sizes.animNormal }
        }
        
        Column {
            anchors.centerIn: parent
            spacing: ThemeManager.sizes.spacingMedium
            
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
                    ColorAnimation { duration: ThemeManager.sizes.animNormal }
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
                font.pixelSize: ThemeManager.sizes.fontMedium
                font.bold: themeOptionRoot.isSelected
            }
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: themeOptionRoot.clicked()
        }
    }
}