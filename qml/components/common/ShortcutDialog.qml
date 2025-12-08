import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

Dialog {
    id: root
    modal: true
    implicitWidth: 400
    padding: ThemeManager.sizes.spacingLarge
    
    property string actionId: ""
    property string actionLabel: ""
    property string currentShortcut: ""
    property string newShortcut: ""
    property bool recording: false
    
    title: "Set Shortcut"
    
    onOpened: {
        newShortcut = currentShortcut
        recording = false
        shortcutInput.forceActiveFocus()
    }
    
    background: Rectangle {
        color: ThemeManager.colors.backgroundPrimary
        border.width: ThemeManager.sizes.borderThin
        border.color: ThemeManager.colors.borderPrimary
        radius: ThemeManager.sizes.radiusMedium
    }
    
    Overlay.modal: Rectangle {
        color: ThemeManager.colors.surfacePrimary
    }
    
    contentItem: ColumnLayout {
        spacing: ThemeManager.sizes.spacingMedium
        
        Text {
            text: "Press a key combination for:"
            font.pixelSize: ThemeManager.sizes.fontMedium
            color: ThemeManager.colors.textPrimary
        }
        
        Text {
            text: root.actionLabel
            font.pixelSize: ThemeManager.sizes.fontLarge
            font.bold: true
            color: ThemeManager.colors.textPrimary
            Layout.fillWidth: true
        }
        
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            color: ThemeManager.colors.surfacePrimary
            border.width: ThemeManager.sizes.borderThin
            border.color: root.recording ? 
                ThemeManager.colors.accentBase :
                ThemeManager.colors.borderPrimary
            radius: ThemeManager.sizes.radiusMedium
            
            Item {
                id: shortcutInput
                anchors.fill: parent
                focus: true
                
                property var pressedKeys: []
                property string modifiers: ""
                
                Keys.onPressed: function(event) {
                    root.recording = true
                    
                    // Build modifier string
                    var mods = []
                    if (event.modifiers & Qt.ControlModifier) mods.push("Ctrl")
                    if (event.modifiers & Qt.AltModifier) mods.push("Alt")
                    if (event.modifiers & Qt.ShiftModifier) mods.push("Shift")
                    if (event.modifiers & Qt.MetaModifier) mods.push("Meta")
                    
                    // Get key name
                    var keyName = ""
                    if (event.key >= Qt.Key_A && event.key <= Qt.Key_Z) {
                        keyName = String.fromCharCode(event.key)
                    } else if (event.key >= Qt.Key_0 && event.key <= Qt.Key_9) {
                        keyName = String.fromCharCode(event.key)
                    } else if (event.key >= Qt.Key_F1 && event.key <= Qt.Key_F12) {
                        keyName = "F" + (event.key - Qt.Key_F1 + 1)
                    } else {
                        // Map special keys
                        var keyMap = {
                            [Qt.Key_Escape]: "Esc",
                            [Qt.Key_Tab]: "Tab",
                            [Qt.Key_Backtab]: "Backtab",
                            [Qt.Key_Backspace]: "Backspace",
                            [Qt.Key_Return]: "Return",
                            [Qt.Key_Enter]: "Enter",
                            [Qt.Key_Insert]: "Insert",
                            [Qt.Key_Delete]: "Delete",
                            [Qt.Key_Pause]: "Pause",
                            [Qt.Key_Home]: "Home",
                            [Qt.Key_End]: "End",
                            [Qt.Key_Left]: "Left",
                            [Qt.Key_Up]: "Up",
                            [Qt.Key_Right]: "Right",
                            [Qt.Key_Down]: "Down",
                            [Qt.Key_PageUp]: "PageUp",
                            [Qt.Key_PageDown]: "PageDown",
                            [Qt.Key_Space]: "Space",
                            [Qt.Key_Plus]: "+",
                            [Qt.Key_Minus]: "-",
                            [Qt.Key_Equal]: "=",
                            [Qt.Key_Comma]: ",",
                            [Qt.Key_Period]: ".",
                            [Qt.Key_Slash]: "/",
                            [Qt.Key_Backslash]: "\\",
                            [Qt.Key_BracketLeft]: "[",
                            [Qt.Key_BracketRight]: "]",
                            [Qt.Key_Semicolon]: ";",
                            [Qt.Key_Apostrophe]: "'",
                            [Qt.Key_QuoteLeft]: "`"
                        }
                        keyName = keyMap[event.key] || ""
                    }
                    
                    // Build shortcut string
                    if (keyName !== "" && 
                        event.key !== Qt.Key_Control && 
                        event.key !== Qt.Key_Alt && 
                        event.key !== Qt.Key_Shift && 
                        event.key !== Qt.Key_Meta) {
                        
                        if (mods.length > 0) {
                            root.newShortcut = mods.join("+") + "+" + keyName
                        } else {
                            root.newShortcut = keyName
                        }
                    }
                    
                    event.accepted = true
                }
                
                Text {
                    anchors.centerIn: parent
                    text: root.recording ? 
                        (root.newShortcut || "Press keys...") : 
                        (root.currentShortcut || "Not set")
                    color: root.recording ? 
                        ThemeManager.colors.accentBase :
                        ThemeManager.colors.textPrimary
                    font.pixelSize: ThemeManager.sizes.fontLarge
                    font.bold: root.recording
                }
            }
        }
        
        // Conflict warning
        Text {
            visible: {
                if (!root.newShortcut || root.newShortcut === root.currentShortcut)
                    return false
                return !KeymapManager.isShortcutAvailable(root.newShortcut, root.actionId)
            }
            
            text: {
                var conflictAction = KeymapManager.getActionUsingShortcut(root.newShortcut)
                if (conflictAction) {
                    var actions = KeymapManager.getAllActions()
                    if (actions[conflictAction]) {
                        return "⚠ Already used by: " + actions[conflictAction].label
                    }
                }
                return ""
            }
            
            color: ThemeManager.colors.statusWarning
            font.pixelSize: ThemeManager.sizes.fontSmall
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
        }
        
        // Buttons
        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
            spacing: ThemeManager.sizes.spacingMedium
            
            Item { Layout.fillWidth: true }
            
            Button {
                text: "Clear"
                
                background: Rectangle {
                    color: parent.pressed ? 
                        ThemeManager.colors.surfaceActive :
                        parent.hovered ? 
                        ThemeManager.colors.surfaceHover :
                        ThemeManager.colors.surfacePrimary
                    border.width: ThemeManager.sizes.borderThin
                    border.color: ThemeManager.colors.borderPrimary
                    radius: ThemeManager.sizes.radiusSmall
                }
                
                contentItem: Text {
                    text: parent.text
                    color: ThemeManager.colors.textPrimary
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                
                onClicked: {
                    root.newShortcut = ""
                    root.recording = false
                }
            }
            
            Button {
                text: "Cancel"
                
                background: Rectangle {
                    color: parent.pressed ? 
                        ThemeManager.colors.surfaceActive :
                        parent.hovered ? 
                        ThemeManager.colors.surfaceHover :
                        ThemeManager.colors.surfacePrimary
                    border.width: ThemeManager.sizes.borderThin
                    border.color: ThemeManager.colors.borderPrimary
                    radius: ThemeManager.sizes.radiusSmall
                }
                
                contentItem: Text {
                    text: parent.text
                    color: ThemeManager.colors.textPrimary
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                
                onClicked: root.reject()
            }
            
            Button {
                text: "OK"
                
                background: Rectangle {
                    color: parent.pressed ? 
                        ThemeManager.colors.primaryActive :
                        ThemeManager.colors.primaryBase
                    radius: ThemeManager.sizes.radiusSmall
                }
                
                contentItem: Text {
                    text: parent.text
                    color: ThemeManager.colors.textOnPrimary
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                
                onClicked: {
                    KeymapManager.setShortcut(root.actionId, root.newShortcut)
                    root.accept()
                }
            }
        }
    }
}