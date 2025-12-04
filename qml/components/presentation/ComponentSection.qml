import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

Item {
    id: root
    
    property string title: ""
    property bool collapsed: true
    
    default property alias content: contentContainer.data
    
    implicitWidth: parent ? parent.width : 400
    implicitHeight: mainLayout.implicitHeight
    
    Layout.fillWidth: true
    
    // Global container with border and radius
    Rectangle {
        width: parent.width
        height: mainLayout.implicitHeight
        color: ThemeManager.surface
        border.width: ThemeManager.borderWidth
        border.color: ThemeManager.border
        radius: ThemeManager.radius
        
        ColumnLayout {
            id: mainLayout
            width: parent.width
            spacing: 0
            
            // Header
            MouseArea {
                Layout.fillWidth: true
                Layout.preferredHeight: 45
                cursorShape: Qt.PointingHandCursor
                onClicked: root.collapsed = !root.collapsed
                
                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 15
                    anchors.rightMargin: 15
                    spacing: 10
                    
                    // Chevron icon
                    Item {
                        Layout.preferredWidth: 10
                        Layout.preferredHeight: 10
                        Item {
                            width: 10
                            height: 10
                            Button {
                                anchors.centerIn: parent
                                background: Item { }
                                icon.source: root.collapsed ? "qrc:/resources/icons/chevron-right.svg" : "qrc:/resources/icons/chevron-down.svg"
                                icon.width: 10
                                icon.height: 10
                                icon.color: ThemeManager.text
                                enabled: false
                            }
                        }
                    }
                    
                    // Title
                    Text {
                        Layout.fillWidth: true
                        text: root.title
                        font.pixelSize: ThemeManager.fontSizeLarge
                        color: ThemeManager.text
                    }
                }
            }
            
            // Content container
            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: root.collapsed ? 0 : contentContainer.implicitHeight
                clip: true
                visible: Layout.preferredHeight > 0
                
                ColumnLayout {
                    id: contentContainer
                    width: parent.width
                    spacing: 0
                }
            }
        }
    }
}