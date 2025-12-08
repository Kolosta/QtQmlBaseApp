#include "ThemeAtoms.h"

ColorAtom::ColorAtom(QObject *parent) : QObject(parent) {}

void ColorAtom::loadFromJson(const QJsonObject& json) {
    if (json.contains("bgPrimary")) m_bgPrimary = QColor(json["bgPrimary"].toString());
    if (json.contains("bgSecondary")) m_bgSecondary = QColor(json["bgSecondary"].toString());
    if (json.contains("bgTertiary")) m_bgTertiary = QColor(json["bgTertiary"].toString());
    if (json.contains("surfPrimary")) m_surfPrimary = QColor(json["surfPrimary"].toString());
    if (json.contains("surfSecondary")) m_surfSecondary = QColor(json["surfSecondary"].toString());
    if (json.contains("surfHover")) m_surfHover = QColor(json["surfHover"].toString());
    if (json.contains("surfActive")) m_surfActive = QColor(json["surfActive"].toString());
    if (json.contains("surfDisabled")) m_surfDisabled = QColor(json["surfDisabled"].toString());
    if (json.contains("primBase")) m_primBase = QColor(json["primBase"].toString());
    if (json.contains("primHover")) m_primHover = QColor(json["primHover"].toString());
    if (json.contains("primActive")) m_primActive = QColor(json["primActive"].toString());
    if (json.contains("primDisabled")) m_primDisabled = QColor(json["primDisabled"].toString());
    if (json.contains("textPrimary")) m_textPrimary = QColor(json["textPrimary"].toString());
    if (json.contains("textSecondary")) m_textSecondary = QColor(json["textSecondary"].toString());
    if (json.contains("textTertiary")) m_textTertiary = QColor(json["textTertiary"].toString());
    if (json.contains("textDisabled")) m_textDisabled = QColor(json["textDisabled"].toString());
    if (json.contains("textOnPrimary")) m_textOnPrimary = QColor(json["textOnPrimary"].toString());
    if (json.contains("borderPrimary")) m_borderPrimary = QColor(json["borderPrimary"].toString());
    if (json.contains("borderSecondary")) m_borderSecondary = QColor(json["borderSecondary"].toString());
    if (json.contains("borderFocus")) m_borderFocus = QColor(json["borderFocus"].toString());
    if (json.contains("borderDisabled")) m_borderDisabled = QColor(json["borderDisabled"].toString());
    if (json.contains("accentBase")) m_accentBase = QColor(json["accentBase"].toString());
    if (json.contains("accentHover")) m_accentHover = QColor(json["accentHover"].toString());
    if (json.contains("accentActive")) m_accentActive = QColor(json["accentActive"].toString());
    if (json.contains("statError")) m_statError = QColor(json["statError"].toString());
    if (json.contains("statErrorHover")) m_statErrorHover = QColor(json["statErrorHover"].toString());
    if (json.contains("statSuccess")) m_statSuccess = QColor(json["statSuccess"].toString());
    if (json.contains("statSuccessHover")) m_statSuccessHover = QColor(json["statSuccessHover"].toString());
    if (json.contains("statWarning")) m_statWarning = QColor(json["statWarning"].toString());
    if (json.contains("statWarningHover")) m_statWarningHover = QColor(json["statWarningHover"].toString());
    if (json.contains("statInfo")) m_statInfo = QColor(json["statInfo"].toString());
    if (json.contains("statInfoHover")) m_statInfoHover = QColor(json["statInfoHover"].toString());
    emit changed();
}

QJsonObject ColorAtom::toJson() const {
    QJsonObject json;
    json["bgPrimary"] = m_bgPrimary.name();
    json["bgSecondary"] = m_bgSecondary.name();
    json["bgTertiary"] = m_bgTertiary.name();
    json["surfPrimary"] = m_surfPrimary.name();
    json["surfSecondary"] = m_surfSecondary.name();
    json["surfHover"] = m_surfHover.name();
    json["surfActive"] = m_surfActive.name();
    json["surfDisabled"] = m_surfDisabled.name();
    json["primBase"] = m_primBase.name();
    json["primHover"] = m_primHover.name();
    json["primActive"] = m_primActive.name();
    json["primDisabled"] = m_primDisabled.name();
    json["textPrimary"] = m_textPrimary.name();
    json["textSecondary"] = m_textSecondary.name();
    json["textTertiary"] = m_textTertiary.name();
    json["textDisabled"] = m_textDisabled.name();
    json["textOnPrimary"] = m_textOnPrimary.name();
    json["borderPrimary"] = m_borderPrimary.name();
    json["borderSecondary"] = m_borderSecondary.name();
    json["borderFocus"] = m_borderFocus.name();
    json["borderDisabled"] = m_borderDisabled.name();
    json["accentBase"] = m_accentBase.name();
    json["accentHover"] = m_accentHover.name();
    json["accentActive"] = m_accentActive.name();
    json["statError"] = m_statError.name();
    json["statErrorHover"] = m_statErrorHover.name();
    json["statSuccess"] = m_statSuccess.name();
    json["statSuccessHover"] = m_statSuccessHover.name();
    json["statWarning"] = m_statWarning.name();
    json["statWarningHover"] = m_statWarningHover.name();
    json["statInfo"] = m_statInfo.name();
    json["statInfoHover"] = m_statInfoHover.name();
    return json;
}

void ColorAtom::copyFrom(const ColorAtom* other) {
    m_bgPrimary = other->m_bgPrimary;
    m_bgSecondary = other->m_bgSecondary;
    m_bgTertiary = other->m_bgTertiary;
    m_surfPrimary = other->m_surfPrimary;
    m_surfSecondary = other->m_surfSecondary;
    m_surfHover = other->m_surfHover;
    m_surfActive = other->m_surfActive;
    m_surfDisabled = other->m_surfDisabled;
    m_primBase = other->m_primBase;
    m_primHover = other->m_primHover;
    m_primActive = other->m_primActive;
    m_primDisabled = other->m_primDisabled;
    m_textPrimary = other->m_textPrimary;
    m_textSecondary = other->m_textSecondary;
    m_textTertiary = other->m_textTertiary;
    m_textDisabled = other->m_textDisabled;
    m_textOnPrimary = other->m_textOnPrimary;
    m_borderPrimary = other->m_borderPrimary;
    m_borderSecondary = other->m_borderSecondary;
    m_borderFocus = other->m_borderFocus;
    m_borderDisabled = other->m_borderDisabled;
    m_accentBase = other->m_accentBase;
    m_accentHover = other->m_accentHover;
    m_accentActive = other->m_accentActive;
    m_statError = other->m_statError;
    m_statErrorHover = other->m_statErrorHover;
    m_statSuccess = other->m_statSuccess;
    m_statSuccessHover = other->m_statSuccessHover;
    m_statWarning = other->m_statWarning;
    m_statWarningHover = other->m_statWarningHover;
    m_statInfo = other->m_statInfo;
    m_statInfoHover = other->m_statInfoHover;
    emit changed();
}

SizeAtom::SizeAtom(QObject *parent) : QObject(parent) {}

void SizeAtom::loadFromJson(const QJsonObject& json) {
    if (json.contains("none")) m_none = json["none"].toInt();
    if (json.contains("xxsmall")) m_xxsmall = json["xxsmall"].toInt();
    if (json.contains("xsmall")) m_xsmall = json["xsmall"].toInt();
    if (json.contains("small")) m_small = json["small"].toInt();
    if (json.contains("medium")) m_medium = json["medium"].toInt();
    if (json.contains("large")) m_large = json["large"].toInt();
    if (json.contains("xlarge")) m_xlarge = json["xlarge"].toInt();
    if (json.contains("xxlarge")) m_xxlarge = json["xxlarge"].toInt();
    if (json.contains("xxxlarge")) m_xxxlarge = json["xxxlarge"].toInt();
    emit changed();
}

QJsonObject SizeAtom::toJson() const {
    QJsonObject json;
    json["none"] = m_none;
    json["xxsmall"] = m_xxsmall;
    json["xsmall"] = m_xsmall;
    json["small"] = m_small;
    json["medium"] = m_medium;
    json["large"] = m_large;
    json["xlarge"] = m_xlarge;
    json["xxlarge"] = m_xxlarge;
    json["xxxlarge"] = m_xxxlarge;
    return json;
}

void SizeAtom::copyFrom(const SizeAtom* other) {
    m_none = other->m_none;
    m_xxsmall = other->m_xxsmall;
    m_xsmall = other->m_xsmall;
    m_small = other->m_small;
    m_medium = other->m_medium;
    m_large = other->m_large;
    m_xlarge = other->m_xlarge;
    m_xxlarge = other->m_xxlarge;
    m_xxxlarge = other->m_xxxlarge;
    emit changed();
}

WeightAtom::WeightAtom(QObject *parent) : QObject(parent) {}
AnimationAtom::AnimationAtom(QObject *parent) : QObject(parent) {}