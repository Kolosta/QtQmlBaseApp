import QtQuick
import QtQuick.Controls
import QtQmlBaseApp.Core

Rectangle {
    id: root
    height: ThemeManager.sizes.spacingXxxlarge
    
    HoverHandler {
        id: rootHover
    }
    
    color: {
        if (valueInput.visible) return ThemeManager.colors.backgroundPrimary
        if (dragArea.isDragging) return ThemeManager.colors.backgroundPrimary
        if (rootHover.hovered) return ThemeManager.colors.backgroundHover
        return ThemeManager.colors.backgroundPrimary
    }

    border.width: ThemeManager.sizes.borderThin
    border.color: dragArea.isDragging ? 
        ThemeManager.colors.borderFocus : 
        ThemeManager.colors.borderPrimary
    radius: ThemeManager.sizes.radiusMedium
    
    clip: true
    
    Behavior on color { ColorAnimation { duration: ThemeManager.sizes.animFast } }
    Behavior on border.color { ColorAnimation { duration: ThemeManager.sizes.animFast } }
    
    property real value: 0.0
    property real minValue: -999999
    property real maxValue: 999999
    property int decimals: 0
    property real stepSize: 1.0
    property bool hasMin: false
    property bool hasMax: false
    
    readonly property int sideButtonWidth: 90
    
    signal valueModified(real newValue)
    
    readonly property bool showSlider: hasMin && hasMax
    
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
        color: ThemeManager.colors.primaryBase
        radius: ThemeManager.sizes.radiusSmall
        opacity: 0.3
        
        Behavior on width {
            NumberAnimation { duration: ThemeManager.sizes.animFast }
        }
    }
    
    Rectangle {
        id: leftButton
        width: root.sideButtonWidth
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: parent.border.width
        
        visible: !valueInput.visible && (rootHover.hovered || dragArea.isDragging)
        
        color: dragArea.isDragging ? 
            ThemeManager.colors.accentBase : 
            ThemeManager.colors.backgroundPrimary
        
        radius: ThemeManager.sizes.radiusSmall
        
        Behavior on color { ColorAnimation { duration: ThemeManager.sizes.animFast } }

        Text {
            anchors.centerIn: parent
            text: "‹"
            font.pixelSize: ThemeManager.sizes.fontLarge
            color: ThemeManager.colors.textPrimary
        }

        MouseArea {
            id: leftClickArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: decrementValue()
        }
    }
    
    Rectangle {
        id: rightButton
        width: root.sideButtonWidth
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: parent.border.width
        
        visible: !valueInput.visible && (rootHover.hovered || dragArea.isDragging)
        
        color: dragArea.isDragging ? 
            ThemeManager.colors.accentBase :
            ThemeManager.colors.backgroundPrimary
        
        radius: ThemeManager.sizes.radiusSmall
        
        Behavior on color { ColorAnimation { duration: ThemeManager.sizes.animFast } }

        Text {
            anchors.centerIn: parent
            text: "›"
            font.pixelSize: ThemeManager.sizes.fontLarge
            color: ThemeManager.colors.textPrimary
        }

        MouseArea {
            id: rightClickArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked: incrementValue()
        }
    }
    
    Text {
        id: valueText
        anchors.centerIn: parent
        text: formatValue(root.value)
        color: ThemeManager.colors.textPrimary
        font.pixelSize: ThemeManager.sizes.fontMedium
        visible: !valueInput.visible
    }
    
    TextField {
        id: valueInput
        anchors.fill: parent
        anchors.margins: parent.border.width
        visible: false
        horizontalAlignment: Text.AlignCenter
        font.pixelSize: ThemeManager.sizes.fontMedium
        color: ThemeManager.colors.textPrimary
        selectByMouse: true
        
        background: Rectangle {
            color: ThemeManager.colors.backgroundHover
            border.width: ThemeManager.sizes.borderThin
            border.color: ThemeManager.colors.borderFocus
            radius: ThemeManager.sizes.radiusMedium
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
    
    MouseArea {
        id: dragArea
        anchors.fill: parent
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
    
    MouseArea {
        id: externalClickDetector
        anchors.fill: parent
        enabled: valueInput.visible
        propagateComposedEvents: false
        z: -1
    }
    
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