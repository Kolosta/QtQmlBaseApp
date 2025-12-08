#include "ThemeColors.h"

// === TextColors ===
TextColors::TextColors(QObject* parent) : QObject(parent) {
    m_primary = new SimpleColorState(this, QColor("#ffffff"));
    m_secondary = new SimpleColorState(this, QColor("#b0b0b0"));
    m_disabled = new SimpleColorState(this, QColor("#666666"));
    m_onPrimary = new SimpleColorState(this, QColor("#ffffff"));
    m_onSecondary = new SimpleColorState(this, QColor("#000000"));
    m_onBackground = new SimpleColorState(this, QColor("#ffffff"));
    
    connect(m_primary, &SimpleColorState::changed, this, &TextColors::changed);
    connect(m_secondary, &SimpleColorState::changed, this, &TextColors::changed);
    connect(m_disabled, &SimpleColorState::changed, this, &TextColors::changed);
    connect(m_onPrimary, &SimpleColorState::changed, this, &TextColors::changed);
    connect(m_onSecondary, &SimpleColorState::changed, this, &TextColors::changed);
    connect(m_onBackground, &SimpleColorState::changed, this, &TextColors::changed);
}

void TextColors::loadFromJson(const QJsonObject& json) {
    if (json.contains("primary")) m_primary->loadFromJson(json["primary"].toObject());
    if (json.contains("secondary")) m_secondary->loadFromJson(json["secondary"].toObject());
    if (json.contains("disabled")) m_disabled->loadFromJson(json["disabled"].toObject());
    if (json.contains("onPrimary")) m_onPrimary->loadFromJson(json["onPrimary"].toObject());
    if (json.contains("onSecondary")) m_onSecondary->loadFromJson(json["onSecondary"].toObject());
    if (json.contains("onBackground")) m_onBackground->loadFromJson(json["onBackground"].toObject());
}

QJsonObject TextColors::toJson() const {
    QJsonObject json;
    json["primary"] = m_primary->toJson();
    json["secondary"] = m_secondary->toJson();
    json["disabled"] = m_disabled->toJson();
    json["onPrimary"] = m_onPrimary->toJson();
    json["onSecondary"] = m_onSecondary->toJson();
    json["onBackground"] = m_onBackground->toJson();
    return json;
}

void TextColors::copyFrom(const TextColors* other) {
    m_primary->copyFrom(other->m_primary);
    m_secondary->copyFrom(other->m_secondary);
    m_disabled->copyFrom(other->m_disabled);
    m_onPrimary->copyFrom(other->m_onPrimary);
    m_onSecondary->copyFrom(other->m_onSecondary);
    m_onBackground->copyFrom(other->m_onBackground);
}

// === BackgroundColors ===
BackgroundColors::BackgroundColors(QObject* parent) : QObject(parent) {
    m_primary = new SimpleColorState(this, QColor("#1e1e1e"));
    m_secondary = new SimpleColorState(this, QColor("#252525"));
    m_tertiary = new SimpleColorState(this, QColor("#2a2a2a"));
    
    connect(m_primary, &SimpleColorState::changed, this, &BackgroundColors::changed);
    connect(m_secondary, &SimpleColorState::changed, this, &BackgroundColors::changed);
    connect(m_tertiary, &SimpleColorState::changed, this, &BackgroundColors::changed);
}

void BackgroundColors::loadFromJson(const QJsonObject& json) {
    if (json.contains("primary")) m_primary->loadFromJson(json["primary"].toObject());
    if (json.contains("secondary")) m_secondary->loadFromJson(json["secondary"].toObject());
    if (json.contains("tertiary")) m_tertiary->loadFromJson(json["tertiary"].toObject());
}

QJsonObject BackgroundColors::toJson() const {
    QJsonObject json;
    json["primary"] = m_primary->toJson();
    json["secondary"] = m_secondary->toJson();
    json["tertiary"] = m_tertiary->toJson();
    return json;
}

void BackgroundColors::copyFrom(const BackgroundColors* other) {
    m_primary->copyFrom(other->m_primary);
    m_secondary->copyFrom(other->m_secondary);
    m_tertiary->copyFrom(other->m_tertiary);
}

// === SurfaceColors ===
SurfaceColors::SurfaceColors(QObject* parent) : QObject(parent) {
    m_primary = new SimpleColorState(this, QColor("#2d2d2d"));
    m_secondary = new SimpleColorState(this, QColor("#353535"));
    m_hover = new ColorState(this, QColor("#3d3d3d"));
    m_active = new ColorState(this, QColor("#4d4d4d"));
    m_disabled = new SimpleColorState(this, QColor("#252525"));
    
    connect(m_primary, &SimpleColorState::changed, this, &SurfaceColors::changed);
    connect(m_secondary, &SimpleColorState::changed, this, &SurfaceColors::changed);
    connect(m_hover, &ColorState::changed, this, &SurfaceColors::changed);
    connect(m_active, &ColorState::changed, this, &SurfaceColors::changed);
    connect(m_disabled, &SimpleColorState::changed, this, &SurfaceColors::changed);
}

void SurfaceColors::loadFromJson(const QJsonObject& json) {
    if (json.contains("primary")) m_primary->loadFromJson(json["primary"].toObject());
    if (json.contains("secondary")) m_secondary->loadFromJson(json["secondary"].toObject());
    if (json.contains("hover")) m_hover->loadFromJson(json["hover"].toObject());
    if (json.contains("active")) m_active->loadFromJson(json["active"].toObject());
    if (json.contains("disabled")) m_disabled->loadFromJson(json["disabled"].toObject());
}

QJsonObject SurfaceColors::toJson() const {
    QJsonObject json;
    json["primary"] = m_primary->toJson();
    json["secondary"] = m_secondary->toJson();
    json["hover"] = m_hover->toJson();
    json["active"] = m_active->toJson();
    json["disabled"] = m_disabled->toJson();
    return json;
}

void SurfaceColors::copyFrom(const SurfaceColors* other) {
    m_primary->copyFrom(other->m_primary);
    m_secondary->copyFrom(other->m_secondary);
    m_hover->copyFrom(other->m_hover);
    m_active->copyFrom(other->m_active);
    m_disabled->copyFrom(other->m_disabled);
}

// === BorderColors ===
BorderColors::BorderColors(QObject* parent) : QObject(parent) {
    m_default = new SimpleColorState(this, QColor("#3d3d3d"));
    m_focus = new SimpleColorState(this, QColor("#4a9eff"));
    m_active = new SimpleColorState(this, QColor("#6bb0ff"));
    m_pressed = new SimpleColorState(this, QColor("#2a7edf"));
    m_disabled = new SimpleColorState(this, QColor("#2d2d2d"));
    
    connect(m_default, &SimpleColorState::changed, this, &BorderColors::changed);
    connect(m_focus, &SimpleColorState::changed, this, &BorderColors::changed);
    connect(m_active, &SimpleColorState::changed, this, &BorderColors::changed);
    connect(m_pressed, &SimpleColorState::changed, this, &BorderColors::changed);
    connect(m_disabled, &SimpleColorState::changed, this, &BorderColors::changed);
}

void BorderColors::loadFromJson(const QJsonObject& json) {
    if (json.contains("default")) m_default->loadFromJson(json["default"].toObject());
    if (json.contains("focus")) m_focus->loadFromJson(json["focus"].toObject());
    if (json.contains("active")) m_active->loadFromJson(json["active"].toObject());
    if (json.contains("pressed")) m_pressed->loadFromJson(json["pressed"].toObject());
    if (json.contains("disabled")) m_disabled->loadFromJson(json["disabled"].toObject());
}

QJsonObject BorderColors::toJson() const {
    QJsonObject json;
    json["default"] = m_default->toJson();
    json["focus"] = m_focus->toJson();
    json["active"] = m_active->toJson();
    json["pressed"] = m_pressed->toJson();
    json["disabled"] = m_disabled->toJson();
    return json;
}

void BorderColors::copyFrom(const BorderColors* other) {
    m_default->copyFrom(other->m_default);
    m_focus->copyFrom(other->m_focus);
    m_active->copyFrom(other->m_active);
    m_pressed->copyFrom(other->m_pressed);
    m_disabled->copyFrom(other->m_disabled);
}

// === ThemeColors ===
ThemeColors::ThemeColors(QObject* parent) : QObject(parent) {
    m_primary = new ColorState(this, QColor("#0d7377"), QColor("#14a0a5"), QColor("#0a5b5e"), QColor("#084648"));
    m_secondary = new ColorState(this, QColor("#353535"), QColor("#454545"));
    m_accent = new ColorState(this, QColor("#4a9eff"), QColor("#6bb0ff"), QColor("#2a7edf"));
    m_success = new ColorState(this, QColor("#4caf50"), QColor("#66bb6a"));
    m_warning = new ColorState(this, QColor("#ff9800"), QColor("#ffa726"));
    m_error = new ColorState(this, QColor("#f44336"), QColor("#f55a4e"));
    m_info = new ColorState(this, QColor("#2196f3"), QColor("#42a5f5"));
    
    m_text = new TextColors(this);
    m_background = new BackgroundColors(this);
    m_surface = new SurfaceColors(this);
    m_border = new BorderColors(this);
    
    connect(m_primary, &ColorState::changed, this, &ThemeColors::changed);
    connect(m_secondary, &ColorState::changed, this, &ThemeColors::changed);
    connect(m_accent, &ColorState::changed, this, &ThemeColors::changed);
    connect(m_success, &ColorState::changed, this, &ThemeColors::changed);
    connect(m_warning, &ColorState::changed, this, &ThemeColors::changed);
    connect(m_error, &ColorState::changed, this, &ThemeColors::changed);
    connect(m_info, &ColorState::changed, this, &ThemeColors::changed);
    connect(m_text, &TextColors::changed, this, &ThemeColors::changed);
    connect(m_background, &BackgroundColors::changed, this, &ThemeColors::changed);
    connect(m_surface, &SurfaceColors::changed, this, &ThemeColors::changed);
    connect(m_border, &BorderColors::changed, this, &ThemeColors::changed);
}

void ThemeColors::loadFromJson(const QJsonObject& json) {
    if (json.contains("primary")) m_primary->loadFromJson(json["primary"].toObject());
    if (json.contains("secondary")) m_secondary->loadFromJson(json["secondary"].toObject());
    if (json.contains("accent")) m_accent->loadFromJson(json["accent"].toObject());
    if (json.contains("success")) m_success->loadFromJson(json["success"].toObject());
    if (json.contains("warning")) m_warning->loadFromJson(json["warning"].toObject());
    if (json.contains("error")) m_error->loadFromJson(json["error"].toObject());
    if (json.contains("info")) m_info->loadFromJson(json["info"].toObject());
    if (json.contains("text")) m_text->loadFromJson(json["text"].toObject());
    if (json.contains("background")) m_background->loadFromJson(json["background"].toObject());
    if (json.contains("surface")) m_surface->loadFromJson(json["surface"].toObject());
    if (json.contains("border")) m_border->loadFromJson(json["border"].toObject());
}

QJsonObject ThemeColors::toJson() const {
    QJsonObject json;
    json["primary"] = m_primary->toJson();
    json["secondary"] = m_secondary->toJson();
    json["accent"] = m_accent->toJson();
    json["success"] = m_success->toJson();
    json["warning"] = m_warning->toJson();
    json["error"] = m_error->toJson();
    json["info"] = m_info->toJson();
    json["text"] = m_text->toJson();
    json["background"] = m_background->toJson();
    json["surface"] = m_surface->toJson();
    json["border"] = m_border->toJson();
    return json;
}

void ThemeColors::copyFrom(const ThemeColors* other) {
    m_primary->copyFrom(other->m_primary);
    m_secondary->copyFrom(other->m_secondary);
    m_accent->copyFrom(other->m_accent);
    m_success->copyFrom(other->m_success);
    m_warning->copyFrom(other->m_warning);
    m_error->copyFrom(other->m_error);
    m_info->copyFrom(other->m_info);
    m_text->copyFrom(other->m_text);
    m_background->copyFrom(other->m_background);
    m_surface->copyFrom(other->m_surface);
    m_border->copyFrom(other->m_border);
}