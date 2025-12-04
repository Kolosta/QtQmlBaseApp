import QtQuick
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
    
    // Category definitions with their components
    property var categoryData: [
        { id: "general", label: "General", component: interfaceComponent },
        { id: "theme", label: "Theme Selector", component: themeSelectorComponent },
        { id: "editor", label: "Theme Editor", component: themeEditorComponent },
        { id: "componentsLib", label: "Components Lib", component: componentsLibComponent }
    ]
    
    // Components definitions
    Component {
        id: interfaceComponent
        Interface {}
    }
    
    Component {
        id: themeSelectorComponent
        ThemeSelector {}
    }
    
    Component {
        id: themeEditorComponent
        ThemeEditor {}
    }

    Component {
        id: componentsLibComponent
        ComponentsLib {}
    }

    
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
                
                Repeater {
                    model: categoryData
                    
                    CategoryButton {
                        text: modelData.label
                        isSelected: root.currentCategory === modelData.id
                        onClicked: root.currentCategory = modelData.id
                    }
                }
            }
            
            // Sidebar right border
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
            
            ScrollableContentArea {
                anchors.fill: parent
                
                contentItem: Component {
                    Item {
                        width: parent.width
                        height: contentColumn.height
                        
                        Column {
                            id: contentColumn
                            width: parent.width
                            
                            Repeater {
                                model: categoryData
                                
                                Loader {
                                    width: parent.width
                                    sourceComponent: modelData.component
                                    visible: root.currentCategory === modelData.id
                                    active: visible
                                    
                                    // Ensure proper height binding
                                    onLoaded: {
                                        if (item) {
                                            height = Qt.binding(function() { 
                                                if (!item) return 0
                                                return item.implicitHeight > 0 ? item.implicitHeight : item.height 
                                            })
                                        }
                                    }
                                }
                            }
                        }
                    }
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
}