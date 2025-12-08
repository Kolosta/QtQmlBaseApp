// #ifndef THEMEMANAGER_NEW_H
// #define THEMEMANAGER_NEW_H
#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QColor>
#include "core/theme/ThemeAtoms.h"
#include "core/theme/ThemeMolecules.h"

class ThemeManager : public QObject {
    Q_OBJECT
    
    // ===== ACCÈS HIÉRARCHIQUE =====
    // Theme.color.primary (accès direct aux couleurs de base)
    Q_PROPERTY(ColorAtom* color READ color CONSTANT)
    
    // Theme.surface.color.primary, Theme.surface.spacing.medium, Theme.surface.radius.small
    Q_PROPERTY(SurfaceMolecule* surface READ surface CONSTANT)
    
    // Theme.font.color.primary, Theme.font.size.medium, Theme.font.weight.bold
    Q_PROPERTY(FontMolecule* font READ font CONSTANT)
    
    // Theme.border.color.primary, Theme.border.width.thin
    Q_PROPERTY(BorderMolecule* border READ border CONSTANT)
    
    // ===== PROPRIÉTÉS GLOBALES =====
    Q_PROPERTY(QString currentTheme READ currentTheme WRITE setCurrentTheme NOTIFY currentThemeChanged)
    Q_PROPERTY(QStringList availableThemes READ availableThemes CONSTANT)
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)

public:
    static ThemeManager& instance();
    
    // Accès aux molécules
    ColorAtom* color() const { return m_colorAtom; }
    SurfaceMolecule* surface() const { return m_surfaceMolecule; }
    FontMolecule* font() const { return m_fontMolecule; }
    BorderMolecule* border() const { return m_borderMolecule; }
    
    // Gestion du thème
    QString currentTheme() const { return m_currentTheme; }
    void setCurrentTheme(const QString& theme);
    
    QStringList availableThemes() const;
    
    qreal scale() const { return m_scale; }
    void setScale(qreal s);
    
    // Import/Export (optionnel, pour partager des thèmes)
    Q_INVOKABLE bool exportToJson(const QString& filePath) const;
    Q_INVOKABLE bool importFromJson(const QString& filePath);
    
    // Preview pour le sélecteur
    Q_INVOKABLE QColor getThemePreviewPrimary(const QString& themeName) const;
    Q_INVOKABLE QColor getThemePreviewBackground(const QString& themeName) const;
    
    // Reset
    Q_INVOKABLE void resetToDefaults();

signals:
    void currentThemeChanged();
    void scaleChanged();

private:
    explicit ThemeManager(QObject *parent = nullptr);
    ~ThemeManager() = default;
    ThemeManager(const ThemeManager&) = delete;
    ThemeManager& operator=(const ThemeManager&) = delete;
    
    void loadSavedSettings();
    void saveSettings();
    
    QString m_currentTheme{"Dark"};
    qreal m_scale{1.0};
    
    // Atomes (primitives)
    ColorAtom* m_colorAtom;
    SizeAtom* m_sizeAtom;
    WeightAtom* m_weightAtom;
    
    // Molécules (groupes sémantiques)
    SurfaceMolecule* m_surfaceMolecule;
    FontMolecule* m_fontMolecule;
    BorderMolecule* m_borderMolecule;
};

#endif // THEMEMANAGER_H


// #include <QObject>
// #include <QString>
// #include <QStringList>
// #include "core/theme/common/ThemePalette.h"
// #include "core/theme/common/ThemeSizes.h"
// #include "core/theme/components/ComponentStyles.h"


// class ThemeManager : public QObject {
//     Q_OBJECT
    
//     // Exposition hiérarchique vers QML
//     Q_PROPERTY(ThemePalette* colors READ colors CONSTANT)
//     Q_PROPERTY(ThemeSizes* sizes READ sizes CONSTANT)
    
//     // Composants
//     Q_PROPERTY(PreferencesWindowStyle* prefWindow READ prefWindow CONSTANT)
//     Q_PROPERTY(MenuBarStyle* menuBar READ menuBar CONSTANT)
//     Q_PROPERTY(ButtonStyle* button READ button CONSTANT)
    
//     // Thème et scale
//     Q_PROPERTY(QString currentTheme READ currentTheme WRITE setCurrentTheme NOTIFY currentThemeChanged)
//     Q_PROPERTY(QStringList availableThemes READ availableThemes NOTIFY availableThemesChanged)
//     Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)

// public:
//     static ThemeManager& instance();
    
//     // Accès aux sous-systèmes
//     ThemePalette* colors() const { return m_colors; }
//     ThemeSizes* sizes() const { return m_sizes; }
    
//     // Accès aux composants
//     PreferencesWindowStyle* prefWindow() const { return m_prefWindow; }
//     MenuBarStyle* menuBar() const { return m_menuBar; }
//     ButtonStyle* button() const { return m_button; }
    
//     // Thème et scale
//     QString currentTheme() const { return m_currentTheme; }
//     void setCurrentTheme(const QString& theme);
    
//     QStringList availableThemes() const { return m_availableThemes; }
    
//     qreal scale() const { return m_scale; }
//     void setScale(qreal s);
    
//     // Sauvegarde/Chargement
//     Q_INVOKABLE bool loadTheme(const QString& themeName);
//     Q_INVOKABLE bool saveTheme(const QString& themeName);
//     Q_INVOKABLE bool importTheme(const QString& filePath);
//     Q_INVOKABLE bool exportTheme(const QString& filePath);
    
//     // Reset
//     Q_INVOKABLE void resetAllToDefaults();
//     Q_INVOKABLE void resetComponentsToDefaults();
    
//     // Preview (pour ThemeSelector)
//     Q_INVOKABLE QColor getThemePreviewPrimary(const QString& themeName) const;
//     Q_INVOKABLE QColor getThemePreviewBackground(const QString& themeName) const;

// signals:
//     void currentThemeChanged();
//     void scaleChanged();
//     void availableThemesChanged();

// private:
//     explicit ThemeManager(QObject *parent = nullptr);
//     ~ThemeManager() = default;
//     ThemeManager(const ThemeManager&) = delete;
//     ThemeManager& operator=(const ThemeManager&) = delete;
    
//     void discoverThemes();
//     void loadUserOverrides();
//     void saveUserOverrides();
    
//     QString m_currentTheme{"dark"};
//     QStringList m_availableThemes;
//     qreal m_scale{1.0};
    
//     // Sous-systèmes
//     ThemePalette* m_colors;
//     ThemeSizes* m_sizes;
    
//     // Composants
//     PreferencesWindowStyle* m_prefWindow;
//     MenuBarStyle* m_menuBar;
//     ButtonStyle* m_button;
// };

// #endif // THEMEMANAGER_NEW_H