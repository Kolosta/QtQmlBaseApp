#include "ThemeSizes.h"
#include "core/ThemeManager.h"
#include <QJsonObject>
#include <cmath>

ThemeSizes::ThemeSizes(ThemeManager* manager, QObject *parent)
    : QObject(parent), m_manager(manager)
{
}

// Fonction helper pour scaler
inline int scaleValue(int raw, qreal scale) {
    return static_cast<int>(std::round(raw * scale));
}

// ===== SPACING GETTERS (avec scaling auto) =====
int ThemeSizes::none() const { return scaleValue(m_none, m_manager->scale()); }
int ThemeSizes::xxsmall() const { return scaleValue(m_xxsmall, m_manager->scale()); }
int ThemeSizes::xsmall() const { return scaleValue(m_xsmall, m_manager->scale()); }
int ThemeSizes::small() const { return scaleValue(m_small, m_manager->scale()); }
int ThemeSizes::medium() const { return scaleValue(m_medium, m_manager->scale()); }
int ThemeSizes::large() const { return scaleValue(m_large, m_manager->scale()); }
int ThemeSizes::xlarge() const { return scaleValue(m_xlarge, m_manager->scale()); }
int ThemeSizes::xxlarge() const { return scaleValue(m_xxlarge, m_manager->scale()); }
int ThemeSizes::xxxlarge() const { return scaleValue(m_xxxlarge, m_manager->scale()); }

// ===== RADIUS GETTERS =====
int ThemeSizes::radiusNone() const { return 0; }
int ThemeSizes::radiusSmall() const { return scaleValue(m_radiusSmall, m_manager->scale()); }
int ThemeSizes::radiusMedium() const { return scaleValue(m_radiusMedium, m_manager->scale()); }
int ThemeSizes::radiusLarge() const { return scaleValue(m_radiusLarge, m_manager->scale()); }
int ThemeSizes::radiusXlarge() const { return scaleValue(m_radiusXlarge, m_manager->scale()); }
int ThemeSizes::radiusRound() const { return 999; }

// ===== BORDER GETTERS =====
int ThemeSizes::borderNone() const { return 0; }
int ThemeSizes::borderThin() const { return scaleValue(m_borderThin, m_manager->scale()); }
int ThemeSizes::borderMedium() const { return scaleValue(m_borderMedium, m_manager->scale()); }
int ThemeSizes::borderThick() const { return scaleValue(m_borderThick, m_manager->scale()); }

// ===== FONT GETTERS =====
int ThemeSizes::fontXsmall() const { return scaleValue(m_fontXsmall, m_manager->scale()); }
int ThemeSizes::fontSmall() const { return scaleValue(m_fontSmall, m_manager->scale()); }
int ThemeSizes::fontMedium() const { return scaleValue(m_fontMedium, m_manager->scale()); }
int ThemeSizes::fontLarge() const { return scaleValue(m_fontLarge, m_manager->scale()); }
int ThemeSizes::fontXlarge() const { return scaleValue(m_fontXlarge, m_manager->scale()); }
int ThemeSizes::fontXxlarge() const { return scaleValue(m_fontXxlarge, m_manager->scale()); }
int ThemeSizes::fontXxxlarge() const { return scaleValue(m_fontXxxlarge, m_manager->scale()); }

void ThemeSizes::loadFromJson(const QJsonObject& json) {
    if (json.isEmpty()) return;
    
    // Spacing
    if (json.contains("none")) m_none = json["none"].toInt(0);
    if (json.contains("xxsmall")) m_xxsmall = json["xxsmall"].toInt(2);
    if (json.contains("xsmall")) m_xsmall = json["xsmall"].toInt(4);
    if (json.contains("small")) m_small = json["small"].toInt(5);
    if (json.contains("medium")) m_medium = json["medium"].toInt(10);
    if (json.contains("large")) m_large = json["large"].toInt(15);
    if (json.contains("xlarge")) m_xlarge = json["xlarge"].toInt(20);
    if (json.contains("xxlarge")) m_xxlarge = json["xxlarge"].toInt(30);
    if (json.contains("xxxlarge")) m_xxxlarge = json["xxxlarge"].toInt(40);
    
    // Radius
    if (json.contains("radius_small")) m_radiusSmall = json["radius_small"].toInt(4);
    if (json.contains("radius_medium")) m_radiusMedium = json["radius_medium"].toInt(6);
    if (json.contains("radius_large")) m_radiusLarge = json["radius_large"].toInt(12);
    if (json.contains("radius_xlarge")) m_radiusXlarge = json["radius_xlarge"].toInt(16);
    
    // Borders
    if (json.contains("border_thin")) m_borderThin = json["border_thin"].toInt(1);
    if (json.contains("border_medium")) m_borderMedium = json["border_medium"].toInt(2);
    if (json.contains("border_thick")) m_borderThick = json["border_thick"].toInt(3);
    
    // Fonts
    if (json.contains("font_xsmall")) m_fontXsmall = json["font_xsmall"].toInt(10);
    if (json.contains("font_small")) m_fontSmall = json["font_small"].toInt(11);
    if (json.contains("font_medium")) m_fontMedium = json["font_medium"].toInt(13);
    if (json.contains("font_large")) m_fontLarge = json["font_large"].toInt(16);
    if (json.contains("font_xlarge")) m_fontXlarge = json["font_xlarge"].toInt(18);
    if (json.contains("font_xxlarge")) m_fontXxlarge = json["font_xxlarge"].toInt(24);
    if (json.contains("font_xxxlarge")) m_fontXxxlarge = json["font_xxxlarge"].toInt(32);
    
    emit changed();
}

QJsonObject ThemeSizes::toJson() const {
    QJsonObject json;
    
    // Spacing
    json["none"] = m_none;
    json["xxsmall"] = m_xxsmall;
    json["xsmall"] = m_xsmall;
    json["small"] = m_small;
    json["medium"] = m_medium;
    json["large"] = m_large;
    json["xlarge"] = m_xlarge;
    json["xxlarge"] = m_xxlarge;
    json["xxxlarge"] = m_xxxlarge;
    
    // Radius
    json["radius_small"] = m_radiusSmall;
    json["radius_medium"] = m_radiusMedium;
    json["radius_large"] = m_radiusLarge;
    json["radius_xlarge"] = m_radiusXlarge;
    
    // Borders
    json["border_thin"] = m_borderThin;
    json["border_medium"] = m_borderMedium;
    json["border_thick"] = m_borderThick;
    
    // Fonts
    json["font_xsmall"] = m_fontXsmall;
    json["font_small"] = m_fontSmall;
    json["font_medium"] = m_fontMedium;
    json["font_large"] = m_fontLarge;
    json["font_xlarge"] = m_fontXlarge;
    json["font_xxlarge"] = m_fontXxlarge;
    json["font_xxxlarge"] = m_fontXxxlarge;
    
    return json;
}

void ThemeSizes::resetToDefaults() {
    m_none = 0;
    m_xxsmall = 2;
    m_xsmall = 4;
    m_small = 5;
    m_medium = 10;
    m_large = 15;
    m_xlarge = 20;
    m_xxlarge = 30;
    m_xxxlarge = 40;
    
    m_radiusSmall = 4;
    m_radiusMedium = 6;
    m_radiusLarge = 12;
    m_radiusXlarge = 16;
    
    m_borderThin = 1;
    m_borderMedium = 2;
    m_borderThick = 3;
    
    m_fontXsmall = 10;
    m_fontSmall = 11;
    m_fontMedium = 13;
    m_fontLarge = 16;
    m_fontXlarge = 18;
    m_fontXxlarge = 24;
    m_fontXxxlarge = 32;
    
    emit changed();
}