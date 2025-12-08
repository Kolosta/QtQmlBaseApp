#include "ComponentStyles.h"
#include "core/theme/common/ThemePalette.h"
#include "core/theme/common/ThemeSizes.h"
#include "core/ThemeManager.h"
#include <QJsonObject>
#include <cmath>

// ===== PreferencesWindowStyle =====
PreferencesWindowStyle::PreferencesWindowStyle(ThemePalette* palette, ThemeSizes* sizes, 
                                               ThemeManager* manager, QObject* parent)
    : QObject(parent), m_palette(palette), m_sizes(sizes), m_manager(manager)
{
}

QColor PreferencesWindowStyle::background() const {
    if (m_overrideBackground.has_value()) 
        return m_overrideBackground.value();
    return m_palette->property("backgroundPrimary").value<QColor>();
}

QColor PreferencesWindowStyle::sidebarBackground() const {
    if (m_overrideSidebarBg.has_value()) 
        return m_overrideSidebarBg.value();
    return m_palette->property("backgroundSecondary").value<QColor>();
}

int PreferencesWindowStyle::sidebarWidth() const {
    int raw = m_overrideSidebarWidth.value_or(180);
    return static_cast<int>(std::round(raw * m_manager->scale()));
}

void PreferencesWindowStyle::setBackground(const QColor& c) {
    m_overrideBackground = c;
    emit changed();
}

void PreferencesWindowStyle::setSidebarBackground(const QColor& c) {
    m_overrideSidebarBg = c;
    emit changed();
}

void PreferencesWindowStyle::setSidebarWidth(int w) {
    m_overrideSidebarWidth = w;
    emit changed();
}

void PreferencesWindowStyle::resetBackground() {
    m_overrideBackground.reset();
    emit changed();
}

void PreferencesWindowStyle::resetSidebarBackground() {
    m_overrideSidebarBg.reset();
    emit changed();
}

void PreferencesWindowStyle::resetSidebarWidth() {
    m_overrideSidebarWidth.reset();
    emit changed();
}

void PreferencesWindowStyle::resetAll() {
    m_overrideBackground.reset();
    m_overrideSidebarBg.reset();
    m_overrideSidebarWidth.reset();
    emit changed();
}

void PreferencesWindowStyle::loadFromJson(const QJsonObject& json) {
    if (json.contains("background")) {
        QString colorStr = json["background"].toString();
        if (!colorStr.isEmpty() && colorStr != "null") {
            m_overrideBackground = QColor(colorStr);
        }
    }
    if (json.contains("sidebar_background")) {
        QString colorStr = json["sidebar_background"].toString();
        if (!colorStr.isEmpty() && colorStr != "null") {
            m_overrideSidebarBg = QColor(colorStr);
        }
    }
    if (json.contains("sidebar_width")) {
        m_overrideSidebarWidth = json["sidebar_width"].toInt();
    }
    emit changed();
}

QJsonObject PreferencesWindowStyle::toJson() const {
    QJsonObject json;
    if (m_overrideBackground.has_value()) {
        json["background"] = m_overrideBackground.value().name();
    }
    if (m_overrideSidebarBg.has_value()) {
        json["sidebar_background"] = m_overrideSidebarBg.value().name();
    }
    if (m_overrideSidebarWidth.has_value()) {
        json["sidebar_width"] = m_overrideSidebarWidth.value();
    }
    return json;
}

// ===== MenuBarStyle =====
MenuBarStyle::MenuBarStyle(ThemePalette* palette, ThemeSizes* sizes, 
                           ThemeManager* manager, QObject* parent)
    : QObject(parent), m_palette(palette), m_sizes(sizes), m_manager(manager)
{
}

QColor MenuBarStyle::background() const {
    if (m_overrideBackground.has_value()) 
        return m_overrideBackground.value();
    return m_palette->property("backgroundSecondary").value<QColor>();
}

QColor MenuBarStyle::text() const {
    if (m_overrideText.has_value()) 
        return m_overrideText.value();
    return m_palette->property("textPrimary").value<QColor>();
}

QColor MenuBarStyle::hoverBackground() const {
    if (m_overrideHoverBg.has_value()) 
        return m_overrideHoverBg.value();
    return m_palette->property("surfaceHover").value<QColor>();
}

int MenuBarStyle::height() const {
    int raw = m_overrideHeight.value_or(30);
    return static_cast<int>(std::round(raw * m_manager->scale()));
}

void MenuBarStyle::setBackground(const QColor& c) {
    m_overrideBackground = c;
    emit changed();
}

void MenuBarStyle::setText(const QColor& c) {
    m_overrideText = c;
    emit changed();
}

void MenuBarStyle::setHoverBackground(const QColor& c) {
    m_overrideHoverBg = c;
    emit changed();
}

void MenuBarStyle::setHeight(int h) {
    m_overrideHeight = h;
    emit changed();
}

void MenuBarStyle::resetBackground() { m_overrideBackground.reset(); emit changed(); }
void MenuBarStyle::resetText() { m_overrideText.reset(); emit changed(); }
void MenuBarStyle::resetHoverBackground() { m_overrideHoverBg.reset(); emit changed(); }
void MenuBarStyle::resetHeight() { m_overrideHeight.reset(); emit changed(); }

void MenuBarStyle::resetAll() {
    m_overrideBackground.reset();
    m_overrideText.reset();
    m_overrideHoverBg.reset();
    m_overrideHeight.reset();
    emit changed();
}

void MenuBarStyle::loadFromJson(const QJsonObject& json) {
    if (json.contains("background")) {
        QString colorStr = json["background"].toString();
        if (!colorStr.isEmpty() && colorStr != "null") {
            m_overrideBackground = QColor(colorStr);
        }
    }
    if (json.contains("text")) {
        QString colorStr = json["text"].toString();
        if (!colorStr.isEmpty() && colorStr != "null") {
            m_overrideText = QColor(colorStr);
        }
    }
    if (json.contains("hover_background")) {
        QString colorStr = json["hover_background"].toString();
        if (!colorStr.isEmpty() && colorStr != "null") {
            m_overrideHoverBg = QColor(colorStr);
        }
    }
    if (json.contains("height")) {
        m_overrideHeight = json["height"].toInt();
    }
    emit changed();
}

QJsonObject MenuBarStyle::toJson() const {
    QJsonObject json;
    if (m_overrideBackground.has_value()) {
        json["background"] = m_overrideBackground.value().name();
    }
    if (m_overrideText.has_value()) {
        json["text"] = m_overrideText.value().name();
    }
    if (m_overrideHoverBg.has_value()) {
        json["hover_background"] = m_overrideHoverBg.value().name();
    }
    if (m_overrideHeight.has_value()) {
        json["height"] = m_overrideHeight.value();
    }
    return json;
}

// ===== ButtonStyle =====
ButtonStyle::ButtonStyle(ThemePalette* palette, ThemeSizes* sizes, 
                         ThemeManager* manager, QObject* parent)
    : QObject(parent), m_palette(palette), m_sizes(sizes), m_manager(manager)
{
}

QColor ButtonStyle::background() const {
    if (m_overrideBackground.has_value()) 
        return m_overrideBackground.value();
    return m_palette->property("surfacePrimary").value<QColor>();
}

QColor ButtonStyle::hoverBackground() const {
    if (m_overrideHoverBg.has_value()) 
        return m_overrideHoverBg.value();
    return m_palette->property("surfaceHover").value<QColor>();
}

QColor ButtonStyle::activeBackground() const {
    if (m_overrideActiveBg.has_value()) 
        return m_overrideActiveBg.value();
    return m_palette->property("surfaceActive").value<QColor>();
}

QColor ButtonStyle::text() const {
    if (m_overrideText.has_value()) 
        return m_overrideText.value();
    return m_palette->property("textPrimary").value<QColor>();
}

QColor ButtonStyle::border() const {
    if (m_overrideBorder.has_value()) 
        return m_overrideBorder.value();
    return m_palette->property("borderPrimary").value<QColor>();
}

int ButtonStyle::borderWidth() const {
    if (m_overrideBorderWidth.has_value()) {
        return static_cast<int>(std::round(m_overrideBorderWidth.value() * m_manager->scale()));
    }
    return m_sizes->borderThin();
}

int ButtonStyle::radius() const {
    if (m_overrideRadius.has_value()) {
        return static_cast<int>(std::round(m_overrideRadius.value() * m_manager->scale()));
    }
    return m_sizes->radiusMedium();
}

int ButtonStyle::padding() const {
    if (m_overridePadding.has_value()) {
        return static_cast<int>(std::round(m_overridePadding.value() * m_manager->scale()));
    }
    return m_sizes->medium();
}

void ButtonStyle::setBackground(const QColor& c) {
    m_overrideBackground = c;
    emit changed();
}

void ButtonStyle::setHoverBackground(const QColor& c) {
    m_overrideHoverBg = c;
    emit changed();
}

void ButtonStyle::setActiveBackground(const QColor& c) {
    m_overrideActiveBg = c;
    emit changed();
}

void ButtonStyle::setText(const QColor& c) {
    m_overrideText = c;
    emit changed();
}

void ButtonStyle::setBorder(const QColor& c) {
    m_overrideBorder = c;
    emit changed();
}

void ButtonStyle::setBorderWidth(int w) {
    m_overrideBorderWidth = w;
    emit changed();
}

void ButtonStyle::setRadius(int r) {
    m_overrideRadius = r;
    emit changed();
}

void ButtonStyle::setPadding(int p) {
    m_overridePadding = p;
    emit changed();
}

void ButtonStyle::resetAll() {
    m_overrideBackground.reset();
    m_overrideHoverBg.reset();
    m_overrideActiveBg.reset();
    m_overrideText.reset();
    m_overrideBorder.reset();
    m_overrideBorderWidth.reset();
    m_overrideRadius.reset();
    m_overridePadding.reset();
    emit changed();
}

void ButtonStyle::loadFromJson(const QJsonObject& json) {
    if (json.contains("background")) {
        QString colorStr = json["background"].toString();
        if (!colorStr.isEmpty() && colorStr != "null") {
            m_overrideBackground = QColor(colorStr);
        }
    }
    if (json.contains("hover_background")) {
        QString colorStr = json["hover_background"].toString();
        if (!colorStr.isEmpty() && colorStr != "null") {
            m_overrideHoverBg = QColor(colorStr);
        }
    }
    if (json.contains("active_background")) {
        QString colorStr = json["active_background"].toString();
        if (!colorStr.isEmpty() && colorStr != "null") {
            m_overrideActiveBg = QColor(colorStr);
        }
    }
    if (json.contains("text")) {
        QString colorStr = json["text"].toString();
        if (!colorStr.isEmpty() && colorStr != "null") {
            m_overrideText = QColor(colorStr);
        }
    }
    if (json.contains("border")) {
        QString colorStr = json["border"].toString();
        if (!colorStr.isEmpty() && colorStr != "null") {
            m_overrideBorder = QColor(colorStr);
        }
    }
    if (json.contains("border_width")) {
        m_overrideBorderWidth = json["border_width"].toInt();
    }
    if (json.contains("radius")) {
        m_overrideRadius = json["radius"].toInt();
    }
    if (json.contains("padding")) {
        m_overridePadding = json["padding"].toInt();
    }
    emit changed();
}

QJsonObject ButtonStyle::toJson() const {
    QJsonObject json;
    if (m_overrideBackground.has_value()) {
        json["background"] = m_overrideBackground.value().name();
    }
    if (m_overrideHoverBg.has_value()) {
        json["hover_background"] = m_overrideHoverBg.value().name();
    }
    if (m_overrideActiveBg.has_value()) {
        json["active_background"] = m_overrideActiveBg.value().name();
    }
    if (m_overrideText.has_value()) {
        json["text"] = m_overrideText.value().name();
    }
    if (m_overrideBorder.has_value()) {
        json["border"] = m_overrideBorder.value().name();
    }
    if (m_overrideBorderWidth.has_value()) {
        json["border_width"] = m_overrideBorderWidth.value();
    }
    if (m_overrideRadius.has_value()) {
        json["radius"] = m_overrideRadius.value();
    }
    if (m_overridePadding.has_value()) {
        json["padding"] = m_overridePadding.value();
    }
    return json;
}
