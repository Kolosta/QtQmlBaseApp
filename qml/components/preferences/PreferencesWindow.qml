import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

Window {
    id: root
    width: 1100
    height: 750
    minimumWidth: 900
    minimumHeight: 600
    title: "Preferences"
    color: ThemeManager.color.background.primary.defaultColor
    modality: Qt.ApplicationModal
    
    property int currentPage: 0
    
    RowLayout {
        anchors.fill: parent
        spacing: 0
        
        // ===== SIDEBAR =====
        Rectangle {
            Layout.preferredWidth: ThemeManager.components.preferencesWindow.sidebarWidth.scaled
            Layout.fillHeight: true
            color: ThemeManager.color.background.secondary.defaultColor
            
            ColumnLayout {
                anchors.fill: parent
                spacing: 0
                
                // Header
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 70
                    color: "transparent"
                    
                    Text {
                        anchors.centerIn: parent
                        text: "Preferences"
                        font.family: ThemeManager.font.family.primary
                        font.pixelSize: ThemeManager.font.size.heading2.scaled
                        font.weight: ThemeManager.font.weight.bold
                        color: ThemeManager.color.text.primary.defaultColor
                    }
                }
                
                Rectangle {
                    Layout.fillWidth: true
                    height: ThemeManager.border.width.thin.scaled
                    color: ThemeManager.color.border.defaultColor.defaultColor
                }
                
                // Navigation Buttons
                PreferencesSidebarButton {
                    Layout.fillWidth: true
                    text: "Theme Preview"
                    iconText: "🎨"
                    isActive: root.currentPage === 0
                    onClicked: root.currentPage = 0
                }
                
                PreferencesSidebarButton {
                    Layout.fillWidth: true
                    text: "Theme Editor"
                    iconText: "✏️"
                    isActive: root.currentPage === 1
                    onClicked: root.currentPage = 1
                }
                
                PreferencesSidebarButton {
                    Layout.fillWidth: true
                    text: "Theme Selector"
                    iconText: "🔄"
                    isActive: root.currentPage === 2
                    onClicked: root.currentPage = 2
                }
                
                Item { Layout.fillHeight: true }
                
                // Footer - Current Theme
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    color: "transparent"
                    
                    ColumnLayout {
                        anchors.centerIn: parent
                        spacing: 4
                        
                        Text {
                            Layout.alignment: Qt.AlignHCenter
                            text: "Current Theme"
                            font.family: ThemeManager.font.family.primary
                            font.pixelSize: ThemeManager.font.size.text.xs.scaled
                            color: ThemeManager.color.text.secondary.defaultColor
                        }
                        
                        Text {
                            Layout.alignment: Qt.AlignHCenter
                            text: ThemeManager.currentTheme
                            font.family: ThemeManager.font.family.primary
                            font.pixelSize: ThemeManager.font.size.text.md.scaled
                            font.weight: ThemeManager.font.weight.medium
                            color: ThemeManager.color.primary.defaultColor
                        }
                    }
                }
            }
        }
        
        // ===== CONTENT AREA =====
        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: root.currentPage
            
            // Page 0: Theme Preview
            ThemePreviewPage {}
            
            // Page 1: Theme Editor
            ThemeEditorPage {}
            
            // Page 2: Theme Selector
            ThemeSelectorPage {}
        }
    }
}