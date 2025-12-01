import QtQuick
import QtQmlBaseApp.Core
import QtQmlBaseApp.Models

Rectangle {
    anchors.fill: parent
    color: ThemeManager.background
    
    Behavior on color {
        ColorAnimation { duration: ThemeManager.animationDuration }
    }
    
    Text {
        anchors.centerIn: parent
        text: TimeModel.currentTime
        font.pixelSize: 48
        font.bold: true
        color: ThemeManager.text
        
        Behavior on color {
            ColorAnimation { duration: ThemeManager.animationDuration }
        }
    }
}