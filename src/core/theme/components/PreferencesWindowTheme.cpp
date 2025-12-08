#include "PreferencesWindowTheme.h"
#include "core/ThemeManager.h"

PreferencesWindowTheme::PreferencesWindowTheme(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_sidebarWidth = new SizeValue(200, manager, this);
    connect(m_sidebarWidth, &SizeValue::changed, this, &PreferencesWindowTheme::changed);
}

void PreferencesWindowTheme::loadFromJson(const QJsonObject& json) {
    if (json.contains("sidebarWidth")) m_sidebarWidth->loadFromJson(json["sidebarWidth"].toInt());
}

QJsonObject PreferencesWindowTheme::toJson() const {
    QJsonObject json;
    json["sidebarWidth"] = m_sidebarWidth->toJson();
    return json;
}

void PreferencesWindowTheme::copyFrom(const PreferencesWindowTheme* other) {
    m_sidebarWidth->copyFrom(other->m_sidebarWidth);
}