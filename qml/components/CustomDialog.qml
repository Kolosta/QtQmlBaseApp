import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQmlBaseApp.Core

Dialog {
    id: root
    modal: true
    
    Component.onCompleted: {
        mainContent.forceActiveFocus()
    }

    implicitWidth: 400
    padding: 20
    title: ""

    property string dialogTitle: "Title"
    property string text: ""
    property string acceptButtonText: "OK"
    property string cancelButtonText: "Cancel"
    property bool showCancelButton: true
    property bool strictMode: false 

    default property alias body: contentContainer.data
    
    property color borderFlashColor: ThemeManager.accent
    property real borderFlashOpacity: 0.0
    property bool allowClose: false

    // Toujours permettre la fermeture par code, on gérera manuellement le strict mode
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    // Interception de la tentative de fermeture
    onAboutToHide: {
        if (strictMode && !allowClose) {
            //Log 
            console.log("CustomDialog: Strict mode active, preventing close.")
            // Empêcher la fermeture
            close()
            open()
            // Déclencher l'animation de flash
            borderFlashAnimation.restart()
            // Redonne le focus
            mainContent.forceActiveFocus()
        }
        console.log("CustomDialog: Dialog closed.")
    }

    onOpened: {
        allowClose = false
    }
    
    function acceptDialog() {
        allowClose = true
        root.accept()
    }
    
    function rejectDialog() {
        allowClose = true
        root.reject()
    }

    // Animation de flash de la bordure
    SequentialAnimation {
        id: borderFlashAnimation
        
        // Flash rapide 4 fois
        loops: 4
        
        ParallelAnimation {
            NumberAnimation {
                target: root
                property: "borderFlashOpacity"
                from: 0.0
                to: 1.0
                duration: 50
                easing.type: Easing.OutQuad
            }
        }
        
        ParallelAnimation {
            NumberAnimation {
                target: root
                property: "borderFlashOpacity"
                from: 1.0
                to: 0.0
                duration: 100
                easing.type: Easing.InQuad
            }
        }
    }

    // Overlay (Fond grisé) - version simplifiée sans MouseArea
    Overlay.modal: Rectangle {
        color: "#80000000"
    }

    // Arrière-plan avec bordure qui clignote
    background: Rectangle {
        id: bgRect
        color: ThemeManager.surface
        radius: ThemeManager.radius
        
        // Bordure normale
        border.width: ThemeManager.borderWidth
        border.color: ThemeManager.border
        
        // Bordure de flash par-dessus
        Rectangle {
            anchors.fill: parent
            // anchors.margins: -2
            radius: parent.radius
            color: "transparent"
            border.width: 1
            border.color: root.borderFlashColor
            opacity: root.borderFlashOpacity
        }
    }

    contentItem: ColumnLayout {
        id: mainContent
        spacing: 20
        focus: true
        
        // Gestion Clavier : Entrée valide, Escape ferme (sauf en strict mode)
        Keys.onPressed: (event) => {
            if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
                root.acceptDialog()
                event.accepted = true
            } else if (event.key === Qt.Key_Escape) {
                if (true) { // Escape ferme dans tout les cas
                    root.rejectDialog()
                    event.accepted = true
                } else if (root.strictMode) {
                    // En mode strict, Escape déclenche le flash
                    borderFlashAnimation.restart()
                    event.accepted = true 
                } else {
                    // En mode normal, Escape ferme
                    root.rejectDialog()
                    event.accepted = true
                }
            }
        }

        Text {
            text: root.dialogTitle
            font.pixelSize: ThemeManager.fontSizeMedium
            font.bold: true
            color: ThemeManager.text
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft
        }

        ColumnLayout {
            id: contentContainer
            Layout.fillWidth: true
            spacing: 10

            Text {
                visible: root.text !== ""
                text: root.text
                color: ThemeManager.text
                wrapMode: Text.WordWrap
                font.pixelSize: ThemeManager.fontSizeSmall
                Layout.fillWidth: true
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
            spacing: 10

            Item { Layout.fillWidth: true }

            Button {
                visible: root.showCancelButton
                text: root.cancelButtonText
                onClicked: root.rejectDialog()
                
                background: Rectangle {
                    color: parent.pressed ? ThemeManager.surfaceHover : ThemeManager.surface
                    border.width: ThemeManager.borderWidth
                    border.color: ThemeManager.border
                    radius: ThemeManager.radiusSmall
                }
                contentItem: Text {
                    text: parent.text
                    color: ThemeManager.text
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Button {
                text: root.acceptButtonText
                onClicked: root.acceptDialog()

                background: Rectangle {
                    color: parent.pressed ? ThemeManager.primaryHover : ThemeManager.primary
                    radius: ThemeManager.radiusSmall
                }
                contentItem: Text {
                    text: parent.text
                    color: "white"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }
}