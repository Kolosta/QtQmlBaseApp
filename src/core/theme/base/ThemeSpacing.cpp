#include "ThemeSpacing.h"
#include "core/ThemeManager.h"

// === MarginSpacing ===
MarginSpacing::MarginSpacing(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_none = new SizeValue(0, manager, this);
    m_xxxs = new SizeValue(2, manager, this);
    m_xxs = new SizeValue(4, manager, this);
    m_xs = new SizeValue(6, manager, this);
    m_sm = new SizeValue(8, manager, this);
    m_md = new SizeValue(12, manager, this);
    m_lg = new SizeValue(16, manager, this);
    m_xl = new SizeValue(24, manager, this);
    m_xxl = new SizeValue(32, manager, this);
    m_xxxl = new SizeValue(48, manager, this);
    
    connect(m_none, &SizeValue::changed, this, &MarginSpacing::changed);
    connect(m_xxxs, &SizeValue::changed, this, &MarginSpacing::changed);
    connect(m_xxs, &SizeValue::changed, this, &MarginSpacing::changed);
    connect(m_xs, &SizeValue::changed, this, &MarginSpacing::changed);
    connect(m_sm, &SizeValue::changed, this, &MarginSpacing::changed);
    connect(m_md, &SizeValue::changed, this, &MarginSpacing::changed);
    connect(m_lg, &SizeValue::changed, this, &MarginSpacing::changed);
    connect(m_xl, &SizeValue::changed, this, &MarginSpacing::changed);
    connect(m_xxl, &SizeValue::changed, this, &MarginSpacing::changed);
    connect(m_xxxl, &SizeValue::changed, this, &MarginSpacing::changed);
}

void MarginSpacing::loadFromJson(const QJsonObject& json) {
    if (json.contains("none")) m_none->loadFromJson(json["none"].toInt());
    if (json.contains("xxxs")) m_xxxs->loadFromJson(json["xxxs"].toInt());
    if (json.contains("xxs")) m_xxs->loadFromJson(json["xxs"].toInt());
    if (json.contains("xs")) m_xs->loadFromJson(json["xs"].toInt());
    if (json.contains("sm")) m_sm->loadFromJson(json["sm"].toInt());
    if (json.contains("md")) m_md->loadFromJson(json["md"].toInt());
    if (json.contains("lg")) m_lg->loadFromJson(json["lg"].toInt());
    if (json.contains("xl")) m_xl->loadFromJson(json["xl"].toInt());
    if (json.contains("xxl")) m_xxl->loadFromJson(json["xxl"].toInt());
    if (json.contains("xxxl")) m_xxxl->loadFromJson(json["xxxl"].toInt());
}

QJsonObject MarginSpacing::toJson() const {
    QJsonObject json;
    json["none"] = m_none->toJson();
    json["xxxs"] = m_xxxs->toJson();
    json["xxs"] = m_xxs->toJson();
    json["xs"] = m_xs->toJson();
    json["sm"] = m_sm->toJson();
    json["md"] = m_md->toJson();
    json["lg"] = m_lg->toJson();
    json["xl"] = m_xl->toJson();
    json["xxl"] = m_xxl->toJson();
    json["xxxl"] = m_xxxl->toJson();
    return json;
}

void MarginSpacing::copyFrom(const MarginSpacing* other) {
    m_none->copyFrom(other->m_none);
    m_xxxs->copyFrom(other->m_xxxs);
    m_xxs->copyFrom(other->m_xxs);
    m_xs->copyFrom(other->m_xs);
    m_sm->copyFrom(other->m_sm);
    m_md->copyFrom(other->m_md);
    m_lg->copyFrom(other->m_lg);
    m_xl->copyFrom(other->m_xl);
    m_xxl->copyFrom(other->m_xxl);
    m_xxxl->copyFrom(other->m_xxxl);
}

// === PaddingSpacing === (Identique à MarginSpacing)
PaddingSpacing::PaddingSpacing(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_none = new SizeValue(0, manager, this);
    m_xxxs = new SizeValue(2, manager, this);
    m_xxs = new SizeValue(4, manager, this);
    m_xs = new SizeValue(6, manager, this);
    m_sm = new SizeValue(8, manager, this);
    m_md = new SizeValue(12, manager, this);
    m_lg = new SizeValue(16, manager, this);
    m_xl = new SizeValue(24, manager, this);
    m_xxl = new SizeValue(32, manager, this);
    m_xxxl = new SizeValue(48, manager, this);
    
    connect(m_none, &SizeValue::changed, this, &PaddingSpacing::changed);
    connect(m_xxxs, &SizeValue::changed, this, &PaddingSpacing::changed);
    connect(m_xxs, &SizeValue::changed, this, &PaddingSpacing::changed);
    connect(m_xs, &SizeValue::changed, this, &PaddingSpacing::changed);
    connect(m_sm, &SizeValue::changed, this, &PaddingSpacing::changed);
    connect(m_md, &SizeValue::changed, this, &PaddingSpacing::changed);
    connect(m_lg, &SizeValue::changed, this, &PaddingSpacing::changed);
    connect(m_xl, &SizeValue::changed, this, &PaddingSpacing::changed);
    connect(m_xxl, &SizeValue::changed, this, &PaddingSpacing::changed);
    connect(m_xxxl, &SizeValue::changed, this, &PaddingSpacing::changed);
}

void PaddingSpacing::loadFromJson(const QJsonObject& json) {
    if (json.contains("none")) m_none->loadFromJson(json["none"].toInt());
    if (json.contains("xxxs")) m_xxxs->loadFromJson(json["xxxs"].toInt());
    if (json.contains("xxs")) m_xxs->loadFromJson(json["xxs"].toInt());
    if (json.contains("xs")) m_xs->loadFromJson(json["xs"].toInt());
    if (json.contains("sm")) m_sm->loadFromJson(json["sm"].toInt());
    if (json.contains("md")) m_md->loadFromJson(json["md"].toInt());
    if (json.contains("lg")) m_lg->loadFromJson(json["lg"].toInt());
    if (json.contains("xl")) m_xl->loadFromJson(json["xl"].toInt());
    if (json.contains("xxl")) m_xxl->loadFromJson(json["xxl"].toInt());
    if (json.contains("xxxl")) m_xxxl->loadFromJson(json["xxxl"].toInt());
}

QJsonObject PaddingSpacing::toJson() const {
    QJsonObject json;
    json["none"] = m_none->toJson();
    json["xxxs"] = m_xxxs->toJson();
    json["xxs"] = m_xxs->toJson();
    json["xs"] = m_xs->toJson();
    json["sm"] = m_sm->toJson();
    json["md"] = m_md->toJson();
    json["lg"] = m_lg->toJson();
    json["xl"] = m_xl->toJson();
    json["xxl"] = m_xxl->toJson();
    json["xxxl"] = m_xxxl->toJson();
    return json;
}

void PaddingSpacing::copyFrom(const PaddingSpacing* other) {
    m_none->copyFrom(other->m_none);
    m_xxxs->copyFrom(other->m_xxxs);
    m_xxs->copyFrom(other->m_xxs);
    m_xs->copyFrom(other->m_xs);
    m_sm->copyFrom(other->m_sm);
    m_md->copyFrom(other->m_md);
    m_lg->copyFrom(other->m_lg);
    m_xl->copyFrom(other->m_xl);
    m_xxl->copyFrom(other->m_xxl);
    m_xxxl->copyFrom(other->m_xxxl);
}

// === GapSpacing ===
GapSpacing::GapSpacing(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_xs = new SizeValue(4, manager, this);
    m_sm = new SizeValue(8, manager, this);
    m_md = new SizeValue(12, manager, this);
    
    connect(m_xs, &SizeValue::changed, this, &GapSpacing::changed);
    connect(m_sm, &SizeValue::changed, this, &GapSpacing::changed);
    connect(m_md, &SizeValue::changed, this, &GapSpacing::changed);
}

void GapSpacing::loadFromJson(const QJsonObject& json) {
    if (json.contains("xs")) m_xs->loadFromJson(json["xs"].toInt());
    if (json.contains("sm")) m_sm->loadFromJson(json["sm"].toInt());
    if (json.contains("md")) m_md->loadFromJson(json["md"].toInt());
}

QJsonObject GapSpacing::toJson() const {
    QJsonObject json;
    json["xs"] = m_xs->toJson();
    json["sm"] = m_sm->toJson();
    json["md"] = m_md->toJson();
    return json;
}

void GapSpacing::copyFrom(const GapSpacing* other) {
    m_xs->copyFrom(other->m_xs);
    m_sm->copyFrom(other->m_sm);
    m_md->copyFrom(other->m_md);
}

// === ThemeSpacing ===
ThemeSpacing::ThemeSpacing(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_margin = new MarginSpacing(manager, this);
    m_padding = new PaddingSpacing(manager, this);
    m_gap = new GapSpacing(manager, this);
    
    connect(m_margin, &MarginSpacing::changed, this, &ThemeSpacing::changed);
    connect(m_padding, &PaddingSpacing::changed, this, &ThemeSpacing::changed);
    connect(m_gap, &GapSpacing::changed, this, &ThemeSpacing::changed);
}

void ThemeSpacing::loadFromJson(const QJsonObject& json) {
    if (json.contains("margin")) m_margin->loadFromJson(json["margin"].toObject());
    if (json.contains("padding")) m_padding->loadFromJson(json["padding"].toObject());
    if (json.contains("gap")) m_gap->loadFromJson(json["gap"].toObject());
}

QJsonObject ThemeSpacing::toJson() const {
    QJsonObject json;
    json["margin"] = m_margin->toJson();
    json["padding"] = m_padding->toJson();
    json["gap"] = m_gap->toJson();
    return json;
}

void ThemeSpacing::copyFrom(const ThemeSpacing* other) {
    m_margin->copyFrom(other->m_margin);
    m_padding->copyFrom(other->m_padding);
    m_gap->copyFrom(other->m_gap);
}