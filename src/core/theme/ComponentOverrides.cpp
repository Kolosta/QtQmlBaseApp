#include "ComponentOverrides.h"
#include "core/ThemeManager.h"

ComponentOverride::ComponentOverride(const QString& componentName, ThemeManager* manager, QObject* parent)
    : QObject(parent), m_componentName(componentName), m_manager(manager)
{
}

void ComponentOverride::setColorOverride(const QString& atomProperty, const QColor& color) {
    m_overrides[atomProperty] = color;
    emit overridesChanged();
}

void ComponentOverride::setSizeOverride(const QString& atomProperty, int size) {
    m_overrides[atomProperty] = size;
    emit overridesChanged();
}

void ComponentOverride::clearOverride(const QString& property) {
    if (m_overrides.remove(property) > 0) {
        emit overridesChanged();
    }
}

void ComponentOverride::clearAllOverrides() {
    if (!m_overrides.isEmpty()) {
        m_overrides.clear();
        emit overridesChanged();
    }
}

bool ComponentOverride::hasOverride(const QString& property) const {
    return m_overrides.contains(property);
}

QVariant ComponentOverride::getOverride(const QString& property) const {
    return m_overrides.value(property);
}

QColor ComponentOverride::getColor(const QString& atomProperty) const {
    if (hasOverride(atomProperty)) {
        return getOverride(atomProperty).value<QColor>();
    }
    // Fallback sur l'atome global
    return m_manager->color()->property(atomProperty.toLatin1().constData()).value<QColor>();
}

int ComponentOverride::getSize(const QString& atomProperty) const {
    if (hasOverride(atomProperty)) {
        return getOverride(atomProperty).toInt();
    }
    // Fallback sur les molécules avec scale
    // Cette partie dépend de votre logique de fallback
    return 0; // À implémenter selon vos besoins
}

void ComponentOverride::loadFromJson(const QJsonObject& json) {
    m_overrides.clear();
    for (auto it = json.constBegin(); it != json.constEnd(); ++it) {
        QString key = it.key();
        QJsonValue val = it.value();
        
        if (val.isString()) {
            // Probablement une couleur
            m_overrides[key] = QColor(val.toString());
        } else if (val.isDouble()) {
            m_overrides[key] = val.toInt();
        }
    }
    emit overridesChanged();
}

QJsonObject ComponentOverride::toJson() const {
    QJsonObject json;
    for (auto it = m_overrides.constBegin(); it != m_overrides.constEnd(); ++it) {
        QVariant val = it.value();
        if (val.canConvert<QColor>()) {
            json[it.key()] = val.value<QColor>().name();
        } else if (val.canConvert<int>()) {
            json[it.key()] = val.toInt();
        }
    }
    return json;
}

// ===== NumberFieldOverride =====
NumberFieldOverride::NumberFieldOverride(ThemeManager* manager, QObject* parent)
    : ComponentOverride("NumberField", manager, parent)
{
}

QColor NumberFieldOverride::background() const {
    return getColor("bgPrimary");
}

void NumberFieldOverride::setBackground(const QColor& color) {
    setColorOverride("bgPrimary", color);
}

QColor NumberFieldOverride::backgroundHover() const {
    return getColor("bgSecondary");
}

void NumberFieldOverride::setBackgroundHover(const QColor& color) {
    setColorOverride("bgSecondary", color);
}

QColor NumberFieldOverride::borderColor() const {
    return getColor("borderPrimary");
}

void NumberFieldOverride::setBorderColor(const QColor& color) {
    setColorOverride("borderPrimary", color);
}

int NumberFieldOverride::borderWidth() const {
    if (hasOverride("borderWidth")) return getOverride("borderWidth").toInt();
    return 1; // Default
}

void NumberFieldOverride::setBorderWidth(int width) {
    setSizeOverride("borderWidth", width);
}

QColor NumberFieldOverride::textColor() const {
    return getColor("textPrimary");
}

void NumberFieldOverride::setTextColor(const QColor& color) {
    setColorOverride("textPrimary", color);
}

int NumberFieldOverride::textSize() const {
    if (hasOverride("textSize")) return getOverride("textSize").toInt();
    return 13; // Default
}

void NumberFieldOverride::setTextSize(int size) {
    setSizeOverride("textSize", size);
}

int NumberFieldOverride::textWeight() const {
    if (hasOverride("textWeight")) return getOverride("textWeight").toInt();
    return 400; // Normal
}

void NumberFieldOverride::setTextWeight(int weight) {
    setSizeOverride("textWeight", weight);
}

// ===== MenuBarOverride =====
MenuBarOverride::MenuBarOverride(ThemeManager* manager, QObject* parent)
    : ComponentOverride("MenuBar", manager, parent)
{
}

QColor MenuBarOverride::background() const {
    return getColor("surfPrimary");
}

void MenuBarOverride::setBackground(const QColor& color) {
    setColorOverride("surfPrimary", color);
}

QColor MenuBarOverride::hoverBackground() const {
    return getColor("surfHover");
}

void MenuBarOverride::setHoverBackground(const QColor& color) {
    setColorOverride("surfHover", color);
}

int MenuBarOverride::height() const {
    if (hasOverride("height")) return getOverride("height").toInt();
    return 40;
}

void MenuBarOverride::setHeight(int h) {
    setSizeOverride("height", h);
}

// ===== PreferencesWindowOverride =====
PreferencesWindowOverride::PreferencesWindowOverride(ThemeManager* manager, QObject* parent)
    : ComponentOverride("PreferencesWindow", manager, parent)
{
}

QColor PreferencesWindowOverride::sidebarBackground() const {
    return getColor("bgSecondary");
}

void PreferencesWindowOverride::setSidebarBackground(const QColor& color) {
    setColorOverride("bgSecondary", color);
}

QColor PreferencesWindowOverride::contentBackground() const {
    return getColor("bgPrimary");
}

void PreferencesWindowOverride::setContentBackground(const QColor& color) {
    setColorOverride("bgPrimary", color);
}

int PreferencesWindowOverride::sidebarWidth() const {
    if (hasOverride("sidebarWidth")) return getOverride("sidebarWidth").toInt();
    return 200;
}

void PreferencesWindowOverride::setSidebarWidth(int width) {
    setSizeOverride("sidebarWidth", width);
}