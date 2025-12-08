#ifndef COMPONENTOVERRIDES_H
#define COMPONENTOVERRIDES_H

#include <QObject>
#include <QColor>
#include <QJsonObject>
#include <QMap>
#include <QVariant>

class ThemeManager;

// Classe de base pour les overrides de composants
class ComponentOverride : public QObject {
    Q_OBJECT

public:
    explicit ComponentOverride(const QString& componentName, ThemeManager* manager, QObject* parent = nullptr);
    virtual ~ComponentOverride() = default;
    
    // Système de propriétés overridées
    Q_INVOKABLE void setColorOverride(const QString& atomProperty, const QColor& color);
    Q_INVOKABLE void setSizeOverride(const QString& atomProperty, int size);
    Q_INVOKABLE void clearOverride(const QString& property);
    Q_INVOKABLE void clearAllOverrides();
    
    Q_INVOKABLE bool hasOverride(const QString& property) const;
    Q_INVOKABLE QVariant getOverride(const QString& property) const;
    
    // Accès aux valeurs finales (avec fallback sur les atomes si pas d'override)
    Q_INVOKABLE QColor getColor(const QString& atomProperty) const;
    Q_INVOKABLE int getSize(const QString& atomProperty) const;
    
    // Serialization
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    
    QString componentName() const { return m_componentName; }

signals:
    void overridesChanged();

protected:
    QString m_componentName;
    ThemeManager* m_manager;
    QMap<QString, QVariant> m_overrides; // "bgPrimary" -> QColor, "spacingMedium" -> int
};

// Override spécifique pour NumberField (exemple)
class NumberFieldOverride : public ComponentOverride {
    Q_OBJECT
    
    // Propriétés QML accessibles
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY overridesChanged)
    Q_PROPERTY(QColor backgroundHover READ backgroundHover WRITE setBackgroundHover NOTIFY overridesChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY overridesChanged)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY overridesChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY overridesChanged)
    Q_PROPERTY(int textSize READ textSize WRITE setTextSize NOTIFY overridesChanged)
    Q_PROPERTY(int textWeight READ textWeight WRITE setTextWeight NOTIFY overridesChanged)

public:
    explicit NumberFieldOverride(ThemeManager* manager, QObject* parent = nullptr);
    
    QColor background() const;
    void setBackground(const QColor& color);
    
    QColor backgroundHover() const;
    void setBackgroundHover(const QColor& color);
    
    QColor borderColor() const;
    void setBorderColor(const QColor& color);
    
    int borderWidth() const;
    void setBorderWidth(int width);
    
    QColor textColor() const;
    void setTextColor(const QColor& color);
    
    int textSize() const;
    void setTextSize(int size);
    
    int textWeight() const;
    void setTextWeight(int weight);
};

// Override pour MenuBar
class MenuBarOverride : public ComponentOverride {
    Q_OBJECT
    
    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY overridesChanged)
    Q_PROPERTY(QColor hoverBackground READ hoverBackground WRITE setHoverBackground NOTIFY overridesChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY overridesChanged)

public:
    explicit MenuBarOverride(ThemeManager* manager, QObject* parent = nullptr);
    
    QColor background() const;
    void setBackground(const QColor& color);
    
    QColor hoverBackground() const;
    void setHoverBackground(const QColor& color);
    
    int height() const;
    void setHeight(int h);
};

// Override pour PreferencesWindow
class PreferencesWindowOverride : public ComponentOverride {
    Q_OBJECT
    
    Q_PROPERTY(QColor sidebarBackground READ sidebarBackground WRITE setSidebarBackground NOTIFY overridesChanged)
    Q_PROPERTY(QColor contentBackground READ contentBackground WRITE setContentBackground NOTIFY overridesChanged)
    Q_PROPERTY(int sidebarWidth READ sidebarWidth WRITE setSidebarWidth NOTIFY overridesChanged)

public:
    explicit PreferencesWindowOverride(ThemeManager* manager, QObject* parent = nullptr);
    
    QColor sidebarBackground() const;
    void setSidebarBackground(const QColor& color);
    
    QColor contentBackground() const;
    void setContentBackground(const QColor& color);
    
    int sidebarWidth() const;
    void setSidebarWidth(int width);
};

#endif