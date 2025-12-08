import QtQuick
import QtQmlBaseApp.Core
import QtQmlBaseApp.Models

Rectangle {
    anchors.fill: parent
    color: ThemeManager.color.background.primary.defaultColor
    
    Behavior on color {
        ColorAnimation { duration: ThemeManager.transition.duration.md }
    }
    
    Text {
        anchors.centerIn: parent
        text: TimeModel.currentTime
        font.family: ThemeManager.font.family.primary
        font.pixelSize: ThemeManager.font.size.heading1.scaled
        font.weight: ThemeManager.font.weight.bold
        color: ThemeManager.color.text.primary.defaultColor
        
        Behavior on color {
            ColorAnimation { duration: ThemeManager.transition.duration.md }
        }
    }
}