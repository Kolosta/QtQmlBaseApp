#include "ThemeBorder.h"
#include "core/ThemeManager.h"

// === BorderWidth ===
BorderWidth::BorderWidth(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_thin = new SizeValue(1, manager, this);
    m_md = new SizeValue(2, manager, this);
    m_thick = new SizeValue(3, manager, this);
    
    connect(m_thin, &SizeValue::changed, this, &BorderWidth::changed);
    connect(m_md, &SizeValue::changed, this, &BorderWidth::changed);
    connect(m_thick, &SizeValue::changed, this, &BorderWidth::changed);
}

void BorderWidth::loadFromJson(const QJsonObject& json) {
    if (json.contains("thin")) m_thin->loadFromJson(json["thin"].toInt());
    if (json.contains("md")) m_md->loadFromJson(json["md"].toInt());
    if (json.contains("thick")) m_thick->loadFromJson(json["thick"].toInt());
}

QJsonObject BorderWidth::toJson() const {
    QJsonObject json;
    json["thin"] = m_thin->toJson();
    json["md"] = m_md->toJson();
    json["thick"] = m_thick->toJson();
    return json;
}

void BorderWidth::copyFrom(const BorderWidth* other) {
    m_thin->copyFrom(other->m_thin);
    m_md->copyFrom(other->m_md);
    m_thick->copyFrom(other->m_thick);
}

// === BorderRadius ===
BorderRadius::BorderRadius(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_xs = new SizeValue(2, manager, this);
    m_sm = new SizeValue(4, manager, this);
    m_md = new SizeValue(8, manager, this);
    m_lg = new SizeValue(16, manager, this);
    m_full = new SizeValue(9999, manager, this);
    
    connect(m_xs, &SizeValue::changed, this, &BorderRadius::changed);
    connect(m_sm, &SizeValue::changed, this, &BorderRadius::changed);
    connect(m_md, &SizeValue::changed, this, &BorderRadius::changed);
    connect(m_lg, &SizeValue::changed, this, &BorderRadius::changed);
    connect(m_full, &SizeValue::changed, this, &BorderRadius::changed);
}

void BorderRadius::loadFromJson(const QJsonObject& json) {
    if (json.contains("xs")) m_xs->loadFromJson(json["xs"].toInt());
    if (json.contains("sm")) m_sm->loadFromJson(json["sm"].toInt());
    if (json.contains("md")) m_md->loadFromJson(json["md"].toInt());
    if (json.contains("lg")) m_lg->loadFromJson(json["lg"].toInt());
    if (json.contains("full")) m_full->loadFromJson(json["full"].toInt());
}

QJsonObject BorderRadius::toJson() const {
    QJsonObject json;
    json["xs"] = m_xs->toJson();
    json["sm"] = m_sm->toJson();
    json["md"] = m_md->toJson();
    json["lg"] = m_lg->toJson();
    json["full"] = m_full->toJson();
    return json;
}

void BorderRadius::copyFrom(const BorderRadius* other) {
    m_xs->copyFrom(other->m_xs);
    m_sm->copyFrom(other->m_sm);
    m_md->copyFrom(other->m_md);
    m_lg->copyFrom(other->m_lg);
    m_full->copyFrom(other->m_full);
}

// === ThemeBorder ===
ThemeBorder::ThemeBorder(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_width = new BorderWidth(manager, this);
    m_radius = new BorderRadius(manager, this);
    
    connect(m_width, &BorderWidth::changed, this, &ThemeBorder::changed);
    connect(m_radius, &BorderRadius::changed, this, &ThemeBorder::changed);
}

void ThemeBorder::loadFromJson(const QJsonObject& json) {
    if (json.contains("width")) m_width->loadFromJson(json["width"].toObject());
    if (json.contains("radius")) m_radius->loadFromJson(json["radius"].toObject());
}

QJsonObject ThemeBorder::toJson() const {
    QJsonObject json;
    json["width"] = m_width->toJson();
    json["radius"] = m_radius->toJson();
    return json;
}

void ThemeBorder::copyFrom(const ThemeBorder* other) {
    m_width->copyFrom(other->m_width);
    m_radius->copyFrom(other->m_radius);
}