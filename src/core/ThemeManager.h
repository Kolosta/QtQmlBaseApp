#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QVariantMap>
#include <QStringList>
#include <QColor>

class ThemeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentTheme READ currentTheme WRITE setCurrentTheme NOTIFY currentThemeChanged)
    Q_PROPERTY(QStringList availableThemes READ availableThemes NOTIFY availableThemesChanged)
    
    // Colors
    Q_PROPERTY(QColor background READ background NOTIFY themePropertiesChanged)
    Q_PROPERTY(QColor surface READ surface NOTIFY themePropertiesChanged)
    Q_PROPERTY(QColor surfaceHover READ surfaceHover NOTIFY themePropertiesChanged)
    Q_PROPERTY(QColor primary READ primary NOTIFY themePropertiesChanged)
    Q_PROPERTY(QColor primaryHover READ primaryHover NOTIFY themePropertiesChanged)
    Q_PROPERTY(QColor text READ text NOTIFY themePropertiesChanged)
    Q_PROPERTY(QColor textSecondary READ textSecondary NOTIFY themePropertiesChanged)
    Q_PROPERTY(QColor border READ border NOTIFY themePropertiesChanged)
    Q_PROPERTY(QColor accent READ accent NOTIFY themePropertiesChanged)
    Q_PROPERTY(QColor error READ error NOTIFY themePropertiesChanged)
    Q_PROPERTY(QColor success READ success NOTIFY themePropertiesChanged)
    Q_PROPERTY(QColor warning READ warning NOTIFY themePropertiesChanged)
    
    // Dimensions
    Q_PROPERTY(int menuBarHeight READ menuBarHeight NOTIFY themePropertiesChanged)
    Q_PROPERTY(int spacing READ spacing NOTIFY themePropertiesChanged)
    Q_PROPERTY(int spacingSmall READ spacingSmall NOTIFY themePropertiesChanged)
    Q_PROPERTY(int spacingLarge READ spacingLarge NOTIFY themePropertiesChanged)
    Q_PROPERTY(int radius READ radius NOTIFY themePropertiesChanged)
    Q_PROPERTY(int radiusSmall READ radiusSmall NOTIFY themePropertiesChanged)
    Q_PROPERTY(int radiusLarge READ radiusLarge NOTIFY themePropertiesChanged)
    Q_PROPERTY(int borderWidth READ borderWidth NOTIFY themePropertiesChanged)
    Q_PROPERTY(int animationDuration READ animationDuration NOTIFY themePropertiesChanged)
    
    // Fonts
    Q_PROPERTY(int fontSizeSmall READ fontSizeSmall NOTIFY themePropertiesChanged)
    Q_PROPERTY(int fontSizeMedium READ fontSizeMedium NOTIFY themePropertiesChanged)
    Q_PROPERTY(int fontSizeLarge READ fontSizeLarge NOTIFY themePropertiesChanged)
    Q_PROPERTY(int fontSizeTitle READ fontSizeTitle NOTIFY themePropertiesChanged)

public:
    explicit ThemeManager(QObject *parent = nullptr);
    
    QString currentTheme() const { return m_currentTheme; }
    void setCurrentTheme(const QString &theme);
    
    QStringList availableThemes() const { return m_availableThemes; }
    
    // Getters for properties
    QColor background() const { return getColor("background"); }
    QColor surface() const { return getColor("surface"); }
    QColor surfaceHover() const { return getColor("surfaceHover"); }
    QColor primary() const { return getColor("primary"); }
    QColor primaryHover() const { return getColor("primaryHover"); }
    QColor text() const { return getColor("text"); }
    QColor textSecondary() const { return getColor("textSecondary"); }
    QColor border() const { return getColor("border"); }
    QColor accent() const { return getColor("accent"); }
    QColor error() const { return getColor("error"); }
    QColor success() const { return getColor("success"); }
    QColor warning() const { return getColor("warning"); }
    
    int menuBarHeight() const { return getInt("menuBarHeight"); }
    int spacing() const { return getInt("spacing"); }
    int spacingSmall() const { return getInt("spacingSmall"); }
    int spacingLarge() const { return getInt("spacingLarge"); }
    int radius() const { return getInt("radius"); }
    int radiusSmall() const { return getInt("radiusSmall"); }
    int radiusLarge() const { return getInt("radiusLarge"); }
    int borderWidth() const { return getInt("borderWidth"); }
    int animationDuration() const { return getInt("animationDuration"); }
    
    int fontSizeSmall() const { return getInt("fontSizeSmall"); }
    int fontSizeMedium() const { return getInt("fontSizeMedium"); }
    int fontSizeLarge() const { return getInt("fontSizeLarge"); }
    int fontSizeTitle() const { return getInt("fontSizeTitle"); }
    
    // Methods callable from QML
    Q_INVOKABLE QVariantMap getAllProperties() const;
    Q_INVOKABLE QVariant getProperty(const QString &key) const;
    Q_INVOKABLE void setProperty(const QString &key, const QVariant &value);
    Q_INVOKABLE void resetProperty(const QString &key);
    Q_INVOKABLE void resetAllProperties();
    Q_INVOKABLE bool isPropertyModified(const QString &key) const;
    Q_INVOKABLE QVariant getOriginalValue(const QString &key) const;
    
    Q_INVOKABLE bool importTheme(const QString &filePath);
    Q_INVOKABLE bool exportTheme(const QString &filePath) const;
    
    Q_INVOKABLE QString getPropertyType(const QString &key) const;
    
    Q_INVOKABLE QColor getThemePreviewBackground(const QString &themeName) const;
    Q_INVOKABLE QColor getThemePreviewPrimary(const QString &themeName) const;

signals:
    void currentThemeChanged();
    void themePropertiesChanged();
    void availableThemesChanged();

private:
    void loadDefaultTheme();
    void loadTheme(const QString &themeName);
    void loadUserOverrides();
    void saveUserOverrides();
    void discoverThemes();
    QVariantMap mergeThemes(const QVariantMap &base, const QVariantMap &override) const;
    
    QColor getColor(const QString &key) const;
    int getInt(const QString &key) const;
    
    // Méthodes pour normaliser et comparer les valeurs
    QVariant normalizeValue(const QVariant &value) const;
    bool valuesAreEqual(const QVariant &v1, const QVariant &v2) const;
    
    QString m_currentTheme;
    QStringList m_availableThemes;
    QVariantMap m_defaultTheme;
    QVariantMap m_currentThemeBase;
    QVariantMap m_userOverrides;
    QVariantMap m_effectiveTheme;
};

#endif // THEMEMANAGER_H