import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

Rectangle {
    id: root
    height: ThemeManager.components.menuBar.height.scaled
    color: ThemeManager.color.surface.primary.defaultColor
    
    signal preferencesRequested()
    
    // Global shortcuts
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
        anchors.leftMargin: ThemeManager.spacing.padding.sm.scaled
        spacing: ThemeManager.spacing.gap.sm.scaled
        
        // File Menu
        Button {
            height: parent.height
            text: "File"
            
            background: Rectangle {
                color: parent.hovered ? 
                    ThemeManager.color.surface.hover.defaultColor :
                    "transparent"
                
                Behavior on color {
                    ColorAnimation { duration: ThemeManager.transition.duration.fast }
                }
            }
            
            contentItem: Text {
                text: parent.text
                font.family: ThemeManager.font.family.primary
                font.pixelSize: ThemeManager.font.size.text.md.scaled
                font.weight: ThemeManager.font.weight.medium
                color: ThemeManager.color.text.primary.defaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            
            onClicked: fileMenu.popup(this, 0, height)
            
            Menu {
                id: fileMenu
                
                background: Rectangle {
                    implicitWidth: 250
                    color: ThemeManager.color.surface.primary.defaultColor
                    border.width: ThemeManager.border.width.thin.scaled
                    border.color: ThemeManager.color.border.defaultColor.defaultColor
                    radius: ThemeManager.border.radius.sm.scaled
                }
                
                MenuItem {
                    text: "Save"
                    onTriggered: console.log("Save clicked")
                    
                    background: Rectangle {
                        color: parent.highlighted ? 
                            ThemeManager.color.surface.hover.defaultColor :
                            ThemeManager.color.surface.primary.defaultColor
                        
                        Behavior on color {
                            ColorAnimation { duration: ThemeManager.transition.duration.fast }
                        }
                    }
                    
                    contentItem: RowLayout {
                        spacing: ThemeManager.spacing.padding.md.scaled
                        
                        Text {
                            Layout.fillWidth: true
                            text: parent.parent.text
                            font.family: ThemeManager.font.family.primary
                            font.pixelSize: ThemeManager.font.size.text.md.scaled
                            color: ThemeManager.color.text.primary.defaultColor
                        }
                        
                        Text {
                            text: KeymapManager.getShortcutDisplay("file.save")
                            font.family: ThemeManager.font.family.mono
                            font.pixelSize: ThemeManager.font.size.text.sm.scaled
                            color: ThemeManager.color.text.secondary.defaultColor
                        }
                    }
                }
                
                MenuSeparator {
                    contentItem: Rectangle {
                        implicitHeight: ThemeManager.border.width.thin.scaled
                        color: ThemeManager.color.border.defaultColor.defaultColor
                    }
                }
                
                MenuItem {
                    text: "Exit"
                    onTriggered: Application.quit()
                    
                    background: Rectangle {
                        color: parent.highlighted ? 
                            ThemeManager.color.surface.hover.defaultColor : 
                            ThemeManager.color.surface.primary.defaultColor
                        
                        Behavior on color {
                            ColorAnimation { duration: ThemeManager.transition.duration.fast }
                        }
                    }
                    
                    contentItem: RowLayout {
                        spacing: ThemeManager.spacing.padding.md.scaled
                        
                        Text {
                            Layout.fillWidth: true
                            text: parent.parent.text
                            font.family: ThemeManager.font.family.primary
                            font.pixelSize: ThemeManager.font.size.text.md.scaled
                            color: ThemeManager.color.text.primary.defaultColor
                        }
                        
                        Text {
                            text: KeymapManager.getShortcutDisplay("file.quit")
                            font.family: ThemeManager.font.family.mono
                            font.pixelSize: ThemeManager.font.size.text.sm.scaled
                            color: ThemeManager.color.text.secondary.defaultColor
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
                    ThemeManager.color.surface.hover.defaultColor :
                    "transparent"
                
                Behavior on color {
                    ColorAnimation { duration: ThemeManager.transition.duration.fast }
                }
            }
            
            contentItem: Text {
                text: parent.text
                font.family: ThemeManager.font.family.primary
                font.pixelSize: ThemeManager.font.size.text.md.scaled
                font.weight: ThemeManager.font.weight.medium
                color: ThemeManager.color.text.primary.defaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            
            onClicked: editMenu.popup(this, 0, height)
            
            Menu {
                id: editMenu
                
                background: Rectangle {
                    implicitWidth: 250
                    color: ThemeManager.color.surface.primary.defaultColor
                    border.width: ThemeManager.border.width.thin.scaled
                    border.color: ThemeManager.color.border.defaultColor.defaultColor
                    radius: ThemeManager.border.radius.sm.scaled
                }
                
                MenuItem {
                    text: "Preferences"
                    onTriggered: {
                        console.log("Preferences clicked")
                        root.preferencesRequested()
                    }
                    
                    background: Rectangle {
                        color: parent.highlighted ? 
                            ThemeManager.color.surface.hover.defaultColor : 
                            ThemeManager.color.surface.primary.defaultColor
                        
                        Behavior on color {
                            ColorAnimation { duration: ThemeManager.transition.duration.fast }
                        }
                    }
                    
                    contentItem: RowLayout {
                        spacing: ThemeManager.spacing.padding.md.scaled
                        
                        Text {
                            Layout.fillWidth: true
                            text: parent.parent.text
                            font.family: ThemeManager.font.family.primary
                            font.pixelSize: ThemeManager.font.size.text.md.scaled
                            color: ThemeManager.color.text.primary.defaultColor
                        }
                        
                        Text {
                            text: KeymapManager.getShortcutDisplay("edit.preferences")
                            font.family: ThemeManager.font.family.mono
                            font.pixelSize: ThemeManager.font.size.text.sm.scaled
                            color: ThemeManager.color.text.secondary.defaultColor
                        }
                    }
                }
            }
        }
    }
    
    // Bottom border
    Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: ThemeManager.border.width.thin.scaled
        color: ThemeManager.color.border.defaultColor.defaultColor
    }
}