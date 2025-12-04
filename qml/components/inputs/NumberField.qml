import QtQuick
import QtQuick.Controls
import QtQmlBaseApp.Core

Rectangle {
    id: root
    height: 30
    
    // Détection du survol global (Input entier)
    HoverHandler {
        id: rootHover
    }
    
    // Gestion de la couleur de fond (partie centrale)
    color: {
        if (valueInput.visible) return ThemeManager.surface
        if (dragArea.isDragging) return ThemeManager.background
        // Si on survole n'importe où sur le composant, le centre devient SurfaceHover
        if (rootHover.hovered) return ThemeManager.surfaceHover 
        return ThemeManager.surface
    }

    border.width: ThemeManager.borderWidth
    border.color: dragArea.isDragging ? ThemeManager.surfaceHover : ThemeManager.border
    radius: ThemeManager.radiusSmall
    
    // Le clip est important ici pour que les coins des boutons latéraux 
    // respectent l'arrondi du composant parent
    clip: true 
    
    Behavior on color { ColorAnimation { duration: 100 } }
    Behavior on border.color { ColorAnimation { duration: 100 } }
    
    // Properties configurables
    property real value: 0.0
    property real minValue: -999999
    property real maxValue: 999999
    property int decimals: 0
    property real stepSize: 1.0
    property bool hasMin: false
    property bool hasMax: false
    
    // Taille des zones de clic latérales
    readonly property int sideButtonWidth: 30 
    
    signal valueModified(real newValue)
    
    readonly property bool showSlider: hasMin && hasMax
    
    // Partie remplie du slider (Arrière-plan)
    Rectangle {
        visible: root.showSlider
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: parent.border.width
        width: {
            if (!root.showSlider) return 0
            var ratio = (root.value - root.minValue) / (root.maxValue - root.minValue)
            return Math.max(0, (parent.width - 2 * parent.border.width) * ratio)
        }
        color: ThemeManager.primary
        radius: ThemeManager.radiusSmall - 1 // Légèrement plus petit pour l'intérieur
        opacity: 0.3 // Légère transparence pour ne pas gêner la lisibilité
        
        Behavior on width {
            NumberAnimation { duration: 50 }
        }
    }
    
    // --- ZONE GAUCHE (Décrémenter) ---
    Rectangle {
        id: leftButton
        width: root.sideButtonWidth
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: parent.border.width // Pour ne pas écraser la bordure
        
        // Visibilité : Uniquement si survol global ou dragging, et pas en mode édition
        visible: !valueInput.visible && (rootHover.hovered || dragArea.isDragging)
        
        // Couleur : Surface en hover, Accent en drag
        color: dragArea.isDragging ? ThemeManager.accent : ThemeManager.surface
        
        // Arrondi uniquement sur les coins gauches pour matcher le parent (visuel)
        radius: ThemeManager.radiusSmall 
        
        Behavior on color { ColorAnimation { duration: 100 } }

        Text {
            anchors.centerIn: parent
            text: "‹"
            font.pixelSize: ThemeManager.fontSizeLarge
            // Le texte reste visible (blanc/noir) ou s'adapte
            color: ThemeManager.text
        }

        MouseArea {
            id: leftClickArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: decrementValue()
        }
    }
    
    // --- ZONE DROITE (Incrémenter) ---
    Rectangle {
        id: rightButton
        width: root.sideButtonWidth
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: parent.border.width
        
        visible: !valueInput.visible && (rootHover.hovered || dragArea.isDragging)
        
        color: dragArea.isDragging ? ThemeManager.accent : ThemeManager.surface
        
        radius: ThemeManager.radiusSmall
        
        Behavior on color { ColorAnimation { duration: 100 } }

        Text {
            anchors.centerIn: parent
            text: "›"
            font.pixelSize: ThemeManager.fontSizeLarge
            color: ThemeManager.text
        }

        MouseArea {
            id: rightClickArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: incrementValue()
        }
    }
    
    // Valeur au centre
    Text {
        id: valueText
        anchors.centerIn: parent
        text: formatValue(root.value)
        color: ThemeManager.text
        font.pixelSize: ThemeManager.fontSizeMedium
        visible: !valueInput.visible
    }
    
    // Champ de texte pour édition manuelle
    TextField {
        id: valueInput
        anchors.fill: parent
        anchors.margins: parent.border.width
        visible: false
        horizontalAlignment: Text.AlignCenter
        font.pixelSize: ThemeManager.fontSizeMedium
        color: ThemeManager.text
        selectByMouse: true
        
        background: Rectangle {
            color: ThemeManager.surfaceHover
            border.width: ThemeManager.borderWidth
            border.color: ThemeManager.accent
            radius: ThemeManager.radiusSmall
        }
        
        validator: DoubleValidator {
            bottom: root.hasMin ? root.minValue : -999999
            top: root.hasMax ? root.maxValue : 999999
            decimals: root.decimals
            notation: DoubleValidator.StandardNotation
        }
        
        onEditingFinished: {
            applyTextInput()
        }
        
        Keys.onEscapePressed: function(event) {
            cancelTextInput()
            event.accepted = true
        }
        
        Keys.onReturnPressed: function(event) {
            applyTextInput()
            event.accepted = true
        }
    }
    
    // Zone de drag centrale
    MouseArea {
        id: dragArea
        anchors.fill: parent
        // Les marges correspondent maintenant à la largeur des zones latérales
        anchors.leftMargin: root.sideButtonWidth 
        anchors.rightMargin: root.sideButtonWidth
        
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        hoverEnabled: true
        cursorShape: !valueInput.visible ? Qt.SizeHorCursor : Qt.ArrowCursor
        propagateComposedEvents: false
        
        property real startValue: 0
        property real startX: 0
        property real currentX: 0
        property bool isDragging: false
        
        function updateValue(mouse) {
            if (valueInput.visible) return
            
            var delta = mouse.x - startX
            var precision = (mouse.modifiers & Qt.ShiftModifier) ? 0.3 : 1.0
            var dpiCorrection = 1.0 / Screen.devicePixelRatio
            var change = delta * precision * dpiCorrection
            var rawValue = startValue + change
            
            var newValue = rawValue
            if (root.stepSize !== 1.0) {
                newValue = Math.round(rawValue / root.stepSize) * root.stepSize
            }
            
            newValue = clampValue(newValue)
            
            if (root.decimals === 0) {
                newValue = Math.round(newValue)
            } else {
                newValue = parseFloat(newValue.toFixed(root.decimals))
            }
            
            if (newValue !== root.value) {
                root.value = newValue
                root.valueModified(newValue)
            }
        }
        
        onPressed: function(mouse) {
            if (valueInput.visible) return
            
            if (mouse.button === Qt.RightButton) {
                if (isDragging) {
                    cancelDrag()
                } else {
                    cancelTextInput()
                }
                return
            }
            
            startValue = root.value
            startX = mouse.x
            currentX = mouse.x
            isDragging = true
            root.forceActiveFocus()
        }
        
        onPositionChanged: function(mouse) {
            if (!isDragging || valueInput.visible) return
            currentX = mouse.x
            updateValue(mouse)
        }
        
        onReleased: {
            isDragging = false
        }
        
        onDoubleClicked: function(mouse) {
            if (mouse.button === Qt.LeftButton && !valueInput.visible) {
                valueInput.text = formatValue(root.value)
                valueInput.visible = true
                valueInput.forceActiveFocus()
                valueInput.selectAll()
            }
        }
        
        onClicked: function(mouse) {
            if (mouse.button === Qt.RightButton) {
                if (isDragging) {
                    cancelDrag()
                } else if (valueInput.visible) {
                    cancelTextInput()
                }
            }
        }
    }
    
    Keys.onEscapePressed: function(event) {
        if (dragArea.isDragging) {
            cancelDrag()
            event.accepted = true
        }
    }
    
    // MouseArea invisible pour détecter les clics en dehors du TextField
    MouseArea {
        id: externalClickDetector
        anchors.fill: parent
        enabled: valueInput.visible
        propagateComposedEvents: false
        z: -1
    }
    
    // Overlay global pour capturer les clics en dehors du composant
    Loader {
        active: valueInput.visible
        sourceComponent: MouseArea {
            parent: Overlay.overlay
            anchors.fill: parent
            z: 1000
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            
            onPressed: function(mouse) {
                var inputPos = valueInput.mapFromItem(parent, mouse.x, mouse.y)
                if (!valueInput.contains(inputPos)) {
                    if (mouse.button === Qt.RightButton) {
                        cancelTextInput()
                    } else if (mouse.button === Qt.LeftButton) {
                        applyTextInput()
                    }
                    mouse.accepted = true
                } else {
                    mouse.accepted = false
                }
            }
        }
    }
    
    //TODO : à remettre ??
    // Connections {
    //     target: root.Window.window
    //     enabled: dragArea.isDragging
    //     function onMousePressed(mouse) {
    //         if (mouse.button === Qt.RightButton && dragArea.isDragging) {
    //             cancelDrag()
    //         }
    //     }
    // }
    
    // Fonctions utilitaires
    function formatValue(val) {
        if (root.decimals === 0) {
            return Math.round(val).toString()
        }
        return val.toFixed(root.decimals)
    }
    
    function clampValue(val) {
        if (root.hasMin) {
            val = Math.max(root.minValue, val)
        }
        if (root.hasMax) {
            val = Math.min(root.maxValue, val)
        }
        return val
    }
    
    function incrementValue() {
        var newValue = root.value + root.stepSize
        newValue = clampValue(newValue)
        root.value = newValue
        root.valueModified(newValue)
    }
    
    function decrementValue() {
        var newValue = root.value - root.stepSize
        newValue = clampValue(newValue)
        root.value = newValue
        root.valueModified(newValue)
    }
    
    function applyTextInput() {
        if (!valueInput.visible) return
        
        var newValue = parseFloat(valueInput.text)
        if (!isNaN(newValue)) {
            newValue = clampValue(newValue)
            if (root.decimals === 0) {
                newValue = Math.round(newValue)
            }
            root.value = newValue
            root.valueModified(newValue)
        }
        valueInput.visible = false
        valueText.text = formatValue(root.value)
    }
    
    function cancelTextInput() {
        if (!valueInput.visible) return
        valueInput.visible = false
        valueText.text = formatValue(root.value)
    }
    
    function cancelDrag() {
        if (dragArea.isDragging) {
            root.value = dragArea.startValue
            root.valueModified(dragArea.startValue)
            dragArea.isDragging = false
        }
    }
}