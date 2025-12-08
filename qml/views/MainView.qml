import QtQuick
import QtQmlBaseApp.Core
import QtQmlBaseApp.Models

Rectangle {
    anchors.fill: parent
    color: ThemeManager.background.color.bgPrimary
    
    Behavior on color {
        ColorAnimation { duration: ThemeManager.sizes.animNormal }
    }
    
    Text {
        anchors.centerIn: parent
        text: TimeModel.currentTime
        font.pixelSize: 48
        font.bold: true
        color: ThemeManager.font.color.textPrimary
        
        Behavior on color {
            ColorAnimation { duration: ThemeManager.sizes.animNormal }
        }
    }
}