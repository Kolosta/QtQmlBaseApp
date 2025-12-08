#ifndef THEMEPRESETS_H
#define THEMEPRESETS_H

#include "ThemeAtoms.h"

// ===== PRESET: DARK =====
class DarkThemePreset {
public:
    static void apply(ColorAtom* colorAtom, SizeAtom* sizeAtom) {
        // Couleurs
        colorAtom->m_bgPrimary      = QColor("#1e1e1e");
        colorAtom->m_bgSecondary    = QColor("#252525");
        colorAtom->m_bgTertiary     = QColor("#2a2a2a");

        // Surface
        colorAtom->m_surfPrimary    = QColor("#2d2d2d");
        colorAtom->m_surfSecondary  = QColor("#353535");
        colorAtom->m_surfHover      = QColor("#3d3d3d");
        colorAtom->m_surfActive     = QColor("#4d4d4d");
        colorAtom->m_surfDisabled   = QColor("#252525");

        // Primary
        colorAtom->m_primBase       = QColor("#0d7377");
        colorAtom->m_primHover      = QColor("#14a0a5");
        colorAtom->m_primActive     = QColor("#0a5b5e");
        colorAtom->m_primDisabled   = QColor("#084648");

        // Text
        colorAtom->m_textPrimary    = QColor("#ffffff");
        colorAtom->m_textSecondary  = QColor("#b0b0b0");
        colorAtom->m_textTertiary   = QColor("#808080");
        colorAtom->m_textDisabled   = QColor("#666666");
        colorAtom->m_textOnPrimary  = QColor("#ffffff");

        // Border
        colorAtom->m_borderPrimary  = QColor("#3d3d3d");
        colorAtom->m_borderSecondary= QColor("#454545");
        colorAtom->m_borderFocus    = QColor("#4a9eff");
        colorAtom->m_borderDisabled = QColor("#2d2d2d");

        // Accent
        colorAtom->m_accentBase     = QColor("#4a9eff");
        colorAtom->m_accentHover    = QColor("#6bb0ff");
        colorAtom->m_accentActive   = QColor("#2a7edf");

        // Status
        colorAtom->m_statError      = QColor("#f44336");
        colorAtom->m_statErrorHover = QColor("#f55a4e");
        colorAtom->m_statSuccess    = QColor("#4caf50");
        colorAtom->m_statSuccessHover= QColor("#66bb6a");
        colorAtom->m_statWarning    = QColor("#ff9800");
        colorAtom->m_statWarningHover= QColor("#ffa726");
        colorAtom->m_statInfo       = QColor("#2196f3");
        colorAtom->m_statInfoHover  = QColor("#42a5f5");
        
        // Tailles (optionnel si différent du défaut)
        sizeAtom->m_small = 5;
        sizeAtom->m_medium = 10;
        sizeAtom->m_large = 15;
        
        emit colorAtom->changed();
        emit sizeAtom->changed();
    }
    
    static QString name() { return "Dark"; }
    static QColor previewPrimary() { return QColor("#0d7377"); }
    static QColor previewBackground() { return QColor("#252525"); }
};

// ===== PRESET: ARCTIC =====
class ArcticThemePreset {
public:
    static void apply(ColorAtom* colorAtom, SizeAtom* sizeAtom) {
        // Background
        colorAtom->m_bgPrimary      = QColor("#e8f4f8");
        // Les valeurs manquantes dans le JSON prennent un fallback logique
        // (souvent hérité du Dark ou adapté légèrement, ici je mets des valeurs 'light')
        colorAtom->m_bgSecondary    = QColor("#dbeff5"); // fallback calculé
        colorAtom->m_bgTertiary     = QColor("#ceeaf2"); // fallback calculé

        // Surface
        colorAtom->m_surfPrimary    = QColor("#f0f8fa");
        colorAtom->m_surfSecondary  = QColor("#e6f4f7"); // fallback
        colorAtom->m_surfHover      = QColor("#d9eff5");
        colorAtom->m_surfActive     = QColor("#cce9f2"); // fallback
        colorAtom->m_surfDisabled   = QColor("#e0e0e0"); // fallback

        // Primary
        colorAtom->m_primBase       = QColor("#006494");
        colorAtom->m_primHover      = QColor("#0077b6");
        colorAtom->m_primActive     = QColor("#00507a"); // fallback
        colorAtom->m_primDisabled   = QColor("#80b2ca"); // fallback

        // Text
        colorAtom->m_textPrimary    = QColor("#001f3f");
        colorAtom->m_textSecondary  = QColor("#4a7c8c");
        colorAtom->m_textTertiary   = QColor("#6a9ca8"); // fallback
        colorAtom->m_textDisabled   = QColor("#a0c0cc"); // fallback
        colorAtom->m_textOnPrimary  = QColor("#ffffff");

        // Border
        colorAtom->m_borderPrimary  = QColor("#b8d8e0");
        colorAtom->m_borderSecondary= QColor("#a0c8d4"); // fallback
        colorAtom->m_borderFocus    = QColor("#0096c7"); // fallback
        colorAtom->m_borderDisabled = QColor("#d0e4ea"); // fallback

        // Accent
        colorAtom->m_accentBase     = QColor("#0096c7");
        colorAtom->m_accentHover    = QColor("#00a8e0"); // fallback
        colorAtom->m_accentActive   = QColor("#007da6"); // fallback

        // Status (Pas dans le JSON, on garde des couleurs vives standards pour light theme)
        colorAtom->m_statError      = QColor("#dc143c");
        colorAtom->m_statSuccess    = QColor("#00a86b");
        colorAtom->m_statWarning    = QColor("#ff8c00");
        colorAtom->m_statInfo       = QColor("#1e90ff");
        
        emit colorAtom->changed();
        emit sizeAtom->changed();
    }
    
    static QString name() { return "Arctic"; }
    static QColor previewPrimary() { return QColor("#006494"); }
    static QColor previewBackground() { return QColor("#e8f4f8"); }
};

// ===== PRESET: SEPIA =====
// class SepiaThemePreset {
// public:
//     static void apply(ColorAtom* colorAtom, SizeAtom* sizeAtom) {
//         colorAtom->m_primary = QColor("#8b4513");
//         colorAtom->m_secondary = QColor("#f4ecd8");
//         colorAtom->m_tertiary = QColor("#e8ddc0");
//         colorAtom->m_accent = QColor("#cd853f");
        
//         colorAtom->m_textPrimary = QColor("#3e2723");
//         colorAtom->m_textSecondary = QColor("#6d4c41");
//         colorAtom->m_textTertiary = QColor("#8d6e63");
//         colorAtom->m_textDisabled = QColor("#bcaaa4");
        
//         colorAtom->m_success = QColor("#7cb342");
//         colorAtom->m_warning = QColor("#fb8c00");
//         colorAtom->m_error = QColor("#e53935");
//         colorAtom->m_info = QColor("#039be5");
        
//         emit colorAtom->changed();
//         emit sizeAtom->changed();
//     }
    
//     static QString name() { return "Sepia"; }
//     static QColor previewPrimary() { return QColor("#8b4513"); }
//     static QColor previewBackground() { return QColor("#f4ecd8"); }
// };

class BlueThemePreset {
public:
    static void apply(ColorAtom* colorAtom, SizeAtom* sizeAtom) {
        colorAtom->m_bgPrimary      = QColor("#0d1b2a");
        colorAtom->m_bgSecondary    = QColor("#142338"); // fallback
        colorAtom->m_bgTertiary     = QColor("#1b2b42"); // fallback

        colorAtom->m_surfPrimary    = QColor("#1b2838");
        colorAtom->m_surfSecondary  = QColor("#223347"); // fallback
        colorAtom->m_surfHover      = QColor("#253647");
        colorAtom->m_surfActive     = QColor("#30455b"); // fallback
        colorAtom->m_surfDisabled   = QColor("#182230"); // fallback

        colorAtom->m_primBase       = QColor("#1e90ff");
        colorAtom->m_primHover      = QColor("#4da3ff");
        colorAtom->m_primActive     = QColor("#0077e6"); // fallback
        colorAtom->m_primDisabled   = QColor("#104a80"); // fallback

        colorAtom->m_textPrimary    = QColor("#e0f4ff");
        colorAtom->m_textSecondary  = QColor("#7ab8e8");
        colorAtom->m_textTertiary   = QColor("#5a8ab0"); // fallback
        colorAtom->m_textDisabled   = QColor("#3a5a70"); // fallback
        colorAtom->m_textOnPrimary  = QColor("#ffffff");

        colorAtom->m_borderPrimary  = QColor("#2c4a66");
        colorAtom->m_borderSecondary= QColor("#365a7a"); // fallback
        colorAtom->m_borderFocus    = QColor("#00bfff"); // fallback
        colorAtom->m_borderDisabled = QColor("#1e3345"); // fallback

        colorAtom->m_accentBase     = QColor("#00bfff");
        colorAtom->m_accentHover    = QColor("#33ccff"); // fallback
        colorAtom->m_accentActive   = QColor("#0099cc"); // fallback
        
        // Keep standard dark status colors
        colorAtom->m_statError      = QColor("#f44336");
        colorAtom->m_statSuccess    = QColor("#4caf50");
        colorAtom->m_statWarning    = QColor("#ff9800");
        colorAtom->m_statInfo       = QColor("#2196f3");

        emit colorAtom->changed();
        emit sizeAtom->changed();
    }

    static QString name() { return "Sepia"; }
    static QColor previewPrimary() { return QColor("#1e90ff"); }
    static QColor previewBackground() { return QColor("#0d1b2a"); }
};

// ===== REGISTRY =====
// Liste de tous les thèmes disponibles
class ThemeRegistry {
public:
    static QStringList availableThemes() {
        return {
            DarkThemePreset::name(),
            ArcticThemePreset::name(),
            BlueThemePreset::name()
        };
    }
    
    static void applyTheme(const QString& name, ColorAtom* colorAtom, SizeAtom* sizeAtom) {
        if (name == "Dark") {
            DarkThemePreset::apply(colorAtom, sizeAtom);
        } else if (name == "Arctic") {
            ArcticThemePreset::apply(colorAtom, sizeAtom);
        } else if (name == "Sepia") {
            BlueThemePreset::apply(colorAtom, sizeAtom);
        } else {
            // Default to Dark
            DarkThemePreset::apply(colorAtom, sizeAtom);
        }
    }
    
    static QColor getPreviewPrimary(const QString& name) {
        if (name == "Dark") return DarkThemePreset::previewPrimary();
        if (name == "Arctic") return ArcticThemePreset::previewPrimary();
        if (name == "Sepia") return BlueThemePreset::previewPrimary();
        return DarkThemePreset::previewPrimary();
    }
    
    static QColor getPreviewBackground(const QString& name) {
        if (name == "Dark") return DarkThemePreset::previewBackground();
        if (name == "Arctic") return ArcticThemePreset::previewBackground();
        if (name == "Sepia") return BlueThemePreset::previewBackground();
        return DarkThemePreset::previewBackground();
    }
};

#endif // THEMEPRESETS_H