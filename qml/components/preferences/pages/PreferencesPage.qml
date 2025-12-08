import QtQuick
import QtQuick.Layouts
import QtQmlBaseApp.Core

Rectangle {
    id: root
    
    property alias content: contentLoader.sourceComponent
    property string pageTitle: ""
    
    color: ThemeManager.preferencesWindow.contentBackground
    
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: ThemeManager.surface.spacingXlarge
        spacing: ThemeManager.surface.spacingLarge
        
        // Titre de la page
        Text {
            text: root.pageTitle
            color: ThemeManager.font.color.textPrimary
            font.pixelSize: ThemeManager.font.sizeXxlarge
            font.weight: ThemeManager.font.weight.bold
        }
        
        // Séparateur
        Rectangle {
            Layout.fillWidth: true
            height: ThemeManager.border.widthThin
            color: ThemeManager.border.color.borderPrimary
        }
        
        // Contenu de la page
        Loader {
            id: contentLoader
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}