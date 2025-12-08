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
    # Application
    src/main.cpp
    src/core/Application.h
    src/core/Application.cpp

    # Theme management
    # src/core/ThemeManager.h
    # src/core/ThemeManager.cpp
    # src/core/theme/common/ThemePalette.h
    # src/core/theme/common/ThemePalette.cpp
    # src/core/theme/common/ThemeSizes.h
    # src/core/theme/common/ThemeSizes.cpp
    # src/core/theme/components/ComponentStyles.h
    # src/core/theme/components/ComponentStyles.cpp

    src/core/ThemeManager.h
    src/core/ThemeManager.cpp
    src/core/theme/ThemeAtoms.h
    src/core/theme/ThemeAtoms.cpp
    src/core/theme/ThemeMolecules.h
    src/core/theme/ThemeMolecules.cpp
    src/core/theme/ThemePresets.h
    src/core/theme/ComponentOverrides.h
    src/core/theme/ComponentOverrides.cpp
    src/core/ThemeManager.h
    src/core/ThemeManager.cpp

    # Base
    src/core/theme/base/ColorState.h
    src/core/theme/base/ColorState.cpp
    src/core/theme/base/SimpleColorState.h
    src/core/theme/base/SimpleColorState.cpp
    src/core/theme/base/SizeValue.h
    src/core/theme/base/SizeValue.cpp
    src/core/theme/base/ThemeColors.h
    src/core/theme/base/ThemeColors.cpp
    src/core/theme/base/ThemeSpacing.h
    src/core/theme/base/ThemeSpacing.cpp
    src/core/theme/base/ThemeFont.h
    src/core/theme/base/ThemeFont.cpp
    src/core/theme/base/ThemeBorder.h
    src/core/theme/base/ThemeBorder.cpp
    src/core/theme/base/ThemeSize.h
    src/core/theme/base/ThemeSize.cpp
    src/core/theme/base/ThemeTransition.h
    src/core/theme/base/ThemeTransition.cpp

    # Components
    src/core/theme/components/MenuBarTheme.h
    src/core/theme/components/MenuBarTheme.cpp
    src/core/theme/components/ButtonTheme.h
    src/core/theme/components/ButtonTheme.cpp
    src/core/theme/components/PreferencesWindowTheme.h
    src/core/theme/components/PreferencesWindowTheme.cpp
    src/core/theme/components/ThemeComponents.h
    src/core/theme/components/ThemeComponents.cpp

    # Presets
    src/core/theme/presets/ThemePreset.h
    src/core/theme/presets/ThemePreset.cpp

    # Preferences and Keymaps
    # src/core/PreferencesManager.h
    # src/core/PreferencesManager.cpp
    src/core/KeymapManager.h
    src/core/KeymapManager.cpp

    # Models
    src/models/TimeModel.h
    src/models/TimeModel.cpp
    # src/models/ThemePropertyModel.h
    # src/models/ThemePropertyModel.cpp
)

# Fichiers QML
set(PROJECT_QML_FILES
    # Root
    qml/Main.qml
    # Views
    qml/views/MainView.qml

    # Common components
    qml/components/common/MenuBar.qml
    # qml/components/common/CustomDialog.qml
    # qml/components/common/ScrollableContentArea.qml
    # qml/components/common/ShortcutDialog.qml

    # Input components
    # qml/components/inputs/NumberField.qml
    # qml/components/inputs/SliderField.qml
    # qml/components/inputs/SegmentedButton.qml

    # Color pickers
    # qml/components/pickers/ColorPicker.qml
    # qml/components/pickers/CustomColorPicker.qml
    # qml/components/pickers/ColorWheel.qml
    # qml/components/pickers/ValueBar.qml

    # Preferences components
    qml/components/preferences/PreferencesWindow.qml
    qml/components/preferences/pages/PreferencesPage.qml
    qml/components/preferences/pages/ThemeSelectorPage.qml
    qml/components/preferences/pages/ThemePreviewPage.qml
    qml/components/preferences/pages/ThemeEditorPage.qml
    qml/components/preferences/editors/PropertyEditor.qml
    qml/components/preferences/editors/PropertyGroup.qml
    qml/components/preferences/PreferencesSidebarButton.qml
    # qml/components/preferences/pages/Interface.qml
    # qml/components/preferences/pages/Keymaps.qml
    # qml/components/preferences/pages/ComponentsLib.qml

    
    # Presentation components
    qml/components/presentation/ComponentSection.qml
    qml/components/presentation/ComponentSubSection.qml
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