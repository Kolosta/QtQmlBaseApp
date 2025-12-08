#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QMap>
#include "core/theme/base/ThemeColors.h"
#include "core/theme/base/ThemeSpacing.h"
#include "core/theme/base/ThemeFont.h"
#include "core/theme/base/ThemeBorder.h"
#include "core/theme/base/ThemeSize.h"
#include "core/theme/base/ThemeTransition.h"
#include "core/theme/components/ThemeComponents.h"
#include "core/theme/presets/ThemePreset.h"

class ThemeManager : public QObject {
    Q_OBJECT
    
    // ===== PROPRIÉTÉS DE BASE =====
    Q_PROPERTY(ThemeColors* color READ color CONSTANT)
    Q_PROPERTY(ThemeSpacing* spacing READ spacing CONSTANT)
    Q_PROPERTY(ThemeFont* font READ font CONSTANT)
    Q_PROPERTY(ThemeBorder* border READ border CONSTANT)
    Q_PROPERTY(ThemeSize* size READ size CONSTANT)
    Q_PROPERTY(ThemeTransition* transition READ transition CONSTANT)
    
    // ===== COMPOSANTS =====
    Q_PROPERTY(ThemeComponents* components READ components CONSTANT)
    
    // ===== PROPRIÉTÉS GLOBALES =====
    Q_PROPERTY(QString currentTheme READ currentTheme WRITE setCurrentTheme NOTIFY currentThemeChanged)
    Q_PROPERTY(QStringList availableThemes READ availableThemes NOTIFY availableThemesChanged)
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(bool hasUnsavedChanges READ hasUnsavedChanges NOTIFY hasUnsavedChangesChanged)

public:
    static ThemeManager& instance();
    
    // Accès aux propriétés
    ThemeColors* color() const { return m_colors; }
    ThemeSpacing* spacing() const { return m_spacing; }
    ThemeFont* font() const { return m_font; }
    ThemeBorder* border() const { return m_border; }
    ThemeSize* size() const { return m_size; }
    ThemeTransition* transition() const { return m_transition; }
    ThemeComponents* components() const { return m_components; }
    
    // Gestion du thème
    QString currentTheme() const { return m_currentThemeName; }
    void setCurrentTheme(const QString& theme);
    
    QStringList availableThemes() const;
    
    qreal scale() const { return m_scale; }
    void setScale(qreal s);
    
    bool hasUnsavedChanges() const { return m_hasUnsavedChanges; }
    
    // Import/Export
    Q_INVOKABLE bool exportTheme(const QString& filePath);
    Q_INVOKABLE bool importTheme(const QString& filePath);
    
    // Sauvegarde
    Q_INVOKABLE void saveCurrentThemeChanges();
    Q_INVOKABLE void discardCurrentThemeChanges();
    
    // Reset
    Q_INVOKABLE void resetToDefaults();
    
    // Preview
    Q_INVOKABLE QColor getThemePreviewPrimary(const QString& themeName) const;
    Q_INVOKABLE QColor getThemePreviewBackground(const QString& themeName) const;

signals:
    void currentThemeChanged();
    void scaleChanged();
    void availableThemesChanged();
    void hasUnsavedChangesChanged();
    void themeModified();

private:
    explicit ThemeManager(QObject *parent = nullptr);
    ~ThemeManager() = default;
    ThemeManager(const ThemeManager&) = delete;
    ThemeManager& operator=(const ThemeManager&) = delete;
    
    void initializeBuiltinPresets();
    void loadSavedSettings();
    void saveSettings();
    void applyTheme(const QString& themeName);
    void markAsModified();
    
    // État actuel
    QString m_currentThemeName{"Dark"};
    qreal m_scale{1.0};
    bool m_hasUnsavedChanges{false};
    
    // Propriétés actives (pointent vers le preset actuel)
    ThemeColors* m_colors;
    ThemeSpacing* m_spacing;
    ThemeFont* m_font;
    ThemeBorder* m_border;
    ThemeSize* m_size;
    ThemeTransition* m_transition;
    ThemeComponents* m_components;
    
    // Stockage des presets
    QMap<QString, ThemePreset*> m_presets; // Presets de base
    QMap<QString, ThemePreset*> m_unsavedChanges; // Modifications par thème
};

#endif // THEMEMANAGER_H