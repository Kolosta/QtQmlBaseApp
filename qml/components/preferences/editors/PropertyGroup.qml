import QtQuick
import QtQuick.Layouts
import QtQmlBaseApp.Core

ColumnLayout {
    id: root
    
    property string title: ""
    property alias content: contentLoader.sourceComponent
    
    spacing: ThemeManager.spacing.padding.sm.scaled
    Layout.fillWidth: true
    
    // Title
    Text {
        text: root.title
        font.family: ThemeManager.font.family.primary
        font.pixelSize: ThemeManager.font.size.text.lg.scaled
        font.weight: ThemeManager.font.weight.medium
        color: ThemeManager.color.text.primary.defaultColor
    }
    
    // Separator
    Rectangle {
        Layout.fillWidth: true
        height: ThemeManager.border.width.thin.scaled
        color: ThemeManager.color.border.defaultColor.defaultColor
    }
    
    // Content
    Loader {
        id: contentLoader
        Layout.fillWidth: true
    }
}