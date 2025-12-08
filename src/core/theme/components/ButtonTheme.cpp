#include "ButtonTheme.h"
#include "core/ThemeManager.h"

ButtonTheme::ButtonTheme(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_minWidth = new SizeValue(80, manager, this);
    m_minHeight = new SizeValue(32, manager, this);
    
    connect(m_minWidth, &SizeValue::changed, this, &ButtonTheme::changed);
    connect(m_minHeight, &SizeValue::changed, this, &ButtonTheme::changed);
}

void ButtonTheme::loadFromJson(const QJsonObject& json) {
    if (json.contains("minWidth")) m_minWidth->loadFromJson(json["minWidth"].toInt());
    if (json.contains("minHeight")) m_minHeight->loadFromJson(json["minHeight"].toInt());
}

QJsonObject ButtonTheme::toJson() const {
    QJsonObject json;
    json["minWidth"] = m_minWidth->toJson();
    json["minHeight"] = m_minHeight->toJson();
    return json;
}

void ButtonTheme::copyFrom(const ButtonTheme* other) {
    m_minWidth->copyFrom(other->m_minWidth);
    m_minHeight->copyFrom(other->m_minHeight);
}