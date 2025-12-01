import QtQuick
import QtQuick.Controls
import QtQmlBaseApp.Core

// Roue de couleur (Hue + Saturation)
Item {
    id: root
    width: 200
    height: 200
    
    property real hue: 0.0        // 0.0 - 1.0
    property real saturation: 1.0 // 0.0 - 1.0
    property real value: 1.0      // 0.0 - 1.0
    
    signal colorChanged()
    
    // Canvas pour dessiner la roue de couleur
    Canvas {
        id: canvas
        anchors.fill: parent
        
        onPaint: {
            var ctx = getContext("2d")
            var centerX = width / 2
            var centerY = height / 2
            var radius = Math.min(width, height) / 2
            
            ctx.clearRect(0, 0, width, height)
            
            // Dessiner la roue de couleur
            for (var angle = 0; angle < 360; angle += 1) {
                for (var r = 0; r < radius; r += 1) {
                    var hue = angle / 360.0
                    var sat = r / radius
                    
                    ctx.fillStyle = Qt.hsva(hue, sat, root.value, 1.0)
                    
                    var rad = angle * Math.PI / 180
                    var x = centerX + r * Math.cos(rad)
                    var y = centerY + r * Math.sin(rad)
                    
                    ctx.fillRect(x, y, 2, 2)
                }
            }
        }
        
        // Redessiner quand value change
        Connections {
            target: root
            function onValueChanged() {
                canvas.requestPaint()
            }
        }
    }
    
    // Curseur de sélection
    Rectangle {
        id: cursor
        width: 12
        height: 12
        radius: 6
        border.width: 2
        border.color: "white"
        color: "transparent"
        
        property real angle: root.hue * 360
        property real distance: root.saturation * (root.width / 2)
        
        x: root.width / 2 + distance * Math.cos(angle * Math.PI / 180) - width / 2
        y: root.height / 2 + distance * Math.sin(angle * Math.PI / 180) - height / 2
    }
    
    MouseArea {
        anchors.fill: parent
        
        function updateColor(mouse) {
            var centerX = width / 2
            var centerY = height / 2
            var dx = mouse.x - centerX
            var dy = mouse.y - centerY
            var distance = Math.sqrt(dx * dx + dy * dy)
            var maxRadius = Math.min(width, height) / 2
            
            if (distance <= maxRadius) {
                var angle = Math.atan2(dy, dx) * 180 / Math.PI
                if (angle < 0) angle += 360
                
                root.hue = angle / 360.0
                root.saturation = Math.min(1.0, distance / maxRadius)
                root.colorChanged()
            }
        }
        
        onPressed: function(mouse) { updateColor(mouse) }
        onPositionChanged: function(mouse) { if (pressed) updateColor(mouse) }
    }
}