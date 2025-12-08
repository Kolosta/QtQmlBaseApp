import QtQuick
import QtQuick.Controls
import QtQmlBaseApp.Core

Button {
    id: root
    
    property bool isActive: false
    property string iconText: ""
    
    height: 54
    
    background: Rectangle {
        color: {
            if (root.isActive) return ThemeManager.color.primary.defaultColor
            if (root.hovered) return ThemeManager.color.surface.hover.defaultColor
            return "transparent"
        }
        
        Behavior on color {
            ColorAnimation { duration: ThemeManager.transition.duration.fast }
        }
        
        // Active indicator
        Rectangle {
            anchors.left: parent.left
            width: 4
            height: parent.height
            color: ThemeManager.color.accent.defaultColor
            opacity: root.isActive ? 1 : 0
            
            Behavior on opacity {
                NumberAnimation { duration: ThemeManager.transition.duration.fast }
            }
        }
    }
    
    contentItem: Row {
        spacing: ThemeManager.spacing.padding.md.scaled
        leftPadding: ThemeManager.spacing.padding.lg.scaled
        
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.iconText
            font.pixelSize: ThemeManager.font.size.text.lg.scaled
        }
        
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.text
            font.family: ThemeManager.font.family.primary
            font.pixelSize: ThemeManager.font.size.text.md.scaled
            font.weight: root.isActive ? 
                ThemeManager.font.weight.medium : 
                ThemeManager.font.weight.regular
            color: root.isActive ? 
                ThemeManager.color.text.onPrimary.defaultColor : 
                ThemeManager.color.text.primary.defaultColor
            
            Behavior on color {
                ColorAnimation { duration: ThemeManager.transition.duration.fast }
            }
        }
    }
}