import QtQuick
import QtQuick.Controls
import QtQmlBaseApp.Core

Rectangle {
    id: root
    color: "transparent"
    
    property alias contentItem: contentLoader.sourceComponent
    property int horizontalMargin: 20
    
    // Scrollbar area on the right
    Item {
        id: scrollbarArea
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: root.horizontalMargin
        
        // MouseArea to detect hover over the scrollbar zone
        MouseArea {
            id: scrollbarZoneHover
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            acceptedButtons: Qt.NoButton
        }
        
        ScrollBar {
            id: scrollBar
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: scrollbarZoneHover.containsMouse ? 10 : 6
            
            // Only show if content is scrollable
            visible: flickable.contentHeight > flickable.height
            policy: ScrollBar.AsNeeded
            active: flickable.moving || hovered || scrollbarZoneHover.containsMouse
            
            contentItem: Rectangle {
                implicitWidth: scrollBar.width
                radius: scrollBar.width / 2
                color: ThemeManager.surface
                opacity: scrollBar.pressed ? 0.9 : 
                         (scrollBar.hovered || scrollbarZoneHover.containsMouse) ? 0.7 : 0.5
                
                Behavior on opacity {
                    NumberAnimation { duration: ThemeManager.animationDuration }
                }
            }
            
            Behavior on width {
                NumberAnimation { duration: ThemeManager.animationDuration }
            }
        }
    }
    
    // Main flickable area
    Flickable {
        id: flickable
        anchors.fill: parent
        anchors.leftMargin: root.horizontalMargin
        anchors.rightMargin: root.horizontalMargin
        
        contentWidth: width
        contentHeight: contentLoader.item ? contentLoader.item.height : 0
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        
        interactive: false // Disable drag/flick gestures
        
        ScrollBar.vertical: scrollBar
        
        Loader {
            id: contentLoader
            width: parent.width
        }
        
        // Mouse wheel handling only
        MouseArea {
            anchors.fill: parent
            propagateComposedEvents: true
            
            onWheel: function(wheel) {
                var delta = wheel.angleDelta.y
                var scrollAmount = 120 // Pixels per wheel step
                
                if (delta > 0) {
                    flickable.contentY = Math.max(0, flickable.contentY - scrollAmount)
                } else if (delta < 0) {
                    var maxContentY = Math.max(0, flickable.contentHeight - flickable.height)
                    flickable.contentY = Math.min(maxContentY, flickable.contentY + scrollAmount)
                }
                
                wheel.accepted = true
            }
            
            onPressed: function(mouse) {
                mouse.accepted = false
            }
        }
    }
}