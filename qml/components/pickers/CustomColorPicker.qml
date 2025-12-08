import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

Popup {
    id: root
    width: 320
    height: 420
    modal: false
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    
    // Définir le parent explicitement (sera la fenêtre principale)
    parent: Overlay.overlay
    
    property color currentColor: "#ffffff"
    property color initialColor: "#ffffff"
    property bool blockWheelUpdates: false  // Bloquer les updates depuis la wheel
    property bool blockSliderUpdates: false // Bloquer les updates depuis les sliders
    property bool updateInProgress: false 
    
    signal colorAccepted(color finalColor)
    
    // Composants de couleur HSV
    property real hue: 0.0
    property real saturation: 1.0
    property real value: 1.0
    property real red: 1.0
    property real green: 1.0
    property real blue: 1.0
    
    property int colorMode: 0 // 0=RGB, 1=HSV, 2=HSL
    property bool accepted: true  // Par défaut, accepter (clic extérieur = validation)
    
    function open(sourceItem) {
        // Initialiser depuis currentColor
        initialColor = currentColor
        updateFromColor(currentColor)
        accepted = true  // Par défaut accepter
        
        // Calculer la position globale
        var globalPos = sourceItem.mapToItem(null, 0, sourceItem.height + 5)
        x = globalPos.x
        y = globalPos.y
        
        // Ouvrir le popup
        visible = true
        forceActiveFocus()
    }
    
    function updateFromColor(color) {
        if (updateInProgress) return
        updateInProgress = true
        
        red = color.r
        green = color.g
        blue = color.b
        
        // Convertir RGB vers HSV
        var max = Math.max(red, green, blue)
        var min = Math.min(red, green, blue)
        var delta = max - min
        
        value = max
        saturation = max === 0 ? 0 : delta / max
        
        if (delta === 0) {
            hue = 0
        } else if (max === red) {
            hue = ((green - blue) / delta) % 6
        } else if (max === green) {
            hue = (blue - red) / delta + 2
        } else {
            hue = (red - green) / delta + 4
        }
        hue = hue / 6
        if (hue < 0) hue += 1
        
        // Mettre à jour la ColorWheel
        colorWheel.hue = hue
        colorWheel.saturation = saturation
        colorWheel.value = value
        
        updateInProgress = false
    }
    
    function updateFromHSV() {
        if (updateInProgress) return
        updateInProgress = true
        
        var c = value * saturation
        var x = c * (1 - Math.abs(((hue * 6) % 2) - 1))
        var m = value - c
        
        var r, g, b
        var h = hue * 6
        
        if (h < 1) { r = c; g = x; b = 0 }
        else if (h < 2) { r = x; g = c; b = 0 }
        else if (h < 3) { r = 0; g = c; b = x }
        else if (h < 4) { r = 0; g = x; b = c }
        else if (h < 5) { r = x; g = 0; b = c }
        else { r = c; g = 0; b = x }
        
        red = r + m
        green = g + m
        blue = b + m
        
        currentColor = Qt.rgba(red, green, blue, 1)
        
        // Forcer la mise à jour des sliders RGB
        if (!blockSliderUpdates) {
            redSlider.value = red
            greenSlider.value = green
            blueSlider.value = blue
        }
        
        updateInProgress = false
    }

    function updateFromRGB() {
        if (updateInProgress) return
        updateInProgress = true
        
        currentColor = Qt.rgba(red, green, blue, 1)
        
        // Convertir RGB vers HSV
        var max = Math.max(red, green, blue)
        var min = Math.min(red, green, blue)
        var delta = max - min
        
        value = max
        saturation = max === 0 ? 0 : delta / max
        
        if (delta === 0) {
            hue = 0
        } else if (max === red) {
            hue = ((green - blue) / delta) % 6
        } else if (max === green) {
            hue = (blue - red) / delta + 2
        } else {
            hue = (red - green) / delta + 4
        }
        hue = hue / 6
        if (hue < 0) hue += 1
        
        // Mettre à jour la ColorWheel
        colorWheel.hue = hue
        colorWheel.saturation = saturation
        colorWheel.value = value
        
        // Forcer la mise à jour des sliders HSV/HSL
        if (!blockSliderUpdates) {
            hueSliderHSV.value = hue
            saturationSliderHSV.value = saturation
            valueSliderHSV.value = value
            
            hueSliderHSL.value = hue
            saturationSliderHSL.value = saturation
            lightnessSliderHSL.value = value
        }
        
        updateInProgress = false
    }
    
    onClosed: {
        if (!accepted) {
            // Annuler : revenir à la couleur initiale
            currentColor = initialColor
        }
    }
    
    // Gérer la validation et l'annulation
    Connections {
        target: root
        function onVisibleChanged() {
            if (!visible && accepted) {
                // La popup a été fermée avec validation
                colorAccepted(currentColor)
            }
        }
    }
    
    // Gérer Échap et Entrée avec un Item invisible
    Item {
        focus: true
        Keys.onEscapePressed: {
            root.accepted = false
            root.close()
        }
        Keys.onReturnPressed: {
            root.accepted = true
            root.close()
        }
    }
    
    background: Rectangle {
        color: ThemeManager.colors.surfacePrimary
        border.width: ThemeManager.sizes.borderThin
        border.color: ThemeManager.colors.borderPrimary
        radius: ThemeManager.sizes.radiusMedium
    }
    
    contentItem: ColumnLayout {
        spacing: 15
        
        // Roue de couleur + Barre de Value
        RowLayout {
            Layout.fillWidth: true
            spacing: 10
            
            ColorWheel {
                id: colorWheel
                Layout.preferredWidth: 180
                Layout.preferredHeight: 180
                hue: root.hue
                saturation: root.saturation
                value: root.value
                
                onColorChanged: {
                    if (root.blockWheelUpdates) return
                    
                    root.blockSliderUpdates = true
                    root.hue = hue
                    root.saturation = saturation
                    root.updateFromHSV()
                    root.blockSliderUpdates = false
                }
            }
            
            // // Barre verticale de Value
            // Rectangle {
            //     Layout.preferredWidth: 30
            //     Layout.preferredHeight: 180
            //     radius: ThemeManager.radiusSmall
            //     border.width: ThemeManager.borderThin
            //     border.color: ThemeManager.borderPrimary
                
            //     gradient: Gradient {
            //         GradientStop { position: 0.0; color: Qt.hsva(root.hue, root.saturation, 1.0, 1) }
            //         GradientStop { position: 1.0; color: Qt.hsva(root.hue, root.saturation, 0.0, 1) }
            //     }
                
            //     Rectangle {
            //         width: parent.width
            //         height: 4
            //         y: (1 - root.value) * (parent.height - height)
            //         color: "white"
            //         border.width: 1
            //         border.color: "black"
            //     }
                
            //     MouseArea {
            //         anchors.fill: parent
                    
            //         function updateValue(mouse) {
            //             var ratio = 1 - Math.max(0, Math.min(1, mouse.y / height))
                        
            //             root.blockSliderUpdates = true
            //             root.value = ratio
            //             colorWheel.value = ratio
            //             root.updateFromHSV()
            //             root.blockSliderUpdates = false
            //         }
                    
            //         onPressed: updateValue(mouse)
            //         onPositionChanged: if (pressed) updateValue(mouse)
            //     }
            // }
            ValueBar {
                id: valueBar
                hue: root.hue
                saturation: root.saturation
                value: root.value

                onValueUpdated: function(newValue) {
                    root.blockSliderUpdates = true
                    root.value = newValue
                    colorWheel.value = newValue
                    root.updateFromHSV()
                    root.blockSliderUpdates = false
                }
            }
        }
        
        // Boutons RGB / HSV / HSL
        SegmentedButton {
            id: modeSelector
            Layout.alignment: Qt.AlignHCenter
            options: ["RGB", "HSV", "HSL"]
            currentIndex: root.colorMode
            onSelectionChanged: root.colorMode = index
        }
        
        // Sliders selon le mode
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 5
            visible: root.colorMode === 0 // RGB
            
            SliderField {
                id: redSlider
                Layout.fillWidth: true
                label: "Red"
                value: root.red
                minValue: 0
                maxValue: 1
                decimals: 3
                onValueModified: function(newValue) {
                    if (root.blockSliderUpdates) return
                    root.blockWheelUpdates = true
                    root.red = newValue
                    root.updateFromRGB()
                    root.blockWheelUpdates = false
                }
            }
            
            SliderField {
                id: greenSlider
                Layout.fillWidth: true
                label: "Green"
                value: root.green
                minValue: 0
                maxValue: 1
                decimals: 3
                onValueModified: function(newValue) {
                    root.blockWheelUpdates = true
                    if (root.blockSliderUpdates) return
                    root.green = newValue
                    root.updateFromRGB()
                    root.blockWheelUpdates = false
                }
            }
            
            SliderField {
                id: blueSlider
                Layout.fillWidth: true
                label: "Blue"
                value: root.blue
                minValue: 0
                maxValue: 1
                decimals: 3
                onValueModified: function(newValue) {
                    if (root.blockSliderUpdates) return
                    root.blockWheelUpdates = true
                    root.blue = newValue
                    root.updateFromRGB()
                    root.blockWheelUpdates = false
                }
            }
        }
        
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 5
            visible: root.colorMode === 1 // HSV
            
            SliderField {
                id: hueSliderHSV
                Layout.fillWidth: true
                label: "Hue"
                value: root.hue
                minValue: 0
                maxValue: 1
                decimals: 3
                onValueModified: function(newValue) {
                    if (root.blockSliderUpdates) return
                    root.blockWheelUpdates = true
                    root.hue = newValue
                    colorWheel.hue = newValue
                    root.updateFromHSV()
                    root.blockWheelUpdates = false
                }
            }
            
            SliderField {
                id: saturationSliderHSV
                Layout.fillWidth: true
                label: "Saturation"
                value: root.saturation
                minValue: 0
                maxValue: 1
                decimals: 3
                onValueModified: function(newValue) {
                    if (root.blockSliderUpdates) return
                    root.blockWheelUpdates = true
                    root.saturation = newValue
                    colorWheel.saturation = newValue
                    root.updateFromHSV()
                    root.blockWheelUpdates = false
                }
            }
            
            SliderField {
                id: valueSliderHSV
                Layout.fillWidth: true
                label: "Value"
                value: root.value
                minValue: 0
                maxValue: 1
                decimals: 3
                onValueModified: function(newValue) {
                    if (root.blockSliderUpdates) return
                    root.blockWheelUpdates = true
                    root.value = newValue
                    colorWheel.value = newValue
                    root.updateFromHSV()
                    root.blockWheelUpdates = false
                }
            }
        }
        
        // HSL (simplifié, convertit via HSV)
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 5
            visible: root.colorMode === 2 // HSL
            
            SliderField {
                id: hueSliderHSL
                Layout.fillWidth: true
                label: "Hue"
                value: root.hue
                minValue: 0
                maxValue: 1
                decimals: 3
                onValueModified: function(newValue) {
                    if (root.blockSliderUpdates) return
                    root.blockWheelUpdates = true
                    root.hue = newValue
                    colorWheel.hue = newValue
                    root.updateFromHSV()
                    root.blockWheelUpdates = false
                }
            }
            
            SliderField {
                id: saturationSliderHSL
                Layout.fillWidth: true
                label: "Saturation"
                value: root.saturation
                minValue: 0
                maxValue: 1
                decimals: 3
                onValueModified: function(newValue) {
                    if (root.blockSliderUpdates) return
                    root.blockWheelUpdates = true
                    root.saturation = newValue
                    colorWheel.saturation = newValue
                    root.updateFromHSV()
                    root.blockWheelUpdates = false
                }
            }
            
            SliderField {
                id: lightnessSliderHSL
                Layout.fillWidth: true
                label: "Lightness"
                value: root.value
                minValue: 0
                maxValue: 1
                decimals: 3
                onValueModified: function(newValue) {
                    if (root.blockSliderUpdates) return
                    root.blockWheelUpdates = true
                    root.value = newValue
                    colorWheel.value = newValue
                    root.updateFromHSV()
                    root.blockWheelUpdates = false
                }
            }
        }
        
        // Hex + Pipette
        RowLayout {
            Layout.fillWidth: true
            spacing: 10
            
            Text {
                text: "Hex"
                color: ThemeManager.colors.textPrimary
                font.pixelSize: ThemeManager.sizes.fontSmall
            }
            
            TextField {
                id: hexField
                Layout.fillWidth: true
                text: root.currentColor.toString().toUpperCase()
                font.pixelSize: ThemeManager.sizes.fontSmall
                horizontalAlignment: Text.AlignLeft
                color: ThemeManager.colors.textPrimary
                selectByMouse: true
                
                background: Rectangle {
                    color: ThemeManager.colors.surfacePrimary
                    border.width: ThemeManager.sizes.borderThin
                    border.color: ThemeManager.colors.borderPrimary
                    radius: ThemeManager.sizes.radiusSmall
                }
                
                onEditingFinished: {
                    if (text.match(/^#[0-9A-Fa-f]{6}$/)) {
                        root.blockSliderUpdates = true
                        root.currentColor = text
                        root.updateFromColor(root.currentColor)
                        root.blockSliderUpdates = false
                    }
                }
                
                Keys.onReturnPressed: editingFinished()
            }
            
            Button {
                text: "💉"  // Icône pipette
                width: 30
                height: 30
                
                background: Rectangle {
                    color: parent.pressed ? ThemeManager.colors.surfaceHover : ThemeManager.colors.surfacePrimary
                    border.width: ThemeManager.sizes.borderThin
                    border.color: ThemeManager.colors.borderPrimary
                    radius: ThemeManager.sizes.radiusSmall
                }
                
                contentItem: Text {
                    text: parent.text
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 16
                }
                
                ToolTip.visible: hovered
                ToolTip.text: "Color Picker (not yet implemented)"
                
                onClicked: {
                    console.log("TODO: Implement screen color picker")
                    // TODO: Implémenter la sélection de couleur à l'écran
                }
            }
        }
    }
}