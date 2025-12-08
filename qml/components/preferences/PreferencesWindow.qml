// import QtQuick
// import QtQuick.Layouts
// import QtQmlBaseApp.Core

// Window {
//     id: root
//     width: 900
//     height: 700
//     minimumWidth: 800
//     minimumHeight: 600
//     title: "Preferences"
//     color: ThemeManager.getComponentColor("preferencesWindow", "background")
//     modality: Qt.ApplicationModal
    
//     property string currentCategory: "general"
    
//     // Category definitions with their components
//     property var categoryData: [
//         { id: "general", label: "General", component: interfaceComponent },
//         { id: "theme", label: "Theme Selector", component: themeSelectorComponent },
//         { id: "editor", label: "Theme Editor", component: themeEditorComponent },
//         { id: "keymaps", label: "Keyboard Shortcuts", component: keymapsComponent },
//         { id: "componentsLib", label: "Components Lib", component: componentsLibComponent }
//     ]
    
//     // Components definitions
//     Component {
//         id: interfaceComponent
//         Interface {}
//     }
    
//     Component {
//         id: themeSelectorComponent
//         ThemeSelector {}
//     }
    
//     Component {
//         id: themeEditorComponent
//         ThemeEditor {}
//     }
    
//     Component {
//         id: keymapsComponent
//         Keymaps {}
//     }

//     Component {
//         id: componentsLibComponent
//         ComponentsLib {}
//     }

    
//     RowLayout {
//         anchors.fill: parent
//         spacing: 0
        
//         // Sidebar
//         Rectangle {
//             Layout.preferredWidth: ThemeManager.getComponentScaledInt("preferencesWindow", "sidebarWidth")
//             Layout.fillHeight: true
//             color: ThemeManager.getComponentColor("preferencesWindow", "sidebarBackground")
            
//             Column {
//                 anchors.fill: parent
//                 anchors.margins: ThemeManager.spacingMedium
//                 spacing: ThemeManager.getScaledInt("spacing.small")
                
//                 Repeater {
//                     model: categoryData
                    
//                     CategoryButton {
//                         text: modelData.label
//                         isSelected: root.currentCategory === modelData.id
//                         onClicked: root.currentCategory = modelData.id
//                     }
//                 }
//             }
            
//             // Sidebar right border
//             Rectangle {
//                 anchors.right: parent.right
//                 width: ThemeManager.borderThin
//                 height: parent.height
//                 color: ThemeManager.getColor("colors.border.primary")
//             }
//         }
        
//         // Content area
//         Rectangle {
//             Layout.fillWidth: true
//             Layout.fillHeight: true
//             color: ThemeManager.getComponentColor("preferencesWindow", "background")
            
//             ScrollableContentArea {
//                 anchors.fill: parent
                
//                 contentItem: Component {
//                     Item {
//                         width: parent.width
//                         height: contentColumn.height
                        
//                         Column {
//                             id: contentColumn
//                             width: parent.width
                            
//                             Repeater {
//                                 model: categoryData
                                
//                                 Loader {
//                                     width: parent.width
//                                     sourceComponent: modelData.component
//                                     visible: root.currentCategory === modelData.id
//                                     active: visible
                                    
//                                     onLoaded: {
//                                         if (item) {
//                                             height = Qt.binding(function() { 
//                                                 if (!item) return 0
//                                                 return item.implicitHeight > 0 ? item.implicitHeight : item.height 
//                                             })
//                                         }
//                                     }
//                                 }
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
    
//     // Category Button Component
//     component CategoryButton: Rectangle {
//         property string text
//         property bool isSelected: false
//         signal clicked()
        
//         width: parent.width
//         height: ThemeManager.getScaledInt("spacing.xxxlarge")
//         radius: ThemeManager.radiusMedium
//         color: isSelected ? ThemeManager.getColor("colors.primary.base") : 
//                (mouseArea.containsMouse ? ThemeManager.getColor("colors.surface.hover") : "transparent")
        
//         Text {
//             anchors.centerIn: parent
//             text: parent.text
//             color: parent.isSelected ? 
//                 ThemeManager.getColor("colors.text.onPrimary") : 
//                 ThemeManager.getColor("colors.text.primary")
//             font.pixelSize: ThemeManager.fontSizeMedium
//         }
        
//         MouseArea {
//             id: mouseArea
//             anchors.fill: parent
//             hoverEnabled: true
//             onClicked: parent.clicked()
//         }
        
//         Behavior on color {
//             ColorAnimation { duration: ThemeManager.get("animation.duration.normal") }
//         }
//     }
// }








// import QtQuick
// import QtQuick.Layouts
// import QtQmlBaseApp.Core

// Window {
//     id: root
//     width: 900
//     height: 700
//     minimumWidth: 800
//     minimumHeight: 600
//     title: "Preferences"
//     color: ThemeManager.prefWindow.background
//     modality: Qt.ApplicationModal

//     //
//     // ========= CATÉGORIES =========
//     //
//     property var categoryData: [
//         { id: "general", label: "General", component: interfaceComponent },
//         { id: "theme",   label: "Theme Selector", component: themeSelectorComponent },
//         { id: "editor",  label: "Theme Editor", component: themeEditorComponent }
//     ]

//     property string currentCategory: "general"

//     //
//     // ========= COMPOSANTS DYNAMIQUES =========
//     //
//     Component { id: interfaceComponent; Interface {} }
//     Component { id: themeSelectorComponent; ThemeSelector {} }
//     Component { id: themeEditorComponent; ThemeEditor {} }

//     RowLayout {
//         anchors.fill: parent
//         spacing: 0

//         //
//         // ========= SIDEBAR =========
//         //
//         Rectangle {
//             Layout.preferredWidth: ThemeManager.prefWindow.sidebarWidth
//             Layout.fillHeight: true
//             color: ThemeManager.prefWindow.sidebarBackground

//             Column {
//                 anchors.fill: parent
//                 anchors.margins: ThemeManager.sizes.medium
//                 spacing: ThemeManager.sizes.small

//                 Repeater {
//                     model: categoryData

//                     CategoryButton {
//                         text: modelData.label
//                         isSelected: root.currentCategory === modelData.id
//                         onClicked: root.currentCategory = modelData.id
//                     }
//                 }
//             }

//             Rectangle {
//                 anchors.right: parent.right
//                 width: ThemeManager.sizes.borderThin
//                 height: parent.height
//                 color: ThemeManager.colors.borderPrimary
//             }
//         }

//         //
//         // ========= CONTENT AREA =========
//         //
//         Rectangle {
//             Layout.fillWidth: true
//             Layout.fillHeight: true
//             color: ThemeManager.prefWindow.background

//             ScrollableContentArea {
//                 anchors.fill: parent

//                 contentItem: Component {
//                     Item {
//                         width: parent.width
//                         height: contentColumn.height

//                         Column {
//                             id: contentColumn
//                             width: parent.width

//                             Repeater {
//                                 model: categoryData

//                                 Loader {
//                                     width: parent.width
//                                     sourceComponent: modelData.component
//                                     visible: root.currentCategory === modelData.id
//                                     active: visible

//                                     onLoaded: {
//                                         if (item) {
//                                             height = Qt.binding(function() {
//                                                 return item.implicitHeight > 0 ? item.implicitHeight : item.height
//                                             })
//                                         }
//                                     }
//                                 }
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     //
//     // ========= CATEGORY BUTTON =========
//     //
//     component CategoryButton: Rectangle {
//         property string text
//         property bool isSelected: false
//         signal clicked()

//         width: parent.width
//         height: ThemeManager.sizes.xxxlarge
//         radius: ThemeManager.sizes.radiusMedium

//         color: isSelected
//                ? ThemeManager.colors.primaryBase
//                : (mouseArea.containsMouse
//                   ? ThemeManager.colors.surfaceHover
//                   : "transparent")

//         Text {
//             anchors.centerIn: parent
//             text: parent.text
//             color: parent.isSelected
//                    ? ThemeManager.colors.textOnPrimary
//                    : ThemeManager.colors.textPrimary
//             font.pixelSize: ThemeManager.sizes.fontMedium
//         }

//         MouseArea {
//             id: mouseArea
//             anchors.fill: parent
//             hoverEnabled: true
//             onClicked: parent.clicked()
//         }

//         Behavior on color {
//             ColorAnimation { duration: ThemeManager.sizes.animNormal }
//         }
//     }
// }



import QtQuick
import QtQuick.Layouts
import QtQmlBaseApp.Core

Window {
    id: root
    width: 900
    height: 700
    minimumWidth: 800
    minimumHeight: 600
    title: "Preferences - DEBUG VIEW"
    color: ThemeManager.surface.color.bgTertiary
    modality: Qt.ApplicationModal

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: ThemeManager.surface.spacingLarge
        spacing: ThemeManager.surface.spacingLarge

        //
        // ==== TITRE ====
        //
        Text {
            text: "Theme Debug Preview"
            color: ThemeManager.font.color.textPrimary
            font.pixelSize: ThemeManager.font.sizeXxlarge
            font.weight: ThemeManager.font.weight.bold
        }

        //
        // ==== BOX COLORS ====
        //
        RowLayout {
            Layout.fillWidth: true
            spacing: ThemeManager.surface.spacingMedium

            Rectangle {
                Layout.fillWidth: true
                height: 120
                radius: ThemeManager.surface.radiusMedium
                color: ThemeManager.surface.color.primBase

                Text {
                    anchors.centerIn: parent
                    text: "Primary"
                    color: ThemeManager.font.color.textOnPrimary
                    font.pixelSize: ThemeManager.font.sizeLarge
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 120
                radius: ThemeManager.surface.radiusMedium
                color: ThemeManager.surface.color.surfSecondary

                Text {
                    anchors.centerIn: parent
                    text: "Secondary"
                    color: ThemeManager.font.color.textPrimary
                    font.pixelSize: ThemeManager.font.sizeLarge
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 120
                radius: ThemeManager.surface.radiusMedium
                color: ThemeManager.surface.color.accentBase

                Text {
                    anchors.centerIn: parent
                    text: "Accent"
                    color: ThemeManager.font.color.textOnPrimary
                    font.pixelSize: ThemeManager.font.sizeLarge
                }
            }
        }

        //
        // ==== TEXT PREVIEW ====
        //
        ColumnLayout {
            Layout.fillWidth: true
            spacing: ThemeManager.surface.spacingSmall

            Text {
                text: "Text Primary"
                color: ThemeManager.font.color.textPrimary
                font.pixelSize: ThemeManager.font.sizeLarge
            }

            Text {
                text: "Text Secondary"
                color: ThemeManager.font.color.textSecondary
                font.pixelSize: ThemeManager.font.sizeLarge
            }

            Text {
                text: "Text Tertiary"
                color: ThemeManager.font.color.textTertiary
                font.pixelSize: ThemeManager.font.sizeLarge
            }

            Text {
                text: "Text Disabled"
                color: ThemeManager.font.color.textDisabled
                font.pixelSize: ThemeManager.font.sizeLarge
            }
        }

        //
        // ==== STATUS COLORS ====
        //
        RowLayout {
            Layout.fillWidth: true
            spacing: ThemeManager.surface.spacingMedium

            Rectangle {
                Layout.fillWidth: true
                height: 80
                radius: ThemeManager.surface.radiusSmall
                color: ThemeManager.surface.color.statSuccess

                Text {
                    anchors.centerIn: parent
                    text: "Success"
                    color: "white"
                    font.pixelSize: ThemeManager.font.sizeLarge
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 80
                radius: ThemeManager.surface.radiusSmall
                color: ThemeManager.surface.color.statWarning

                Text {
                    anchors.centerIn: parent
                    text: "Warning"
                    color: "black"
                    font.pixelSize: ThemeManager.font.sizeLarge
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 80
                radius: ThemeManager.surface.radiusSmall
                color: ThemeManager.surface.color.statError

                Text {
                    anchors.centerIn: parent
                    text: "Error"
                    color: "white"
                    font.pixelSize: ThemeManager.font.sizeLarge
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 80
                radius: ThemeManager.surface.radiusSmall
                color: ThemeManager.surface.color.statInfo

                Text {
                    anchors.centerIn: parent
                    text: "Info"
                    color: "white"
                    font.pixelSize: ThemeManager.font.sizeLarge
                }
            }
        }

        //
        // ==== BORDER & SURFACE STATES ====
        //
        Text {
            text: "Surface States & Borders"
            color: ThemeManager.font.color.textPrimary
            font.pixelSize: ThemeManager.font.sizeXlarge
            font.weight: ThemeManager.font.weight.semibold
            Layout.topMargin: ThemeManager.surface.spacingLarge
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: ThemeManager.surface.spacingMedium

            Rectangle {
                Layout.fillWidth: true
                height: 80
                radius: ThemeManager.surface.radiusSmall
                color: ThemeManager.surface.color.surfPrimary
                border.width: ThemeManager.border.widthThin
                border.color: ThemeManager.border.color.borderPrimary

                Text {
                    anchors.centerIn: parent
                    text: "Primary"
                    color: ThemeManager.font.color.textPrimary
                    font.pixelSize: ThemeManager.font.sizeMedium
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 80
                radius: ThemeManager.surface.radiusSmall
                color: ThemeManager.surface.color.surfHover
                border.width: ThemeManager.border.widthThin
                border.color: ThemeManager.border.color.borderSecondary

                Text {
                    anchors.centerIn: parent
                    text: "Hover"
                    color: ThemeManager.font.color.textPrimary
                    font.pixelSize: ThemeManager.font.sizeMedium
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 80
                radius: ThemeManager.surface.radiusSmall
                color: ThemeManager.surface.color.surfActive
                border.width: ThemeManager.border.widthMedium
                border.color: ThemeManager.border.color.borderFocus

                Text {
                    anchors.centerIn: parent
                    text: "Active"
                    color: ThemeManager.font.color.textPrimary
                    font.pixelSize: ThemeManager.font.sizeMedium
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 80
                radius: ThemeManager.surface.radiusSmall
                color: ThemeManager.surface.color.surfDisabled
                border.width: ThemeManager.border.widthThin
                border.color: ThemeManager.border.color.borderDisabled

                Text {
                    anchors.centerIn: parent
                    text: "Disabled"
                    color: ThemeManager.font.color.textDisabled
                    font.pixelSize: ThemeManager.font.sizeMedium
                }
            }
        }

        Item { Layout.fillHeight: true }
    }
}
