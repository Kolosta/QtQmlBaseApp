import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core
import "../editors"

ScrollView {
    clip: true
    
    ColumnLayout {
        width: parent.parent.width - 40
        spacing: ThemeManager.spacing.padding.xl.scaled
        anchors.margins: ThemeManager.spacing.padding.xl.scaled
        
        // Page Title
        Text {
            text: "Theme Editor"
            font.family: ThemeManager.font.family.primary
            font.pixelSize: ThemeManager.font.size.heading1.scaled
            font.weight: ThemeManager.font.weight.bold
            color: ThemeManager.color.text.primary.defaultColor
        }
        
        // Info message
        Rectangle {
            Layout.fillWidth: true
            height: 40
            radius: ThemeManager.border.radius.sm.scaled
            color: ThemeManager.color.info.defaultColor
            opacity: 0.2
            
            Text {
                anchors.centerIn: parent
                text: "✓ Changes are saved automatically"
                font.family: ThemeManager.font.family.primary
                font.pixelSize: ThemeManager.font.size.text.sm.scaled
                font.weight: ThemeManager.font.weight.medium
                color: ThemeManager.color.text.primary.defaultColor
            }
        }
        
        // ===== GLOBAL SETTINGS =====
        PropertyGroup {
            title: "Global Settings"
            content: Component {
                ColumnLayout {
                    spacing: ThemeManager.spacing.padding.md.scaled
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "UI Scale"
                        targetObject: ThemeManager
                        targetProperty: "scale"
                        defaultValue: 1.0
                        editorType: "slider"
                    }
                }
            }
        }
        
        // ===== PRIMARY COLORS =====
        PropertyGroup {
            title: "Primary Colors"
            content: Component {
                ColumnLayout {
                    spacing: ThemeManager.spacing.padding.md.scaled
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Primary Default"
                        targetObject: ThemeManager.color.primary
                        targetProperty: "defaultColor"
                        editorType: "color"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Primary Hover"
                        targetObject: ThemeManager.color.primary
                        targetProperty: "hover"
                        editorType: "color"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Accent Default"
                        targetObject: ThemeManager.color.accent
                        targetProperty: "defaultColor"
                        editorType: "color"
                    }
                }
            }
        }
        
        // ===== BACKGROUND COLORS =====
        PropertyGroup {
            title: "Background Colors"
            content: Component {
                ColumnLayout {
                    spacing: ThemeManager.spacing.padding.md.scaled
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Background Primary"
                        targetObject: ThemeManager.color.background.primary
                        targetProperty: "defaultColor"
                        editorType: "color"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Background Secondary"
                        targetObject: ThemeManager.color.background.secondary
                        targetProperty: "defaultColor"
                        editorType: "color"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Surface Primary"
                        targetObject: ThemeManager.color.surface.primary
                        targetProperty: "defaultColor"
                        editorType: "color"
                    }
                }
            }
        }
        
        // ===== TEXT COLORS =====
        PropertyGroup {
            title: "Text Colors"
            content: Component {
                ColumnLayout {
                    spacing: ThemeManager.spacing.padding.md.scaled
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Text Primary"
                        targetObject: ThemeManager.color.text.primary
                        targetProperty: "defaultColor"
                        editorType: "color"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Text Secondary"
                        targetObject: ThemeManager.color.text.secondary
                        targetProperty: "defaultColor"
                        editorType: "color"
                    }
                }
            }
        }
        
        // ===== STATUS COLORS =====
        PropertyGroup {
            title: "Status Colors"
            content: Component {
                ColumnLayout {
                    spacing: ThemeManager.spacing.padding.md.scaled
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Success"
                        targetObject: ThemeManager.color.success
                        targetProperty: "defaultColor"
                        editorType: "color"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Warning"
                        targetObject: ThemeManager.color.warning
                        targetProperty: "defaultColor"
                        editorType: "color"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Error"
                        targetObject: ThemeManager.color.error
                        targetProperty: "defaultColor"
                        editorType: "color"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Info"
                        targetObject: ThemeManager.color.info
                        targetProperty: "defaultColor"
                        editorType: "color"
                    }
                }
            }
        }
        
        // ===== COMPONENT OVERRIDES - MENUBAR =====
        PropertyGroup {
            title: "Component Overrides - MenuBar"
            content: Component {
                ColumnLayout {
                    spacing: ThemeManager.spacing.padding.md.scaled
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "MenuBar Height"
                        targetObject: ThemeManager.components.menuBar.height
                        targetProperty: "value"
                        defaultValue: 40
                        editorType: "int"
                    }
                }
            }
        }
        
        // ===== COMPONENT OVERRIDES - BUTTON =====
        PropertyGroup {
            title: "Component Overrides - Button"
            content: Component {
                ColumnLayout {
                    spacing: ThemeManager.spacing.padding.md.scaled
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Button Min Width"
                        targetObject: ThemeManager.components.button.minWidth
                        targetProperty: "value"
                        defaultValue: 80
                        editorType: "int"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Button Min Height"
                        targetObject: ThemeManager.components.button.minHeight
                        targetProperty: "value"
                        defaultValue: 32
                        editorType: "int"
                    }
                }
            }
        }
        
        // ===== SPACING =====
        PropertyGroup {
            title: "Spacing - Padding"
            content: Component {
                ColumnLayout {
                    spacing: ThemeManager.spacing.padding.md.scaled
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Padding Small"
                        targetObject: ThemeManager.spacing.padding.sm
                        targetProperty: "value"
                        defaultValue: 8
                        editorType: "int"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Padding Medium"
                        targetObject: ThemeManager.spacing.padding.md
                        targetProperty: "value"
                        defaultValue: 12
                        editorType: "int"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Padding Large"
                        targetObject: ThemeManager.spacing.padding.lg
                        targetProperty: "value"
                        defaultValue: 16
                        editorType: "int"
                    }
                }
            }
        }
        
        // ===== BORDER =====
        PropertyGroup {
            title: "Border"
            content: Component {
                ColumnLayout {
                    spacing: ThemeManager.spacing.padding.md.scaled
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Border Width Thin"
                        targetObject: ThemeManager.border.width.thin
                        targetProperty: "value"
                        defaultValue: 1
                        editorType: "int"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Border Radius Small"
                        targetObject: ThemeManager.border.radius.sm
                        targetProperty: "value"
                        defaultValue: 4
                        editorType: "int"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Border Radius Medium"
                        targetObject: ThemeManager.border.radius.md
                        targetProperty: "value"
                        defaultValue: 8
                        editorType: "int"
                    }
                }
            }
        }
        
        // ===== FONT SIZES =====
        PropertyGroup {
            title: "Font Sizes"
            content: Component {
                ColumnLayout {
                    spacing: ThemeManager.spacing.padding.md.scaled
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Text Small"
                        targetObject: ThemeManager.font.size.text.sm
                        targetProperty: "value"
                        defaultValue: 13
                        editorType: "int"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Text Medium"
                        targetObject: ThemeManager.font.size.text.md
                        targetProperty: "value"
                        defaultValue: 15
                        editorType: "int"
                    }
                    
                    PropertyEditor {
                        Layout.fillWidth: true
                        label: "Text Large"
                        targetObject: ThemeManager.font.size.text.lg
                        targetProperty: "value"
                        defaultValue: 18
                        editorType: "int"
                    }
                }
            }
        }
        
        Item { Layout.fillHeight: true }
    }
}