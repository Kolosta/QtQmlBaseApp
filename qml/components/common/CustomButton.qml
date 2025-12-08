import QtQuick
import QtQuick.Controls
import QtQmlBaseApp.Core

// CustomButton.qml - Bouton stylisé avec le thème
Button {
    id: root
    
    property bool isPrimary: false
    
    implicitWidth: Math.max(ThemeManager.components.button.minWidth.scaled, contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: ThemeManager.components.button.minHeight.scaled
    
    leftPadding: ThemeManager.spacing.padding.md.scaled
    rightPadding: ThemeManager.spacing.padding.md.scaled
    
    background: Rectangle {
        color: {
            if (!root.enabled) {
                return ThemeManager.color.surface.disabled.defaultColor
            }
            if (root.isPrimary) {
                if (root.pressed) return ThemeManager.color.primary.pressed
                if (root.hovered) return ThemeManager.color.primary.hover
                return ThemeManager.color.primary.defaultColor
            } else {
                if (root.pressed) return ThemeManager.color.surface.active.defaultColor
                if (root.hovered) return ThemeManager.color.surface.hover.defaultColor
                return ThemeManager.color.surface.primary.defaultColor
            }
        }
        
        border.width: root.isPrimary ? 0 : ThemeManager.border.width.thin.scaled
        border.color: {
            if (!root.enabled) return ThemeManager.color.border.disabled.defaultColor
            if (root.activeFocus) return ThemeManager.color.border.focus.defaultColor
            return ThemeManager.color.border.defaultColor.defaultColor
        }
        
        radius: ThemeManager.border.radius.sm.scaled
        
        Behavior on color {
            ColorAnimation { duration: ThemeManager.transition.duration.fast }
        }
        
        Behavior on border.color {
            ColorAnimation { duration: ThemeManager.transition.duration.fast }
        }
    }
    
    contentItem: Text {
        text: root.text
        font.family: ThemeManager.font.family.primary
        font.pixelSize: ThemeManager.font.size.text.md.scaled
        font.weight: ThemeManager.font.weight.medium
        color: {
            if (!root.enabled) return ThemeManager.color.text.disabled.defaultColor
            if (root.isPrimary) return ThemeManager.color.text.onPrimary.defaultColor
            return ThemeManager.color.text.primary.defaultColor
        }
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        
        Behavior on color {
            ColorAnimation { duration: ThemeManager.transition.duration.fast }
        }
    }
}