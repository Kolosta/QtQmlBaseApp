import QtQuick
import QtQuick.Controls
import QtQmlBaseApp.Core
import "components"
import "views"

ApplicationWindow {
    id: root
    width: 800
    height: 600
    visible: true
    visibility: Window.Maximized
    title: qsTr("QtQmlBaseApp - Vector Management Application")
    color: ThemeManager.background.color.bgPrimary
    
    Behavior on color {
        ColorAnimation { duration: ThemeManager.sizes.animNormal }
    }
    
    header: MenuBar {
        onPreferencesRequested: preferencesWindow.show()
    }
    
    MainView {
        anchors.fill: parent
    }
    
    PreferencesWindow {
        id: preferencesWindow
    }
}