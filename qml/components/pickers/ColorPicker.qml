import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQmlBaseApp.Core

Row {
    id: root
    spacing: 10
    
    property color currentColor: "#ffffff"
    property string label: "Color"
    
    signal colorChanged(color newColor)
    
    Text {
        anchors.verticalCenter: parent.verticalCenter
        text: root.label
        color: ThemeManager.colors.textPrimary
        font.pixelSize: ThemeManager.sizes.fontSmall
        width: 120
    }
    
    Rectangle {
        width: 80
        height: 30
        color: root.currentColor
        border.width: ThemeManager.sizes.borderThin
        border.color: ThemeManager.colors.borderPrimary
        radius: ThemeManager.sizes.radiusSmall
        
        MouseArea {
            anchors.fill: parent
            onClicked: colorDialog.open()
        }
    }
    
    TextField {
        width: 100
        height: 30
        text: root.currentColor.toString()
        font.pixelSize: ThemeManager.sizes.fontSmall
        
        background: Rectangle {
            color: ThemeManager.colors.surfacePrimary
            border.width: ThemeManager.sizes.borderThin
            border.color: ThemeManager.colors.borderPrimary
            radius: ThemeManager.sizes.radiusSmall
        }
        
        color: ThemeManager.colors.textPrimary
        
        onEditingFinished: {
            if (text.match(/^#[0-9A-Fa-f]{6}$/)) {
                root.currentColor = text
                root.colorChanged(text)
            }
        }
    }
    
    ColorDialog {
        id: colorDialog
        selectedColor: root.currentColor
        onAccepted: {
            root.currentColor = selectedColor
            root.colorChanged(selectedColor)
        }
    }
}