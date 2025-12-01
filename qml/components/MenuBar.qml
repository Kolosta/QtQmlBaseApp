import QtQuick
import QtQuick.Controls
import QtQmlBaseApp.Core

Rectangle {
    id: root
    height: ThemeManager.menuBarHeight
    color: ThemeManager.surface
    
    signal preferencesRequested()
    
    Row {
        anchors.fill: parent
        spacing: 5
        
        // File Menu
        Button {
            height: parent.height
            text: "File"
            
            background: Rectangle {
                color: parent.hovered ? ThemeManager.surfaceHover : "transparent"
            }
            
            contentItem: Text {
                text: parent.text
                color: ThemeManager.text
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            
            onClicked: fileMenu.popup(this, 0, height)
            
            Menu {
                id: fileMenu
                
                background: Rectangle {
                    implicitWidth: 200
                    color: ThemeManager.surface
                    border.width: 1
                    border.color: ThemeManager.border
                }
                
                MenuItem {
                    text: "Save"
                    onTriggered: console.log("Save clicked")
                    
                    background: Rectangle {
                        color: parent.highlighted ? ThemeManager.surfaceHover : ThemeManager.surface
                    }
                    contentItem: Text {
                        text: parent.text
                        color: ThemeManager.text
                        leftPadding: 10
                    }
                }
                
                MenuSeparator {
                    contentItem: Rectangle {
                        implicitHeight: 1
                        color: ThemeManager.border
                    }
                }
                
                MenuItem {
                    text: "Exit"
                    onTriggered: Application.quit()
                    
                    background: Rectangle {
                        color: parent.highlighted ? ThemeManager.surfaceHover : ThemeManager.surface
                    }
                    contentItem: Text {
                        text: parent.text
                        color: ThemeManager.text
                        leftPadding: 10
                    }
                }
            }
        }
        
        // Edit Menu
        Button {
            height: parent.height
            text: "Edit"
            
            background: Rectangle {
                color: parent.hovered ? ThemeManager.surfaceHover : "transparent"
            }
            
            contentItem: Text {
                text: parent.text
                color: ThemeManager.text
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            
            onClicked: editMenu.popup(this, 0, height)
            
            Menu {
                id: editMenu
                
                background: Rectangle {
                    implicitWidth: 200
                    color: ThemeManager.surface
                    border.width: 1
                    border.color: ThemeManager.border
                }
                
                MenuItem {
                    text: "Preferences"
                    onTriggered: {
                        console.log("Preferences clicked")
                        root.preferencesRequested()
                    }
                    
                    background: Rectangle {
                        color: parent.highlighted ? ThemeManager.surfaceHover : ThemeManager.surface
                    }
                    contentItem: Text {
                        text: parent.text
                        color: ThemeManager.text
                        leftPadding: 10
                    }
                }
            }
        }
    }
    
    Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
        color: ThemeManager.border
    }
}