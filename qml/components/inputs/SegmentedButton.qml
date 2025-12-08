import QtQuick
import QtQuick.Controls
import QtQmlBaseApp.Core

// Composant réutilisable : Boutons segmentés (radio group visuel)
Row {
    id: root
    spacing: 0
    
    property var options: []
    property int currentIndex: 0
    
    signal selectionChanged(int index)
    
    Repeater {
        model: root.options
        
        Item {
            width: 60
            height: 30
            
            Rectangle {
                id: btnBg
                anchors.fill: parent
                anchors.leftMargin: index === 0 ? 0 : -ThemeManager.sizes.borderThin
                color: root.currentIndex === index ? ThemeManager.colors.primaryBase : ThemeManager.colors.surfacePrimary
                border.width: ThemeManager.borderThin
                border.color: root.currentIndex === index ? ThemeManager.colors.primaryBase : ThemeManager.colors.borderPrimary
                z: root.currentIndex === index ? 2 : 1
                
                // Masquer les coins intérieurs avec des rectangles
                Rectangle {
                    visible: index > 0
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: ThemeManager.sizes.radiusSmall
                    color: parent.color
                    z: -1
                }
                
                Rectangle {
                    visible: index < root.options.length - 1
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: ThemeManager.sizes.radiusSmall
                    color: parent.color
                    z: -1
                }
                
                // Radius uniquement sur les extrémités
                radius: {
                    if (index === 0 || index === root.options.length - 1) {
                        return ThemeManager.sizes.radiusSmall
                    }
                    return 0
                }
                
                Behavior on color {
                    ColorAnimation { duration: ThemeManager.sizes.animNormal }
                }
            }
            
            Text {
                anchors.centerIn: parent
                text: modelData
                color: root.currentIndex === index ? "#ffffff" : ThemeManager.colors.textPrimary
                font.pixelSize: ThemeManager.sizes.fontSmall
                font.bold: root.currentIndex === index
                z: 3
                
                Behavior on color {
                    ColorAnimation { duration: ThemeManager.sizes.animNormal }
                }
            }
            
            MouseArea {
                anchors.fill: parent
                z: 3
                onClicked: {
                    root.currentIndex = index
                    root.selectionChanged(index)
                }
            }
        }
    }
}