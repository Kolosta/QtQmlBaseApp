import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

ScrollView {
    clip: true
    
    ColumnLayout {
        width: parent.parent.width - 40
        spacing: ThemeManager.spacing.padding.xl.scaled
        anchors.margins: ThemeManager.spacing.padding.xl.scaled
        
        // Page Title
        Text {
            text: "Theme Preview"
            font.family: ThemeManager.font.family.primary
            font.pixelSize: ThemeManager.font.size.heading1.scaled
            font.weight: ThemeManager.font.weight.bold
            color: ThemeManager.color.text.primary.defaultColor
        }
        
        // Primary Colors
        PropertyGroup {
            title: "Primary Colors"
            content: Component {
                RowLayout {
                    spacing: ThemeManager.spacing.gap.md.scaled
                    
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 100
                        radius: ThemeManager.border.radius.md.scaled
                        color: ThemeManager.color.primary.defaultColor
                        
                        Text {
                            anchors.centerIn: parent
                            text: "Primary"
                            font.family: ThemeManager.font.family.primary
                            font.pixelSize: ThemeManager.font.size.text.lg.scaled
                            color: ThemeManager.color.text.onPrimary.defaultColor
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 100
                        radius: ThemeManager.border.radius.md.scaled
                        color: ThemeManager.color.secondary.defaultColor
                        
                        Text {
                            anchors.centerIn: parent
                            text: "Secondary"
                            font.family: ThemeManager.font.family.primary
                            font.pixelSize: ThemeManager.font.size.text.lg.scaled
                            color: ThemeManager.color.text.primary.defaultColor
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 100
                        radius: ThemeManager.border.radius.md.scaled
                        color: ThemeManager.color.accent.defaultColor
                        
                        Text {
                            anchors.centerIn: parent
                            text: "Accent"
                            font.family: ThemeManager.font.family.primary
                            font.pixelSize: ThemeManager.font.size.text.lg.scaled
                            color: ThemeManager.color.text.onPrimary.defaultColor
                        }
                    }
                }
            }
        }
        
        // Text Styles
        PropertyGroup {
            title: "Text Styles"
            content: Component {
                ColumnLayout {
                    spacing: ThemeManager.spacing.padding.sm.scaled
                    
                    Text {
                        text: "Text Primary - Main content"
                        font.family: ThemeManager.font.family.primary
                        font.pixelSize: ThemeManager.font.size.text.lg.scaled
                        color: ThemeManager.color.text.primary.defaultColor
                    }
                    
                    Text {
                        text: "Text Secondary - Descriptions and labels"
                        font.family: ThemeManager.font.family.primary
                        font.pixelSize: ThemeManager.font.size.text.md.scaled
                        color: ThemeManager.color.text.secondary.defaultColor
                    }
                    
                    Text {
                        text: "Text Disabled - Inactive elements"
                        font.family: ThemeManager.font.family.primary
                        font.pixelSize: ThemeManager.font.size.text.sm.scaled
                        color: ThemeManager.color.text.disabled.defaultColor
                    }
                }
            }
        }
        
        // Status Colors
        PropertyGroup {
            title: "Status Colors"
            content: Component {
                GridLayout {
                    columns: 4
                    columnSpacing: ThemeManager.spacing.gap.md.scaled
                    rowSpacing: ThemeManager.spacing.gap.md.scaled
                    
                    Repeater {
                        model: [
                            {name: "Success", color: ThemeManager.color.success.defaultColor},
                            {name: "Warning", color: ThemeManager.color.warning.defaultColor},
                            {name: "Error", color: ThemeManager.color.error.defaultColor},
                            {name: "Info", color: ThemeManager.color.info.defaultColor}
                        ]
                        
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 60
                            radius: ThemeManager.border.radius.sm.scaled
                            color: modelData.color
                            
                            Text {
                                anchors.centerIn: parent
                                text: modelData.name
                                font.family: ThemeManager.font.family.primary
                                font.pixelSize: ThemeManager.font.size.text.md.scaled
                                color: ThemeManager.color.text.onPrimary.defaultColor
                            }
                        }
                    }
                }
            }
        }
        
        // Surface States
        PropertyGroup {
            title: "Surface States"
            content: Component {
                RowLayout {
                    spacing: ThemeManager.spacing.gap.md.scaled
                    
                    Repeater {
                        model: [
                            {name: "Primary", color: ThemeManager.color.surface.primary.defaultColor},
                            {name: "Hover", color: ThemeManager.color.surface.hover.defaultColor},
                            {name: "Active", color: ThemeManager.color.surface.active.defaultColor},
                            {name: "Disabled", color: ThemeManager.color.surface.disabled.defaultColor}
                        ]
                        
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 70
                            radius: ThemeManager.border.radius.sm.scaled
                            color: modelData.color
                            border.width: ThemeManager.border.width.thin.scaled
                            border.color: ThemeManager.color.border.defaultColor.defaultColor
                            
                            Text {
                                anchors.centerIn: parent
                                text: modelData.name
                                font.family: ThemeManager.font.family.primary
                                font.pixelSize: ThemeManager.font.size.text.md.scaled
                                color: ThemeManager.color.text.primary.defaultColor
                            }
                        }
                    }
                }
            }
        }
        
        Item { Layout.fillHeight: true }
    }
}