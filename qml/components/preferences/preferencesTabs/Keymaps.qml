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
        spacing: ThemeManager.getScaledInt("spacing.medium")
        topPadding: ThemeManager.getScaledInt("spacing.large")
        
        // Header with reset button
        RowLayout {
            width: parent.width
            spacing: ThemeManager.getScaledInt("spacing.medium")
            
            Text {
                Layout.fillWidth: true
                text: "Keyboard Shortcuts"
                font.pixelSize: ThemeManager.getScaledInt("fonts.size.xlarge")
                font.bold: true
                color: ThemeManager.getColor("colors.text.primary")
            }
            
            Button {
                text: "Reset All"
                
                background: Rectangle {
                    color: parent.pressed ? ThemeManager.getColor("colors.status.errorHover") : 
                           parent.hovered ? ThemeManager.getColor("colors.status.error") : 
                           ThemeManager.getComponentColor("button", "background")
                    border.width: ThemeManager.getComponentScaledInt("button", "borderWidth")
                    border.color: ThemeManager.getColor("colors.status.error")
                    radius: ThemeManager.getComponentScaledInt("button", "radius")
                }
                
                contentItem: Text {
                    text: parent.text
                    color: parent.pressed || parent.hovered ? "#ffffff" : ThemeManager.getColor("colors.text.primary")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: ThemeManager.fontSizeMedium
                }
                
                onClicked: resetAllDialog.open()
            }
        }
        
        Text {
            width: parent.width
            text: "Customize keyboard shortcuts for all actions. Click on a shortcut to change it."
            font.pixelSize: ThemeManager.fontSizeMedium
            color: ThemeManager.getColor("colors.text.secondary")
            wrapMode: Text.WordWrap
        }
        
        // Categories and actions
        Column {
            width: parent.width
            spacing: ThemeManager.getScaledInt("spacing.small")
            
            Repeater {
                model: KeymapManager.getCategories()
                
                KeymapCategory {
                    width: parent.width
                    categoryData: modelData
                }
            }
        }
    }
    
    // Category component
    component KeymapCategory: Rectangle {
        id: categoryRoot
        property var categoryData
        
        implicitHeight: categoryColumn.implicitHeight
        color: ThemeManager.getComponentColor("section", "background")
        border.width: ThemeManager.getComponentScaledInt("section", "borderWidth")
        border.color: ThemeManager.getComponentColor("section", "border")
        radius: ThemeManager.getComponentScaledInt("section", "radius")
        
        Column {
            id: categoryColumn
            width: parent.width
            spacing: 0
            
            // Category header
            Rectangle {
                width: parent.width
                height: ThemeManager.getComponentScaledInt("section", "headerHeight")
                color: "transparent"
                
                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: ThemeManager.spacingMedium
                    anchors.verticalCenter: parent.verticalCenter
                    text: categoryRoot.categoryData.label
                    font.pixelSize: ThemeManager.fontSizeLarge
                    font.bold: true
                    color: ThemeManager.getColor("colors.primary.base")
                }
                
                Rectangle {
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: ThemeManager.borderThin
                    color: ThemeManager.getColor("colors.border.primary")
                }
            }
            
            // Actions list
            Column {
                width: parent.width
                spacing: 0
                
                Repeater {
                    model: KeymapManager.getActionsForCategory(categoryRoot.categoryData.id)
                    
                    KeymapActionRow {
                        width: parent.width
                        actionData: modelData
                    }
                }
            }
        }
    }
    
    // Action row component
    component KeymapActionRow: Rectangle {
        id: actionRow
        property var actionData
        
        height: ThemeManager.getScaledInt("spacing.xxxlarge")
        color: hoverArea.containsMouse ? ThemeManager.getColor("colors.surface.hover") : "transparent"
        
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: ThemeManager.getScaledInt("spacing.xlarge")
            anchors.rightMargin: ThemeManager.spacingMedium
            spacing: ThemeManager.spacingMedium
            
            // Action label
            Text {
                Layout.fillWidth: true
                text: actionRow.actionData.label
                color: actionRow.actionData.isModified ? 
                    ThemeManager.getColor("colors.accent.base") : 
                    ThemeManager.getColor("colors.text.primary")
                font.pixelSize: ThemeManager.fontSizeMedium
                font.bold: actionRow.actionData.isModified
            }
            
            // Shortcut display/editor
            Rectangle {
                Layout.preferredWidth: 150
                Layout.preferredHeight: 30
                color: shortcutMouseArea.containsMouse ? 
                    ThemeManager.getColor("colors.surface.hover") : 
                    ThemeManager.getColor("colors.surface.primary")
                border.width: ThemeManager.borderThin
                border.color: ThemeManager.getColor("colors.border.primary")
                radius: ThemeManager.radiusSmall
                
                Text {
                    anchors.centerIn: parent
                    text: actionRow.actionData.shortcut || "Not set"
                    color: actionRow.actionData.shortcut ? 
                        ThemeManager.getColor("colors.text.primary") : 
                        ThemeManager.getColor("colors.text.tertiary")
                    font.pixelSize: ThemeManager.fontSizeSmall
                }
                
                MouseArea {
                    id: shortcutMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    
                    onClicked: {
                        shortcutDialog.actionId = actionRow.actionData.id
                        shortcutDialog.actionLabel = actionRow.actionData.label
                        shortcutDialog.currentShortcut = actionRow.actionData.shortcut
                        shortcutDialog.open()
                    }
                }
            }
            
            // Reset button
            Button {
                Layout.preferredWidth: 30
                Layout.preferredHeight: 30
                text: "↺"
                visible: actionRow.actionData.isModified
                
                background: Rectangle {
                    color: parent.hovered ? 
                        ThemeManager.getColor("colors.surface.hover") : 
                        ThemeManager.getColor("colors.surface.primary")
                    border.width: ThemeManager.borderThin
                    border.color: ThemeManager.getColor("colors.border.primary")
                    radius: ThemeManager.radiusSmall
                }
                
                contentItem: Text {
                    text: parent.text
                    color: ThemeManager.getColor("colors.text.primary")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: ThemeManager.fontSizeLarge
                }
                
                onClicked: {
                    KeymapManager.resetShortcut(actionRow.actionData.id)
                }
            }
        }
        
        MouseArea {
            id: hoverArea
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            acceptedButtons: Qt.NoButton
        }
        
        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: 1
            color: ThemeManager.getColor("colors.border.primary")
            opacity: 0.3
        }
    }
    
    // Shortcut editor dialog
    ShortcutDialog {
        id: shortcutDialog
    }
    
    // Reset all confirmation
    CustomDialog {
        id: resetAllDialog
        
        dialogTitle: "Reset All Shortcuts"
        text: "Are you sure you want to reset all keyboard shortcuts to their defaults?"
        
        acceptButtonText: "Reset All"
        cancelButtonText: "Cancel"
        strictMode: true
        
        onAccepted: {
            KeymapManager.resetAll()
        }
    }
}