#ifndef COMPONENTSTYLES_H
#define COMPONENTSTYLES_H

#include <QObject>
#include <QColor>
#include <QJsonObject>
#include <optional>

class ThemePalette;
class ThemeSizes;
class ThemeManager;

// ===== PreferencesWindow Style =====
class PreferencesWindowStyle : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY changed)
    Q_PROPERTY(QColor sidebarBackground READ sidebarBackground WRITE setSidebarBackground NOTIFY changed)
    Q_PROPERTY(int sidebarWidth READ sidebarWidth WRITE setSidebarWidth NOTIFY changed)

public:
    explicit PreferencesWindowStyle(ThemePalette* palette, ThemeSizes* sizes, 
                                   ThemeManager* manager, QObject* parent = nullptr);
    
    // Getters intelligents avec cascade
    QColor background() const;
    QColor sidebarBackground() const;
    int sidebarWidth() const; // Déjà scalé !
    
    // Setters pour overrides
    void setBackground(const QColor& c);
    void setSidebarBackground(const QColor& c);
    void setSidebarWidth(int w);
    
    // Reset individuel
    void resetBackground();
    void resetSidebarBackground();
    void resetSidebarWidth();
    
    // Reset complet
    void resetAll();
    
    // Vérifier si une propriété est override
    bool isBackgroundOverridden() const { return m_overrideBackground.has_value(); }
    bool isSidebarBackgroundOverridden() const { return m_overrideSidebarBg.has_value(); }
    bool isSidebarWidthOverridden() const { return m_overrideSidebarWidth.has_value(); }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;

signals:
    void changed();

private:
    ThemePalette* m_palette;
    ThemeSizes* m_sizes;
    ThemeManager* m_manager;
    
    // Overrides optionnels
    std::optional<QColor> m_overrideBackground;
    std::optional<QColor> m_overrideSidebarBg;
    std::optional<int> m_overrideSidebarWidth; // Valeur RAW, sera scalée par le getter
};

// ===== MenuBar Style =====
class MenuBarStyle : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY changed)
    Q_PROPERTY(QColor text READ text WRITE setText NOTIFY changed)
    Q_PROPERTY(QColor hoverBackground READ hoverBackground WRITE setHoverBackground NOTIFY changed)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY changed)

public:
    explicit MenuBarStyle(ThemePalette* palette, ThemeSizes* sizes, 
                         ThemeManager* manager, QObject* parent = nullptr);
    
    QColor background() const;
    QColor text() const;
    QColor hoverBackground() const;
    int height() const; // Scalé auto
    
    void setBackground(const QColor& c);
    void setText(const QColor& c);
    void setHoverBackground(const QColor& c);
    void setHeight(int h);
    
    void resetBackground();
    void resetText();
    void resetHoverBackground();
    void resetHeight();
    void resetAll();
    
    bool isBackgroundOverridden() const { return m_overrideBackground.has_value(); }
    bool isTextOverridden() const { return m_overrideText.has_value(); }
    bool isHoverBackgroundOverridden() const { return m_overrideHoverBg.has_value(); }
    bool isHeightOverridden() const { return m_overrideHeight.has_value(); }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;

signals:
    void changed();

private:
    ThemePalette* m_palette;
    ThemeSizes* m_sizes;
    ThemeManager* m_manager;
    
    std::optional<QColor> m_overrideBackground;
    std::optional<QColor> m_overrideText;
    std::optional<QColor> m_overrideHoverBg;
    std::optional<int> m_overrideHeight;
};

// ===== Button Style =====
class ButtonStyle : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY changed)
    Q_PROPERTY(QColor hoverBackground READ hoverBackground WRITE setHoverBackground NOTIFY changed)
    Q_PROPERTY(QColor activeBackground READ activeBackground WRITE setActiveBackground NOTIFY changed)
    Q_PROPERTY(QColor text READ text WRITE setText NOTIFY changed)
    Q_PROPERTY(QColor border READ border WRITE setBorder NOTIFY changed)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY changed)
    Q_PROPERTY(int radius READ radius WRITE setRadius NOTIFY changed)
    Q_PROPERTY(int padding READ padding WRITE setPadding NOTIFY changed)

public:
    explicit ButtonStyle(ThemePalette* palette, ThemeSizes* sizes, 
                        ThemeManager* manager, QObject* parent = nullptr);
    
    QColor background() const;
    QColor hoverBackground() const;
    QColor activeBackground() const;
    QColor text() const;
    QColor border() const;
    int borderWidth() const;
    int radius() const;
    int padding() const;
    
    void setBackground(const QColor& c);
    void setHoverBackground(const QColor& c);
    void setActiveBackground(const QColor& c);
    void setText(const QColor& c);
    void setBorder(const QColor& c);
    void setBorderWidth(int w);
    void setRadius(int r);
    void setPadding(int p);
    
    void resetAll();
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;

signals:
    void changed();

private:
    ThemePalette* m_palette;
    ThemeSizes* m_sizes;
    ThemeManager* m_manager;
    
    std::optional<QColor> m_overrideBackground;
    std::optional<QColor> m_overrideHoverBg;
    std::optional<QColor> m_overrideActiveBg;
    std::optional<QColor> m_overrideText;
    std::optional<QColor> m_overrideBorder;
    std::optional<int> m_overrideBorderWidth;
    std::optional<int> m_overrideRadius;
    std::optional<int> m_overridePadding;
};

// Ajouter d'autres composants selon les besoins : InputStyle, DialogStyle, etc.

#endif // COMPONENTSTYLES_H