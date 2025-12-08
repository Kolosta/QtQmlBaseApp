import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

ColumnLayout {
    spacing: ThemeManager.spacing.padding.xl.scaled
    
    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        color: ThemeManager.color.background.primary.defaultColor
        
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: ThemeManager.spacing.padding.xl.scaled
            spacing: ThemeManager.spacing.padding.xl.scaled
            
            // Page Title
            Text {
                text: "Theme Selector"
                font.family: ThemeManager.font.family.primary
                font.pixelSize: ThemeManager.font.size.heading1.scaled
                font.weight: ThemeManager.font.weight.bold
                color: ThemeManager.color.text.primary.defaultColor
            }
            
            // Theme Grid
            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                
                GridLayout {
                    width: parent.width
                    columns: 2
                    columnSpacing: ThemeManager.spacing.gap.md.scaled
                    rowSpacing: ThemeManager.spacing.gap.md.scaled
                    
                    Repeater {
                        model: ThemeManager.availableThemes
                        
                        Rectangle {
                            Layout.preferredWidth: 350
                            Layout.preferredHeight: 140
                            radius: ThemeManager.border.radius.md.scaled
                            color: ThemeManager.color.surface.primary.defaultColor
                            border.width: ThemeManager.currentTheme === modelData ? 
                                ThemeManager.border.width.md.scaled : 
                                ThemeManager.border.width.thin.scaled
                            border.color: ThemeManager.currentTheme === modelData ? 
                                ThemeManager.color.border.focus.defaultColor : 
                                ThemeManager.color.border.defaultColor.defaultColor
                            
                            Behavior on border.width {
                                NumberAnimation { duration: ThemeManager.transition.duration.fast }
                            }
                            
                            Behavior on border.color {
                                ColorAnimation { duration: ThemeManager.transition.duration.fast }
                            }
                            
                            ColumnLayout {
                                anchors.fill: parent
                                anchors.margins: ThemeManager.spacing.padding.lg.scaled
                                spacing: ThemeManager.spacing.padding.md.scaled
                                
                                Text {
                                    text: modelData
                                    font.family: ThemeManager.font.family.primary
                                    font.pixelSize: ThemeManager.font.size.text.lg.scaled
                                    font.weight: ThemeManager.font.weight.medium
                                    color: ThemeManager.color.text.primary.defaultColor
                                }
                                
                                Row {
                                    spacing: ThemeManager.spacing.gap.sm.scaled
                                    
                                    Rectangle {
                                        width: 50
                                        height: 50
                                        radius: ThemeManager.border.radius.sm.scaled
                                        color: ThemeManager.getThemePreviewPrimary(modelData)
                                    }
                                    
                                    Rectangle {
                                        width: 50
                                        height: 50
                                        radius: ThemeManager.border.radius.sm.scaled
                                        color: ThemeManager.getThemePreviewBackground(modelData)
                                        border.width: 1
                                        border.color: ThemeManager.color.border.defaultColor.defaultColor
                                    }
                                }
                                
                                Item { Layout.fillHeight: true }
                            }
                            
                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: ThemeManager.currentTheme = modelData
                            }
                        }
                    }
                }
            }
            
            // Import/Export Buttons
            RowLayout {
                Layout.fillWidth: true
                spacing: ThemeManager.spacing.gap.md.scaled
                
                Button {
                    text: "Import Theme"
                    
                    background: Rectangle {
                        color: ThemeManager.color.surface.primary.defaultColor
                        border.width: ThemeManager.border.width.thin.scaled
                        border.color: ThemeManager.color.border.defaultColor.defaultColor
                        radius: ThemeManager.border.radius.sm.scaled
                    }
                    
                    contentItem: Text {
                        text: parent.text
                        font.family: ThemeManager.font.family.primary
                        font.pixelSize: ThemeManager.font.size.text.md.scaled
                        color: ThemeManager.color.text.primary.defaultColor
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
                
                Button {
                    text: "Export Current Theme"
                    
                    background: Rectangle {
                        color: ThemeManager.color.surface.primary.defaultColor
                        border.width: ThemeManager.border.width.thin.scaled
                        border.color: ThemeManager.color.border.defaultColor.defaultColor
                        radius: ThemeManager.border.radius.sm.scaled
                    }
                    
                    contentItem: Text {
                        text: parent.text
                        font.family: ThemeManager.font.family.primary
                        font.pixelSize: ThemeManager.font.size.text.md.scaled
                        color: ThemeManager.color.text.primary.defaultColor
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
                
                Item { Layout.fillWidth: true }
            }
        }
    }
}