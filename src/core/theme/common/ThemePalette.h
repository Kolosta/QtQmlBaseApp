#ifndef THEMEPALETTE_H
#define THEMEPALETTE_H

#include <QObject>
#include <QColor>

class ThemePalette : public QObject {
    Q_OBJECT
    
    // Background colors
    Q_PROPERTY(QColor backgroundPrimary MEMBER m_backgroundPrimary NOTIFY changed)
    Q_PROPERTY(QColor backgroundSecondary MEMBER m_backgroundSecondary NOTIFY changed)
    Q_PROPERTY(QColor backgroundTertiary MEMBER m_backgroundTertiary NOTIFY changed)
    
    // Surface colors
    Q_PROPERTY(QColor surfacePrimary MEMBER m_surfacePrimary NOTIFY changed)
    Q_PROPERTY(QColor surfaceSecondary MEMBER m_surfaceSecondary NOTIFY changed)
    Q_PROPERTY(QColor surfaceHover MEMBER m_surfaceHover NOTIFY changed)
    Q_PROPERTY(QColor surfaceActive MEMBER m_surfaceActive NOTIFY changed)
    Q_PROPERTY(QColor surfaceDisabled MEMBER m_surfaceDisabled NOTIFY changed)
    
    // Primary colors
    Q_PROPERTY(QColor primaryBase MEMBER m_primaryBase NOTIFY changed)
    Q_PROPERTY(QColor primaryHover MEMBER m_primaryHover NOTIFY changed)
    Q_PROPERTY(QColor primaryActive MEMBER m_primaryActive NOTIFY changed)
    Q_PROPERTY(QColor primaryDisabled MEMBER m_primaryDisabled NOTIFY changed)
    
    // Text colors
    Q_PROPERTY(QColor textPrimary MEMBER m_textPrimary NOTIFY changed)
    Q_PROPERTY(QColor textSecondary MEMBER m_textSecondary NOTIFY changed)
    Q_PROPERTY(QColor textTertiary MEMBER m_textTertiary NOTIFY changed)
    Q_PROPERTY(QColor textDisabled MEMBER m_textDisabled NOTIFY changed)
    Q_PROPERTY(QColor textOnPrimary MEMBER m_textOnPrimary NOTIFY changed)
    
    // Border colors
    Q_PROPERTY(QColor borderPrimary MEMBER m_borderPrimary NOTIFY changed)
    Q_PROPERTY(QColor borderSecondary MEMBER m_borderSecondary NOTIFY changed)
    Q_PROPERTY(QColor borderFocus MEMBER m_borderFocus NOTIFY changed)
    Q_PROPERTY(QColor borderDisabled MEMBER m_borderDisabled NOTIFY changed)
    
    // Accent colors
    Q_PROPERTY(QColor accentBase MEMBER m_accentBase NOTIFY changed)
    Q_PROPERTY(QColor accentHover MEMBER m_accentHover NOTIFY changed)
    Q_PROPERTY(QColor accentActive MEMBER m_accentActive NOTIFY changed)
    
    // Status colors
    Q_PROPERTY(QColor statusError MEMBER m_statusError NOTIFY changed)
    Q_PROPERTY(QColor statusErrorHover MEMBER m_statusErrorHover NOTIFY changed)
    Q_PROPERTY(QColor statusSuccess MEMBER m_statusSuccess NOTIFY changed)
    Q_PROPERTY(QColor statusSuccessHover MEMBER m_statusSuccessHover NOTIFY changed)
    Q_PROPERTY(QColor statusWarning MEMBER m_statusWarning NOTIFY changed)
    Q_PROPERTY(QColor statusWarningHover MEMBER m_statusWarningHover NOTIFY changed)
    Q_PROPERTY(QColor statusInfo MEMBER m_statusInfo NOTIFY changed)
    Q_PROPERTY(QColor statusInfoHover MEMBER m_statusInfoHover NOTIFY changed)

public:
    explicit ThemePalette(QObject *parent = nullptr);
    
    // Load from JSON
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    
    // Reset to defaults
    void resetToDefaults();

signals:
    void changed();

private:
    // Background
    QColor m_backgroundPrimary{"#1e1e1e"};
    QColor m_backgroundSecondary{" #252525"};
    QColor m_backgroundTertiary{"#2a2a2a"};
    
    // Surface
    QColor m_surfacePrimary{"#2d2d2d"};
    QColor m_surfaceSecondary{"#353535"};
    QColor m_surfaceHover{"#3d3d3d"};
    QColor m_surfaceActive{"#4d4d4d"};
    QColor m_surfaceDisabled{"#252525"};
    
    // Primary
    QColor m_primaryBase{"#0d7377"};
    QColor m_primaryHover{"#14a0a5"};
    QColor m_primaryActive{"#0a5b5e"};
    QColor m_primaryDisabled{"#084648"};
    
    // Text
    QColor m_textPrimary{"#ffffff"};
    QColor m_textSecondary{"#b0b0b0"};
    QColor m_textTertiary{"#808080"};
    QColor m_textDisabled{"#666666"};
    QColor m_textOnPrimary{"#ffffff"};
    
    // Border
    QColor m_borderPrimary{"#3d3d3d"};
    QColor m_borderSecondary{"#454545"};
    QColor m_borderFocus{"#4a9eff"};
    QColor m_borderDisabled{"#2d2d2d"};
    
    // Accent
    QColor m_accentBase{"#4a9eff"};
    QColor m_accentHover{"#6bb0ff"};
    QColor m_accentActive{"#2a7edf"};
    
    // Status
    QColor m_statusError{"#f44336"};
    QColor m_statusErrorHover{"#f55a4e"};
    QColor m_statusSuccess{"#4caf50"};
    QColor m_statusSuccessHover{"#66bb6a"};
    QColor m_statusWarning{"#ff9800"};
    QColor m_statusWarningHover{"#ffa726"};
    QColor m_statusInfo{"#2196f3"};
    QColor m_statusInfoHover{"#42a5f5"};
};

#endif // THEMEPALETTE_H