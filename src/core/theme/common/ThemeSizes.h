#ifndef THEMESIZES_H
#define THEMESIZES_H

#include <QObject>
#include <QJsonObject>

class ThemeManager;

class ThemeSizes : public QObject {
    Q_OBJECT
    
    // Spacing - Valeurs AUTOMATIQUEMENT scalées
    Q_PROPERTY(int none READ none NOTIFY changed)
    Q_PROPERTY(int xxsmall READ xxsmall NOTIFY changed)
    Q_PROPERTY(int xsmall READ xsmall NOTIFY changed)
    Q_PROPERTY(int small READ small NOTIFY changed)
    Q_PROPERTY(int medium READ medium NOTIFY changed)
    Q_PROPERTY(int large READ large NOTIFY changed)
    Q_PROPERTY(int xlarge READ xlarge NOTIFY changed)
    Q_PROPERTY(int xxlarge READ xxlarge NOTIFY changed)
    Q_PROPERTY(int xxxlarge READ xxxlarge NOTIFY changed)
    
    // Radius
    Q_PROPERTY(int radiusNone READ radiusNone NOTIFY changed)
    Q_PROPERTY(int radiusSmall READ radiusSmall NOTIFY changed)
    Q_PROPERTY(int radiusMedium READ radiusMedium NOTIFY changed)
    Q_PROPERTY(int radiusLarge READ radiusLarge NOTIFY changed)
    Q_PROPERTY(int radiusXlarge READ radiusXlarge NOTIFY changed)
    Q_PROPERTY(int radiusRound READ radiusRound NOTIFY changed)
    
    // Borders
    Q_PROPERTY(int borderNone READ borderNone NOTIFY changed)
    Q_PROPERTY(int borderThin READ borderThin NOTIFY changed)
    Q_PROPERTY(int borderMedium READ borderMedium NOTIFY changed)
    Q_PROPERTY(int borderThick READ borderThick NOTIFY changed)

    // Spacings
    Q_PROPERTY(int spacingNone READ none NOTIFY changed)
    Q_PROPERTY(int spacingXxsmall READ xxsmall NOTIFY changed)
    Q_PROPERTY(int spacingXsmall READ xsmall NOTIFY changed)
    Q_PROPERTY(int spacingSmall READ small NOTIFY changed)
    Q_PROPERTY(int spacingMedium READ medium NOTIFY changed)
    Q_PROPERTY(int spacingLarge READ large NOTIFY changed)
    Q_PROPERTY(int spacingXlarge READ xlarge NOTIFY changed)
    Q_PROPERTY(int spacingXxlarge READ xxlarge NOTIFY changed)
    Q_PROPERTY(int spacingXxxlarge READ xxxlarge NOTIFY changed)
    
    // Font sizes
    Q_PROPERTY(int fontXsmall READ fontXsmall NOTIFY changed)
    Q_PROPERTY(int fontSmall READ fontSmall NOTIFY changed)
    Q_PROPERTY(int fontMedium READ fontMedium NOTIFY changed)
    Q_PROPERTY(int fontLarge READ fontLarge NOTIFY changed)
    Q_PROPERTY(int fontXlarge READ fontXlarge NOTIFY changed)
    Q_PROPERTY(int fontXxlarge READ fontXxlarge NOTIFY changed)
    Q_PROPERTY(int fontXxxlarge READ fontXxxlarge NOTIFY changed)
    
    // Font weights (pas de scale)
    Q_PROPERTY(int fontWeightLight READ fontWeightLight CONSTANT)
    Q_PROPERTY(int fontWeightNormal READ fontWeightNormal CONSTANT)
    Q_PROPERTY(int fontWeightMedium READ fontWeightMedium CONSTANT)
    Q_PROPERTY(int fontWeightSemibold READ fontWeightSemibold CONSTANT)
    Q_PROPERTY(int fontWeightBold READ fontWeightBold CONSTANT)
    
    // Animation durations (pas de scale)
    Q_PROPERTY(int animInstant READ animInstant CONSTANT)
    Q_PROPERTY(int animFast READ animFast CONSTANT)
    Q_PROPERTY(int animNormal READ animNormal CONSTANT)
    Q_PROPERTY(int animSlow READ animSlow CONSTANT)


public:
    explicit ThemeSizes(ThemeManager* manager, QObject *parent = nullptr);
    
    // Getters avec scaling automatique
    int none() const;
    int xxsmall() const;
    int xsmall() const;
    int small() const;
    int medium() const;
    int large() const;
    int xlarge() const;
    int xxlarge() const;
    int xxxlarge() const;
    
    int radiusNone() const;
    int radiusSmall() const;
    int radiusMedium() const;
    int radiusLarge() const;
    int radiusXlarge() const;
    int radiusRound() const;
    
    int borderNone() const;
    int borderThin() const;
    int borderMedium() const;
    int borderThick() const;

    int spacingNone() const;
    int spacingXxsmall() const;
    int spacingXsmall() const;
    int spacingSmall() const;
    int spacingMedium() const;
    int spacingLarge() const;
    int spacingXlarge() const;
    int spacingXxlarge() const;
    int spacingXxxlarge() const;
    
    int fontXsmall() const;
    int fontSmall() const;
    int fontMedium() const;
    int fontLarge() const;
    int fontXlarge() const;
    int fontXxlarge() const;
    int fontXxxlarge() const;
    
    int fontWeightLight() const { return 300; }
    int fontWeightNormal() const { return 400; }
    int fontWeightMedium() const { return 500; }
    int fontWeightSemibold() const { return 600; }
    int fontWeightBold() const { return 700; }
    
    int animInstant() const { return 0; }
    int animFast() const { return 50; }
    int animNormal() const { return 150; }
    int animSlow() const { return 300; }
    
    // Setters pour les valeurs RAW (utilisés par l'éditeur et le chargement)
    void setRawNone(int v) { m_none = v; emit changed(); }
    void setRawXxsmall(int v) { m_xxsmall = v; emit changed(); }
    void setRawXsmall(int v) { m_xsmall = v; emit changed(); }
    void setRawSmall(int v) { m_small = v; emit changed(); }
    void setRawMedium(int v) { m_medium = v; emit changed(); }
    void setRawLarge(int v) { m_large = v; emit changed(); }
    void setRawXlarge(int v) { m_xlarge = v; emit changed(); }
    void setRawXxlarge(int v) { m_xxlarge = v; emit changed(); }
    void setRawXxxlarge(int v) { m_xxxlarge = v; emit changed(); }
    
    void setRawRadiusSmall(int v) { m_radiusSmall = v; emit changed(); }
    void setRawRadiusMedium(int v) { m_radiusMedium = v; emit changed(); }
    void setRawRadiusLarge(int v) { m_radiusLarge = v; emit changed(); }
    void setRawRadiusXlarge(int v) { m_radiusXlarge = v; emit changed(); }
    
    void setRawBorderThin(int v) { m_borderThin = v; emit changed(); }
    void setRawBorderMedium(int v) { m_borderMedium = v; emit changed(); }
    void setRawBorderThick(int v) { m_borderThick = v; emit changed(); }

    void setRawSpacingNone(int v) { m_none = v; emit changed(); }
    void setRawSpacingXxsmall(int v) { m_xxsmall = v; emit changed(); }
    void setRawSpacingXsmall(int v) { m_xsmall = v; emit changed(); }
    void setRawSpacingSmall(int v) { m_small = v; emit changed(); }
    void setRawSpacingMedium(int v) { m_medium = v; emit changed(); }
    void setRawSpacingLarge(int v) { m_large = v; emit changed(); }
    void setRawSpacingXlarge(int v) { m_xlarge = v; emit changed(); }
    void setRawSpacingXxlarge(int v) { m_xxlarge = v; emit changed(); }
    void setRawSpacingXxxlarge(int v) { m_xxxlarge = v; emit changed(); }
    
    void setRawFontXsmall(int v) { m_fontXsmall = v; emit changed(); }
    void setRawFontSmall(int v) { m_fontSmall = v; emit changed(); }
    void setRawFontMedium(int v) { m_fontMedium = v; emit changed(); }
    void setRawFontLarge(int v) { m_fontLarge = v; emit changed(); }
    void setRawFontXlarge(int v) { m_fontXlarge = v; emit changed(); }
    void setRawFontXxlarge(int v) { m_fontXxlarge = v; emit changed(); }
    void setRawFontXxxlarge(int v) { m_fontXxxlarge = v; emit changed(); }
    
    // Accès aux valeurs brutes pour sauvegarde
    int rawSmall() const { return m_small; }
    int rawMedium() const { return m_medium; }
    int rawLarge() const { return m_large; }
    // ... (ajouter tous les raw getters si besoin)
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void resetToDefaults();

signals:
    void changed();

private:
    ThemeManager* m_manager;
    
    // Valeurs RAW (base 100%)
    int m_none{0};
    int m_xxsmall{2};
    int m_xsmall{4};
    int m_small{5};
    int m_medium{10};
    int m_large{15};
    int m_xlarge{20};
    int m_xxlarge{30};
    int m_xxxlarge{40};
    
    int m_radiusSmall{4};
    int m_radiusMedium{6};
    int m_radiusLarge{12};
    int m_radiusXlarge{16};
    int m_radiusRound{999};
    
    int m_borderThin{1};
    int m_borderMedium{2};
    int m_borderThick{3};

    int m_spacingNone{0};
    int m_spacingXxsmall{2};
    int m_spacingXsmall{4};
    int m_spacingSmall{5};
    int m_spacingMedium{10};
    int m_spacingLarge{15};
    int m_spacingXlarge{20};
    int m_spacingXxlarge{30};
    int m_spacingXxxlarge{40};
    
    int m_fontXsmall{10};
    int m_fontSmall{11};
    int m_fontMedium{13};
    int m_fontLarge{16};
    int m_fontXlarge{18};
    int m_fontXxlarge{24};
    int m_fontXxxlarge{32};
};

#endif // THEMESIZES_H