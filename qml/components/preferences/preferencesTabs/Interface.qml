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
        spacing: ThemeManager.sizes.spacingMedium
        topPadding: ThemeManager.sizes.spacingLarge
        
        Text {
            text: "Interface Settings"
            font.pixelSize: ThemeManager.sizes.fontXlarge
            font.bold: true
            color: ThemeManager.colors.textPrimary
        }
        
        // Resolution Scale section
        Rectangle {
            width: parent.width
            height: scaleColumn.height + ThemeManager.sizes.spacingLarge * 2
            color: ThemeManager.colors.surfacePrimary
            border.width: ThemeManager.sizes.borderThin
            border.color: ThemeManager.colors.borderPrimary
            radius: ThemeManager.sizes.radiusMedium
            
            Column {
                id: scaleColumn
                width: parent.width - ThemeManager.sizes.spacingLarge * 2
                anchors.centerIn: parent
                spacing: ThemeManager.sizes.spacingMedium
                
                RowLayout {
                    width: parent.width
                    spacing: ThemeManager.sizes.spacingMedium
                    
                    Column {
                        Layout.fillWidth: true
                        spacing: ThemeManager.sizes.spacingSmall
                        
                        Text {
                            text: "Resolution Scale"
                            font.pixelSize: ThemeManager.fontSizeMedium
                            color: ThemeManager.colors.textPrimary
                            font.bold: true
                        }
                        
                        Text {
                            text: "Scale the entire interface. Useful for high-DPI displays."
                            font.pixelSize: ThemeManager.sizes.fontSmall
                            color: ThemeManager.colors.textSecondary
                            wrapMode: Text.WordWrap
                        }
                    }
                    
                    Text {
                        text: (ThemeManager.resolutionScale * 100).toFixed(0) + "%"
                        font.pixelSize: ThemeManager.sizes.fontLarge
                        font.bold: true
                        color: ThemeManager.colors.primaryBase
                    }
                }
                
                Slider {
                    id: scaleSlider
                    width: parent.width
                    from: 0.5
                    to: 3.0
                    value: ThemeManager.resolutionScale
                    stepSize: 0.05
                    
                    background: Rectangle {
                        x: scaleSlider.leftPadding
                        y: scaleSlider.topPadding + scaleSlider.availableHeight / 2 - height / 2
                        width: scaleSlider.availableWidth
                        height: 4
                        radius: 2
                        color: ThemeManager.colors.surfaceSecondary
                        
                        Rectangle {
                            width: scaleSlider.visualPosition * parent.width
                            height: parent.height
                            color: ThemeManager.colors.primaryBase
                            radius: 2
                        }
                    }
                    
                    handle: Rectangle {
                        x: scaleSlider.leftPadding + scaleSlider.visualPosition * (scaleSlider.availableWidth - width)
                        y: scaleSlider.topPadding + scaleSlider.availableHeight / 2 - height / 2
                        width: 20
                        height: 20
                        radius: 10
                        color: scaleSlider.pressed ? 
                            ThemeManager.colors.primaryActive : 
                            ThemeManager.colors.primaryBase
                        border.color: ThemeManager.colors.borderPrimary
                        border.width: ThemeManager.sizes.borderThin
                    }
                    
                    onMoved: {
                        ThemeManager.resolutionScale = value
                    }
                }
                
                RowLayout {
                    width: parent.width
                    spacing: ThemeManager.sizes.spacingSmall
                    
                    Repeater {
                        model: [0.5, 0.75, 1.0, 1.25, 1.5, 2.0, 3.0]
                        
                        Button {
                            text: (modelData * 100).toFixed(0) + "%"
                            
                            background: Rectangle {
                                color: Math.abs(ThemeManager.resolutionScale - modelData) < 0.01 ? 
                                    ThemeManager.colors.primaryBase : 
                                    parent.hovered ? 
                                    ThemeManager.colors.surfaceHover : 
                                    ThemeManager.colors.surfaceSecondary
                                radius: ThemeManager.sizes.radiusSmall
                                border.width: ThemeManager.sizes.borderThin
                                border.color: ThemeManager.colors.borderPrimary
                            }
                            
                            contentItem: Text {
                                text: parent.text
                                color: Math.abs(ThemeManager.resolutionScale - modelData) < 0.01 ? 
                                    ThemeManager.colors.textOnPrimary : 
                                    ThemeManager.colors.textPrimary
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.pixelSize: ThemeManager.sizes.fontSmall
                            }
                            
                            onClicked: {
                                ThemeManager.resolutionScale = modelData
                                scaleSlider.value = modelData
                            }
                        }
                    }
                }
            }
        }
        
        Rectangle {
            width: parent.width
            height: 1
            color: ThemeManager.colors.borderPrimary
            opacity: 0.3
        }
        
        // Language setting
        Row {
            spacing: ThemeManager.sizes.spacingMedium
            
            Column {
                spacing: ThemeManager.sizes.spacingSmall
                
                Row {
                    spacing: ThemeManager.sizes.spacingSmall
                    
                    Text {
                        text: "Language"
                        font.pixelSize: ThemeManager.sizes.fontMedium
                        color: PreferencesManager.isPreferenceModified("general", "language") ? 
                            ThemeManager.colors.accentBase : 
                            ThemeManager.colors.textPrimary
                        font.bold: PreferencesManager.isPreferenceModified("general", "language")
                    }
                    
                    Button {
                        width: 25
                        height: 25
                        text: "↺"
                        visible: PreferencesManager.isPreferenceModified("general", "language")
                        
                        background: Rectangle {
                            color: parent.hovered ? 
                                ThemeManager.colors.surfaceHover : 
                                "transparent"
                            radius: ThemeManager.sizes.radiusSmall
                        }
                        
                        contentItem: Text {
                            text: parent.text
                            color: ThemeManager.colors.textPrimary
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
                        color: ThemeManager.colors.surfacePrimary
                        border.width: ThemeManager.sizes.borderThin
                        border.color: ThemeManager.colors.borderPrimary
                        radius: ThemeManager.sizes.radiusSmall
                    }
                    
                    contentItem: Text {
                        leftPadding: ThemeManager.sizes.spacingMedium
                        text: parent.displayText
                        color: ThemeManager.colors.textPrimary
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: ThemeManager.fontSizeMedium
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
            color: ThemeManager.colors.borderPrimary
            opacity: 0.3
        }
        
        // Reset all button
        Button {
            text: "Reset All General Settings"
            
            background: Rectangle {
                color: parent.pressed ? 
                    ThemeManager.colors.statusError : 
                    parent.hovered ? 
                    ThemeManager.colors.statusErrorHover : 
                    ThemeManager.colors.surfacePrimary
                border.width: ThemeManager.sizes.borderThin
                border.color: ThemeManager.colors.statusError
                radius: ThemeManager.sizes.radiusMedium
            }
            
            contentItem: Text {
                text: parent.text
                color: parent.pressed || parent.hovered ? 
                    "#ffffff" : 
                    ThemeManager.colors.textPrimary
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: ThemeManager.sizes.fontMedium
            }
            
            onClicked: PreferencesManager.resetCategory("general")
        }
    }
}