import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

Window {
    id: root
    width: 800
    height: 600
    minimumWidth: 700
    minimumHeight: 500
    title: "Preferences"
    color: ThemeManager.background
    modality: Qt.ApplicationModal
    
    property string currentCategory: "general"
    
    RowLayout {
        anchors.fill: parent
        spacing: 0
        
        // Sidebar
        Rectangle {
            Layout.preferredWidth: 180
            Layout.fillHeight: true
            color: ThemeManager.surface
            
            Column {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 5
                
                CategoryButton {
                    text: "General"
                    isSelected: root.currentCategory === "general"
                    onClicked: root.currentCategory = "general"
                }
                
                CategoryButton {
                    text: "Theme Selector"
                    isSelected: root.currentCategory === "theme"
                    onClicked: root.currentCategory = "theme"
                }
                
                CategoryButton {
                    text: "Theme Editor"
                    isSelected: root.currentCategory === "editor"
                    onClicked: root.currentCategory = "editor"
                }
            }
            
            Rectangle {
                anchors.right: parent.right
                width: 1
                height: parent.height
                color: ThemeManager.border
            }
        }
        
        // Content area
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: ThemeManager.background
            clip: true  // Important pour éviter le débordement
            
            StackLayout {
                anchors.fill: parent
                anchors.margins: 20
                currentIndex: root.currentCategory === "general" ? 0 : 
                             root.currentCategory === "theme" ? 1 : 2
                
                // General preferences
                Column {
                    spacing: 15
                    
                    Text {
                        text: "General Settings"
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
                                    color: root.currentCategory === "general" && PreferencesManager.isPreferenceModified("general", "language") ? 
                                        ThemeManager.accent : ThemeManager.text
                                    font.bold: root.currentCategory === "general" && PreferencesManager.isPreferenceModified("general", "language")
                                }
                                
                                Button {
                                    width: 25
                                    height: 25
                                    text: "↺"
                                    visible: root.currentCategory === "general" && PreferencesManager.isPreferenceModified("general", "language")
                                    
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
                
                // Theme selector
                Column {
                    spacing: 15
                    
                    Text {
                        text: "Theme Selector"
                        font.pixelSize: ThemeManager.fontSizeTitle
                        font.bold: true
                        color: ThemeManager.text
                    }
                    
                    Text {
                        text: "Select a pre-built theme for your application"
                        font.pixelSize: ThemeManager.fontSizeMedium
                        color: ThemeManager.textSecondary
                    }
                    
                    Flow {
                        id: themeFlow
                        width: parent.width
                        spacing: 15
                        
                        // Propriété pour forcer le rafraîchissement
                        property int refreshCounter: 0
                        
                        Repeater {
                            model: ThemeManager.availableThemes
                            
                            ThemeOption {
                                themeName: modelData
                                isSelected: ThemeManager.currentTheme === modelData
                                refreshTrigger: themeFlow.refreshCounter
                                onClicked: ThemeManager.currentTheme = modelData
                            }
                        }
                        
                        // Écouter les changements de propriétés du thème
                        Connections {
                            target: ThemeManager
                            function onThemePropertiesChanged() {
                                themeFlow.refreshCounter++
                            }
                        }
                    }
                }
                
                // Theme editor
                ThemeEditor {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
    }
    
    // Category Button Component
    component CategoryButton: Rectangle {
        property string text
        property bool isSelected: false
        signal clicked()
        
        width: parent.width
        height: 36
        radius: ThemeManager.radius
        color: isSelected ? ThemeManager.primary : 
               (mouseArea.containsMouse ? ThemeManager.surfaceHover : "transparent")
        
        Text {
            anchors.centerIn: parent
            text: parent.text
            color: parent.isSelected ? "#ffffff" : ThemeManager.text
            font.pixelSize: ThemeManager.fontSizeMedium
        }
        
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: parent.clicked()
        }
        
        Behavior on color {
            ColorAnimation { duration: ThemeManager.animationDuration }
        }
    }
    
    // Theme Option Component
    component ThemeOption: Rectangle {
        id: themeOptionRoot
        property string themeName: ""
        property bool isSelected: false
        property int refreshTrigger: 0  // Utilisé pour forcer le rafraîchissement
        signal clicked()
        
        width: 140
        height: 110
        radius: ThemeManager.radius
        border.width: isSelected ? 3 : ThemeManager.borderWidth
        border.color: isSelected ? ThemeManager.accent : ThemeManager.border
        
        // Calculer les couleurs en fonction du refreshTrigger
        color: {
            var dummy = refreshTrigger; // Dépendance explicite
            return ThemeManager.getThemePreviewBackground(themeName)
        }
        
        Behavior on border.width {
            NumberAnimation { duration: ThemeManager.animationDuration }
        }
        
        Behavior on color {
            ColorAnimation { duration: ThemeManager.animationDuration }
        }
        
        Column {
            anchors.centerIn: parent
            spacing: 10
            
            Rectangle {
                width: 50
                height: 50
                radius: 25
                anchors.horizontalCenter: parent.horizontalCenter
                
                // Calculer la couleur en fonction du refreshTrigger
                color: {
                    var dummy = themeOptionRoot.refreshTrigger; // Dépendance explicite
                    return ThemeManager.getThemePreviewPrimary(themeOptionRoot.themeName)
                }
                
                Behavior on color {
                    ColorAnimation { duration: ThemeManager.animationDuration }
                }
            }
            
            Text {
                text: themeOptionRoot.themeName.charAt(0).toUpperCase() + themeOptionRoot.themeName.slice(1).replace(/_/g, ' ')
                anchors.horizontalCenter: parent.horizontalCenter
                color: {
                    // Dépendance sur refreshTrigger pour recalculer
                    var dummy = themeOptionRoot.refreshTrigger;
                    var bg = ThemeManager.getThemePreviewBackground(themeOptionRoot.themeName)
                    var luminance = (0.299 * bg.r + 0.587 * bg.g + 0.114 * bg.b)
                    return luminance > 0.5 ? "#1e1e1e" : "#ffffff"
                }
                font.pixelSize: ThemeManager.fontSizeMedium
                font.bold: themeOptionRoot.isSelected
            }
        }
        
        MouseArea {
            anchors.fill: parent
            onClicked: themeOptionRoot.clicked()
        }
    }
}