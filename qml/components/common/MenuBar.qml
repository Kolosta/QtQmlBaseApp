import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

Rectangle {
    id: root
    height: 40
    color: ThemeManager.surface.color.surfPrimary
    
    signal preferencesRequested()
    
    // Global shortcuts handler
    Shortcut {
        sequence: KeymapManager.getShortcut("file.save")
        onActivated: console.log("Save triggered")
    }
    
    Shortcut {
        sequence: KeymapManager.getShortcut("file.quit")
        onActivated: Application.quit()
    }
    
    Shortcut {
        sequence: KeymapManager.getShortcut("edit.preferences")
        onActivated: root.preferencesRequested()
    }
    
    Row {
        anchors.fill: parent
        spacing: ThemeManager.surface.spacingMedium
        
        // File Menu
        Button {
            height: parent.height
            text: "File"
            
            background: Rectangle {
                color: parent.hovered ? 
                    ThemeManager.surface.color.surfHover :
                    "transparent"
            }
            
            contentItem: Text {
                text: parent.text
                color: ThemeManager.font.color.textPrimary
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: ThemeManager.font.sizeMedium
                font.weight: ThemeManager.font.weight.medium
            }
            
            onClicked: fileMenu.popup(this, 0, height)
            
            Menu {
                id: fileMenu
                
                background: Rectangle {
                    implicitWidth: 250
                    color: ThemeManager.surface.color.surfPrimary
                    border.width: ThemeManager.border.widthThin
                    border.color: ThemeManager.border.color.borderPrimary
                    radius: ThemeManager.surface.radiusSmall
                }
                
                MenuItem {
                    text: "Save"
                    onTriggered: console.log("Save clicked")
                    
                    background: Rectangle {
                        color: parent.highlighted ? 
                            ThemeManager.surface.color.surfHover :
                            ThemeManager.surface.color.surfPrimary
                    }
                    
                    contentItem: RowLayout {
                        spacing: ThemeManager.surface.spacingMedium
                        
                        Text {
                            Layout.fillWidth: true
                            text: parent.parent.text
                            color: ThemeManager.font.color.textPrimary
                            font.pixelSize: ThemeManager.font.sizeMedium
                        }
                        
                        Text {
                            text: KeymapManager.getShortcutDisplay("file.save")
                            color: ThemeManager.font.color.textSecondary
                            font.pixelSize: ThemeManager.font.sizeSmall
                        }
                    }
                }
                
                MenuSeparator {
                    contentItem: Rectangle {
                        implicitHeight: ThemeManager.border.widthThin
                        color: ThemeManager.border.color.borderPrimary
                    }
                }
                
                MenuItem {
                    text: "Exit"
                    onTriggered: Application.quit()
                    
                    background: Rectangle {
                        color: parent.highlighted ? 
                            ThemeManager.surface.color.surfHover : 
                            ThemeManager.surface.color.surfPrimary
                    }
                    
                    contentItem: RowLayout {
                        spacing: ThemeManager.surface.spacingMedium
                        
                        Text {
                            Layout.fillWidth: true
                            text: parent.parent.text
                            color: ThemeManager.font.color.textPrimary
                            font.pixelSize: ThemeManager.font.sizeMedium
                        }
                        
                        Text {
                            text: KeymapManager.getShortcutDisplay("file.quit")
                            color: ThemeManager.font.color.textSecondary
                            font.pixelSize: ThemeManager.font.sizeSmall
                        }
                    }
                }
            }
        }
        
        // Edit Menu
        Button {
            height: parent.height
            text: "Edit"
            
            background: Rectangle {
                color: parent.hovered ? 
                    ThemeManager.surface.color.surfHover :
                    "transparent"
            }
            
            contentItem: Text {
                text: parent.text
                color: ThemeManager.font.color.textPrimary
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: ThemeManager.font.sizeMedium
                font.weight: ThemeManager.font.weight.medium
            }
            
            onClicked: editMenu.popup(this, 0, height)
            
            Menu {
                id: editMenu
                
                background: Rectangle {
                    implicitWidth: 250
                    color: ThemeManager.surface.color.surfPrimary
                    border.width: ThemeManager.border.widthThin
                    border.color: ThemeManager.border.color.borderPrimary
                    radius: ThemeManager.surface.radiusSmall
                }
                
                MenuItem {
                    text: "Preferences"
                    onTriggered: {
                        console.log("Preferences clicked")
                        root.preferencesRequested()
                    }
                    
                    background: Rectangle {
                        color: parent.highlighted ? 
                            ThemeManager.surface.color.surfHover : 
                            ThemeManager.surface.color.surfPrimary
                    }
                    
                    contentItem: RowLayout {
                        spacing: ThemeManager.surface.spacingMedium
                        
                        Text {
                            Layout.fillWidth: true
                            text: parent.parent.text
                            color: ThemeManager.font.color.textPrimary
                            font.pixelSize: ThemeManager.font.sizeMedium
                        }
                        
                        Text {
                            text: KeymapManager.getShortcutDisplay("edit.preferences")
                            color: ThemeManager.font.color.textSecondary
                            font.pixelSize: ThemeManager.font.sizeSmall
                        }
                    }
                }
            }
        }
    }
    
    Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: ThemeManager.border.widthThin
        color: ThemeManager.border.color.borderPrimary
    }
}