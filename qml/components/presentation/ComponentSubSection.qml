import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

Item {
    id: root
    
    property string title: ""
    property bool collapsed: true
    property int indentSize: 15
    
    default property alias content: contentContainer.data
    
    implicitWidth: parent ? parent.width : 400
    implicitHeight: mainLayout.implicitHeight
    
    Layout.fillWidth: true
    
    ColumnLayout {
        id: mainLayout
        width: parent.width
        spacing: 0
        
        // SubSection Header (title + chevron)
        MouseArea {
            Layout.fillWidth: true
            Layout.preferredHeight: 35
            cursorShape: Qt.PointingHandCursor
            onClicked: root.collapsed = !root.collapsed
            
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: ThemeManager.spacingMedium + root.indentSize
                anchors.rightMargin: ThemeManager.spacingMedium
                spacing: 8
                
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
                            icon.color: ThemeManager.textPrimary
                            enabled: false
                        }
                    }
                }
                
                // Title
                Text {
                    Layout.fillWidth: true
                    text: root.title
                    font.pixelSize: ThemeManager.fontSizeMedium
                    color: ThemeManager.textPrimary
                }
            }
        }
        
        // Content container
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: root.collapsed ? 0 : (contentContainer.implicitHeight + ThemeManager.spacingMedium * 2)
            Layout.leftMargin: ThemeManager.borderThin
            Layout.rightMargin: ThemeManager.borderThin
            Layout.bottomMargin: ThemeManager.borderThin
            clip: true
            visible: !root.collapsed
            
            Rectangle {
                id: contentBg
                width: parent.width
                height: parent.height
                color: ThemeManager.backgroundPrimary
                bottomLeftRadius: ThemeManager.radiusMedium
                bottomRightRadius: ThemeManager.radiusMedium
                
                ColumnLayout {
                    id: contentContainer
                    width: parent.width - (root.indentSize + ThemeManager.spacingMedium) - ThemeManager.spacingMedium
                    anchors.left: parent.left
                    anchors.leftMargin: root.indentSize + ThemeManager.spacingMedium
                    anchors.top: parent.top
                    anchors.topMargin: ThemeManager.spacingSmall
                    spacing: ThemeManager.spacingMedium
                }
            }
        }
    }
}