import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

Item {
    id: root
    implicitHeight: content.height
    
    // États pour NumberField
    property int intValue: 50
    property real floatValue: 3.14159
    property int unboundedValue: 0
    property real preciseValue: 0.5
    property int largeStepValue: 0
    
    // États pour SliderField
    property real opacityValue: 0.75
    property real volumeValue: 0.5
    property real temperatureValue: 20.0
    property int percentValue: 50
    
    // États pour SegmentedButton
    property int alignmentIndex: 0
    property int viewModeIndex: 0
    property int qualityIndex: 1
    
    Column {
        id: content
        width: parent.width
        spacing: 15
        topPadding: 20
        
        Text {
            text: "Components Lib"
            font.pixelSize: ThemeManager.fontSizeTitle
            font.bold: true
            color: ThemeManager.text
        }
        
        // ====== NUMBERFIELD SECTION ======
        ComponentSection {
            Layout.fillWidth: true
            title: "NumberField"
            collapsed: true
            
            ComponentSubSection {
                Layout.fillWidth: true
                title: "Interactive Examples"
                collapsed: true
                
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 20
                    
                    // Exemple 1: Integer avec min/max (avec slider)
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "Integer avec min/max (0-100) - Affiche le slider"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        NumberField {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 30
                            value: root.intValue
                            minValue: 0
                            maxValue: 100
                            decimals: 0
                            hasMin: true
                            hasMax: true
                            stepSize: 1
                            
                            onValueModified: function(newValue) {
                                root.intValue = newValue
                            }
                        }
                        
                        Text {
                            text: "Valeur: " + root.intValue
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: ThemeManager.border
                        opacity: 0.3
                    }
                    
                    // Exemple 2: Float avec 5 décimales
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "Float avec 5 décimales (min: 0, max: 10)"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        NumberField {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 30
                            value: root.floatValue
                            minValue: 0
                            maxValue: 10
                            decimals: 5
                            hasMin: true
                            hasMax: true
                            stepSize: 0.01
                            
                            onValueModified: function(newValue) {
                                root.floatValue = newValue
                            }
                        }
                        
                        Text {
                            text: "Valeur: " + root.floatValue.toFixed(5)
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: ThemeManager.border
                        opacity: 0.3
                    }
                    
                    // Exemple 3: Sans limites (scroll infini)
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "Sans limites (scroll infini) - Pas de slider"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        NumberField {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 30
                            value: root.unboundedValue
                            decimals: 0
                            hasMin: false
                            hasMax: false
                            stepSize: 1
                            
                            onValueModified: function(newValue) {
                                root.unboundedValue = newValue
                            }
                        }
                        
                        Text {
                            text: "Valeur: " + root.unboundedValue
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: ThemeManager.border
                        opacity: 0.3
                    }
                    
                    // Exemple 4: Uniquement min
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "Avec minimum uniquement (min: 0) - Pas de slider"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        NumberField {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 30
                            value: Math.max(0, root.unboundedValue)
                            minValue: 0
                            decimals: 0
                            hasMin: true
                            hasMax: false
                            stepSize: 1
                            
                            onValueModified: function(newValue) {
                                root.unboundedValue = newValue
                            }
                        }
                        
                        Text {
                            text: "Valeur: " + Math.max(0, root.unboundedValue)
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: ThemeManager.border
                        opacity: 0.3
                    }
                    
                    // Exemple 5: Float précis avec petit step
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "Float précis (0-1, step: 0.001, 3 décimales)"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        NumberField {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 30
                            value: root.preciseValue
                            minValue: 0
                            maxValue: 1
                            decimals: 3
                            hasMin: true
                            hasMax: true
                            stepSize: 0.001
                            
                            onValueModified: function(newValue) {
                                root.preciseValue = newValue
                            }
                        }
                        
                        Text {
                            text: "Valeur: " + root.preciseValue.toFixed(3) + " (Shift pour précision fine)"
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: ThemeManager.border
                        opacity: 0.3
                    }
                    
                    // Exemple 6: Grand step
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "Grand step (0-1000, step: 50)"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        NumberField {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 30
                            value: root.largeStepValue
                            minValue: 0
                            maxValue: 1000
                            decimals: 0
                            hasMin: true
                            hasMax: true
                            stepSize: 50
                            
                            onValueModified: function(newValue) {
                                root.largeStepValue = newValue
                            }
                        }
                        
                        Text {
                            text: "Valeur: " + root.largeStepValue
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: ThemeManager.border
                        opacity: 0.3
                    }
                    
                    // Légende des interactions
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "💡 Interactions disponibles:"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        Text {
                            text: "• Drag horizontal (centre) : modifier la valeur\n" +
                                  "• Shift + Drag : précision fine (30%)\n" +
                                  "• Double-clic : édition manuelle\n" +
                                  "• Hover : affiche les boutons ‹ › pour incrémenter/décrémenter\n" +
                                  "• Clic droit pendant drag : annuler\n" +
                                  "• Escape : annuler drag ou édition"
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                            lineHeight: 1.4
                        }
                    }
                }
            }
        }
        
        // ====== SLIDERFIELD SECTION ======
        ComponentSection {
            Layout.fillWidth: true
            title: "SliderField"
            collapsed: true
            
            ComponentSubSection {
                Layout.fillWidth: true
                title: "Standard Examples"
                collapsed: true
                
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 20
                    
                    // Exemple 1: Opacity slider (0-1)
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "Opacity (0-1, 3 décimales)"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        SliderField {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 30
                            label: "Opacity"
                            value: root.opacityValue
                            minValue: 0.0
                            maxValue: 1.0
                            decimals: 3
                            
                            onValueModified: function(newValue) {
                                root.opacityValue = newValue
                            }
                        }
                        
                        Text {
                            text: "Valeur: " + root.opacityValue.toFixed(3)
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: ThemeManager.border
                        opacity: 0.3
                    }
                    
                    // Exemple 2: Volume (0-1, 2 décimales)
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "Volume (0-1, 2 décimales)"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        SliderField {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 30
                            label: "Volume"
                            value: root.volumeValue
                            minValue: 0.0
                            maxValue: 1.0
                            decimals: 2
                            
                            onValueModified: function(newValue) {
                                root.volumeValue = newValue
                            }
                        }
                        
                        Text {
                            text: "Valeur: " + root.volumeValue.toFixed(2)
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: ThemeManager.border
                        opacity: 0.3
                    }
                    
                    // Exemple 3: Température (-20 à 50)
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "Température (-20°C à 50°C, 1 décimale)"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        SliderField {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 30
                            label: "Temperature"
                            value: root.temperatureValue
                            minValue: -20.0
                            maxValue: 50.0
                            decimals: 1
                            
                            onValueModified: function(newValue) {
                                root.temperatureValue = newValue
                            }
                        }
                        
                        Text {
                            text: "Valeur: " + root.temperatureValue.toFixed(1) + "°C"
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: ThemeManager.border
                        opacity: 0.3
                    }
                    
                    // Exemple 4: Pourcentage (0-100, entier)
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "Pourcentage (0-100, entier)"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        SliderField {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 30
                            label: "Progress"
                            value: root.percentValue
                            minValue: 0
                            maxValue: 100
                            decimals: 0
                            
                            onValueModified: function(newValue) {
                                root.percentValue = newValue
                            }
                        }
                        
                        Text {
                            text: "Valeur: " + root.percentValue + "%"
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: ThemeManager.border
                        opacity: 0.3
                    }
                    
                    // Légende des interactions
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "💡 Interactions disponibles:"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        Text {
                            text: "• Clic sur le slider : positionner la valeur\n" +
                                  "• Drag : modifier en continu\n" +
                                  "• Double-clic : édition manuelle du nombre"
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                            lineHeight: 1.4
                        }
                    }
                }
            }
        }
        
        // ====== SEGMENTEDBUTTON SECTION ======
        ComponentSection {
            Layout.fillWidth: true
            title: "SegmentedButton"
            collapsed: true
            
            ComponentSubSection {
                Layout.fillWidth: true
                title: "Examples"
                collapsed: true
                
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 20
                    
                    // Exemple 1: Text Alignment
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "Text Alignment (3 options)"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        SegmentedButton {
                            options: ["Left", "Center", "Right"]
                            currentIndex: root.alignmentIndex
                            
                            onSelectionChanged: function(index) {
                                root.alignmentIndex = index
                            }
                        }
                        
                        Text {
                            text: "Sélection: " + ["Left", "Center", "Right"][root.alignmentIndex]
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: ThemeManager.border
                        opacity: 0.3
                    }
                    
                    // Exemple 2: View Mode
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "View Mode (2 options)"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        SegmentedButton {
                            options: ["List", "Grid"]
                            currentIndex: root.viewModeIndex
                            
                            onSelectionChanged: function(index) {
                                root.viewModeIndex = index
                            }
                        }
                        
                        Text {
                            text: "Mode: " + ["List", "Grid"][root.viewModeIndex]
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: ThemeManager.border
                        opacity: 0.3
                    }
                    
                    // Exemple 3: Quality Settings
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "Quality Settings (4 options)"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        SegmentedButton {
                            options: ["Low", "Medium", "High", "Ultra"]
                            currentIndex: root.qualityIndex
                            
                            onSelectionChanged: function(index) {
                                root.qualityIndex = index
                            }
                        }
                        
                        Text {
                            text: "Qualité: " + ["Low", "Medium", "High", "Ultra"][root.qualityIndex]
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                        }
                    }
                    
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: ThemeManager.border
                        opacity: 0.3
                    }
                    
                    // Légende
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 5
                        
                        Text {
                            text: "💡 Usage:"
                            color: ThemeManager.text
                            font.pixelSize: ThemeManager.fontSizeSmall
                            font.bold: true
                        }
                        
                        Text {
                            text: "• Clic sur une option : sélectionner\n" +
                                  "• L'option sélectionnée est mise en surbrillance\n" +
                                  "• Idéal pour des choix mutuellement exclusifs (radio group)"
                            color: ThemeManager.textSecondary
                            font.pixelSize: ThemeManager.fontSizeSmall
                            lineHeight: 1.4
                        }
                    }
                }
            }
        }
    }
}