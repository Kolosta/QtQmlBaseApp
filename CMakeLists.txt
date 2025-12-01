cmake_minimum_required(VERSION 3.16)
project(QtQmlBaseApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Qml Core QuickControls2)

qt_standard_project_setup(REQUIRES 6.8)

# Sources C++
set(PROJECT_SOURCES
    src/main.cpp
    src/core/Application.h
    src/core/Application.cpp
    src/core/ThemeManager.h
    src/core/ThemeManager.cpp
    src/core/PreferencesManager.h
    src/core/PreferencesManager.cpp
    src/models/TimeModel.h
    src/models/TimeModel.cpp
)

# Fichiers QML
set(PROJECT_QML_FILES
    qml/Main.qml
    qml/views/MainView.qml
    qml/components/MenuBar.qml
    qml/components/PreferencesDialog.qml
    qml/components/ThemeEditor.qml
    qml/components/ColorPicker.qml
    qml/components/PropertyEditor.qml
    qml/components/CustomColorPicker.qml
    qml/components/ColorWheel.qml
    qml/components/SliderField.qml
    qml/components/SegmentedButton.qml
    qml/components/ValueBar.qml
    qml/components/CustomDialog.qml
)

qt_add_executable(appQtQmlBaseApp
    ${PROJECT_SOURCES}
    resources.qrc
)

qt_add_qml_module(appQtQmlBaseApp
    URI QtQmlBaseApp
    VERSION 1.0
    QML_FILES ${PROJECT_QML_FILES}
    RESOURCE_PREFIX /qt/qml
)

set_target_properties(appQtQmlBaseApp PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appQtQmlBaseApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(appQtQmlBaseApp
    PRIVATE 
    Qt6::Quick
    Qt6::Qml
    Qt6::Core
    Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appQtQmlBaseApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)