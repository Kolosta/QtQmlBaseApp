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
        spacing: 15
        topPadding: 20
        
        Text {
            text: "Interface Settings"
            font.pixelSize: ThemeManager.fontSizeTitle
            font.bold: true
            color: ThemeManager.text
        }
        
        // Language setting
        Row {
            spacing: ThemeManager.spacing
            
            Column {
                spacing: 8
                
                Row {
                    spacing: 5
                    
                    Text {
                        text: "Language"
                        font.pixelSize: ThemeManager.fontSizeMedium
                        color: PreferencesManager.isPreferenceModified("general", "language") ? 
                            ThemeManager.accent : ThemeManager.text
                        font.bold: PreferencesManager.isPreferenceModified("general", "language")
                    }
                    
                    Button {
                        width: 25
                        height: 25
                        text: "↺"
                        visible: PreferencesManager.isPreferenceModified("general", "language")
                        
                        background: Rectangle {
                            color: parent.hovered ? ThemeManager.surfaceHover : "transparent"
                            radius: ThemeManager.radiusSmall
                        }
                        
                        contentItem: Text {
                            text: parent.text
                            color: ThemeManager.text
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 14
                        }
                        
                        onClicked: {
                            PreferencesManager.resetPreference("general", "language")
                        }
                    }
                }
                
                ComboBox {
                    width: 200
                    model: ["English"]
                    currentIndex: {
                        let lang = PreferencesManager.language
                        return Math.max(0, model.indexOf(lang))
                    }
                    
                    background: Rectangle {
                        color: ThemeManager.surface
                        border.width: ThemeManager.borderWidth
                        border.color: ThemeManager.border
                        radius: ThemeManager.radiusSmall
                    }
                    
                    contentItem: Text {
                        leftPadding: 10
                        text: parent.displayText
                        color: ThemeManager.text
                        verticalAlignment: Text.AlignVCenter
                    }
                    
                    onCurrentTextChanged: {
                        PreferencesManager.language = currentText
                    }
                }
            }
        }
        
        Rectangle {
            width: parent.width
            height: 1
            color: ThemeManager.border
            opacity: 0.3
        }
        
        // Reset all button
        Button {
            text: "Reset All General Settings"
            
            background: Rectangle {
                color: parent.pressed ? ThemeManager.error : 
                        parent.hovered ? Qt.lighter(ThemeManager.error, 1.2) : 
                        ThemeManager.surface
                border.width: ThemeManager.borderWidth
                border.color: ThemeManager.error
                radius: ThemeManager.radius
            }
            
            contentItem: Text {
                text: parent.text
                color: parent.pressed || parent.hovered ? "#ffffff" : ThemeManager.text
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: ThemeManager.fontSizeMedium
            }
            
            onClicked: PreferencesManager.resetCategory("general")
        }
    }
}