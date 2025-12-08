#include "MenuBarTheme.h"
#include "core/ThemeManager.h"

MenuBarTheme::MenuBarTheme(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_height = new SizeValue(40, manager, this);
    connect(m_height, &SizeValue::changed, this, &MenuBarTheme::changed);
}

void MenuBarTheme::loadFromJson(const QJsonObject& json) {
    if (json.contains("height")) m_height->loadFromJson(json["height"].toInt());
}

QJsonObject MenuBarTheme::toJson() const {
    QJsonObject json;
    json["height"] = m_height->toJson();
    return json;
}

void MenuBarTheme::copyFrom(const MenuBarTheme* other) {
    m_height->copyFrom(other->m_height);
}