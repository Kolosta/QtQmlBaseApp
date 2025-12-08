#include "ThemeSize.h"
#include "core/ThemeManager.h"

// === IconSize ===
IconSize::IconSize(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_sm = new SizeValue(16, manager, this);
    m_md = new SizeValue(24, manager, this);
    m_lg = new SizeValue(32, manager, this);
    
    connect(m_sm, &SizeValue::changed, this, &IconSize::changed);
    connect(m_md, &SizeValue::changed, this, &IconSize::changed);
    connect(m_lg, &SizeValue::changed, this, &IconSize::changed);
}

void IconSize::loadFromJson(const QJsonObject& json) {
    if (json.contains("sm")) m_sm->loadFromJson(json["sm"].toInt());
    if (json.contains("md")) m_md->loadFromJson(json["md"].toInt());
    if (json.contains("lg")) m_lg->loadFromJson(json["lg"].toInt());
}

QJsonObject IconSize::toJson() const {
    QJsonObject json;
    json["sm"] = m_sm->toJson();
    json["md"] = m_md->toJson();
    json["lg"] = m_lg->toJson();
    return json;
}

void IconSize::copyFrom(const IconSize* other) {
    m_sm->copyFrom(other->m_sm);
    m_md->copyFrom(other->m_md);
    m_lg->copyFrom(other->m_lg);
}

// === ThemeSize ===
ThemeSize::ThemeSize(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_icon = new IconSize(manager, this);
    connect(m_icon, &IconSize::changed, this, &ThemeSize::changed);
}

void ThemeSize::loadFromJson(const QJsonObject& json) {
    if (json.contains("icon")) m_icon->loadFromJson(json["icon"].toObject());
}

QJsonObject ThemeSize::toJson() const {
    QJsonObject json;
    json["icon"] = m_icon->toJson();
    return json;
}

void ThemeSize::copyFrom(const ThemeSize* other) {
    m_icon->copyFrom(other->m_icon);
}