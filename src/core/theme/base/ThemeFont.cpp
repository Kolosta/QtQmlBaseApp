#include "ThemeFont.h"
#include "core/ThemeManager.h"

// === FontFamily ===
void FontFamily::loadFromJson(const QJsonObject& json) {
    if (json.contains("primary")) m_primary = json["primary"].toString();
    if (json.contains("secondary")) m_secondary = json["secondary"].toString();
    if (json.contains("mono")) m_mono = json["mono"].toString();
    emit changed();
}

QJsonObject FontFamily::toJson() const {
    QJsonObject json;
    json["primary"] = m_primary;
    json["secondary"] = m_secondary;
    json["mono"] = m_mono;
    return json;
}

void FontFamily::copyFrom(const FontFamily* other) {
    m_primary = other->m_primary;
    m_secondary = other->m_secondary;
    m_mono = other->m_mono;
    emit changed();
}

// === FontSize::TextSizes ===
// FontSize::TextSizes::TextSizes(ThemeManager* manager, QObject* parent)
//     : QObject(parent)
// {
//     m_xs = new SizeValue(11, manager, this);
//     m_sm = new SizeValue(13, manager, this);
//     m_md = new SizeValue(15, manager, this);
//     m_lg = new SizeValue(18, manager, this);
    
//     connect(m_xs, &SizeValue::changed, this, &TextSizes::changed);
//     connect(m_sm, &SizeValue::changed, this, &TextSizes::changed);
//     connect(m_md, &SizeValue::changed, this, &TextSizes::changed);
//     connect(m_lg, &SizeValue::changed, this, &TextSizes::changed);
// }

// void FontSize::TextSizes::loadFromJson(const QJsonObject& json) {
//     if (json.contains("xs")) m_xs->loadFromJson(json["xs"].toInt());
//     if (json.contains("sm")) m_sm->loadFromJson(json["sm"].toInt());
//     if (json.contains("md")) m_md->loadFromJson(json["md"].toInt());
//     if (json.contains("lg")) m_lg->loadFromJson(json["lg"].toInt());
// }

// QJsonObject FontSize::TextSizes::toJson() const {
//     QJsonObject json;
//     json["xs"] = m_xs->toJson();
//     json["sm"] = m_sm->toJson();
//     json["md"] = m_md->toJson();
//     json["lg"] = m_lg->toJson();
//     return json;
// }

// void FontSize::TextSizes::copyFrom(const TextSizes* other) {
//     m_xs->copyFrom(other->m_xs);
//     m_sm->copyFrom(other->m_sm);
//     m_md->copyFrom(other->m_md);
//     m_lg->copyFrom(other->m_lg);
// }

// === TextSizes ===
TextSizes::TextSizes(ThemeManager* manager, QObject* parent) // Changé
    : QObject(parent)
{
    m_xs = new SizeValue(11, manager, this);
    m_sm = new SizeValue(13, manager, this);
    m_md = new SizeValue(15, manager, this);
    m_lg = new SizeValue(18, manager, this);
    
    connect(m_xs, &SizeValue::changed, this, &TextSizes::changed);
    connect(m_sm, &SizeValue::changed, this, &TextSizes::changed);
    connect(m_md, &SizeValue::changed, this, &TextSizes::changed);
    connect(m_lg, &SizeValue::changed, this, &TextSizes::changed);
}

void TextSizes::loadFromJson(const QJsonObject& json) { // Changé
    if (json.contains("xs")) m_xs->loadFromJson(json["xs"].toInt());
    if (json.contains("sm")) m_sm->loadFromJson(json["sm"].toInt());
    if (json.contains("md")) m_md->loadFromJson(json["md"].toInt());
    if (json.contains("lg")) m_lg->loadFromJson(json["lg"].toInt());
}

QJsonObject TextSizes::toJson() const { // Changé
    QJsonObject json;
    json["xs"] = m_xs->toJson();
    json["sm"] = m_sm->toJson();
    json["md"] = m_md->toJson();
    json["lg"] = m_lg->toJson();
    return json;
}

void TextSizes::copyFrom(const TextSizes* other) { // Changé
    m_xs->copyFrom(other->m_xs);
    m_sm->copyFrom(other->m_sm);
    m_md->copyFrom(other->m_md);
    m_lg->copyFrom(other->m_lg);
}

// === FontSize ===
FontSize::FontSize(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_text = new TextSizes(manager, this);
    m_heading1 = new SizeValue(32, manager, this);
    m_heading2 = new SizeValue(24, manager, this);
    m_heading3 = new SizeValue(20, manager, this);
    
    connect(m_text, &TextSizes::changed, this, &FontSize::changed);
    connect(m_heading1, &SizeValue::changed, this, &FontSize::changed);
    connect(m_heading2, &SizeValue::changed, this, &FontSize::changed);
    connect(m_heading3, &SizeValue::changed, this, &FontSize::changed);
}

void FontSize::loadFromJson(const QJsonObject& json) {
    if (json.contains("text")) m_text->loadFromJson(json["text"].toObject());
    if (json.contains("heading1")) m_heading1->loadFromJson(json["heading1"].toInt());
    if (json.contains("heading2")) m_heading2->loadFromJson(json["heading2"].toInt());
    if (json.contains("heading3")) m_heading3->loadFromJson(json["heading3"].toInt());
}

QJsonObject FontSize::toJson() const {
    QJsonObject json;
    json["text"] = m_text->toJson();
    json["heading1"] = m_heading1->toJson();
    json["heading2"] = m_heading2->toJson();
    json["heading3"] = m_heading3->toJson();
    return json;
}

void FontSize::copyFrom(const FontSize* other) {
    m_text->copyFrom(other->m_text);
    m_heading1->copyFrom(other->m_heading1);
    m_heading2->copyFrom(other->m_heading2);
    m_heading3->copyFrom(other->m_heading3);
}

// === FontWeight ===
void FontWeight::loadFromJson(const QJsonObject& json) {
    if (json.contains("light")) m_light = json["light"].toInt();
    if (json.contains("regular")) m_regular = json["regular"].toInt();
    if (json.contains("medium")) m_medium = json["medium"].toInt();
    if (json.contains("bold")) m_bold = json["bold"].toInt();
}

QJsonObject FontWeight::toJson() const {
    QJsonObject json;
    json["light"] = m_light;
    json["regular"] = m_regular;
    json["medium"] = m_medium;
    json["bold"] = m_bold;
    return json;
}

// === ThemeFont ===
ThemeFont::ThemeFont(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_family = new FontFamily(this);
    m_size = new FontSize(manager, this);
    m_weight = new FontWeight(this);
    
    connect(m_family, &FontFamily::changed, this, &ThemeFont::changed);
    connect(m_size, &FontSize::changed, this, &ThemeFont::changed);
}

void ThemeFont::loadFromJson(const QJsonObject& json) {
    if (json.contains("family")) m_family->loadFromJson(json["family"].toObject());
    if (json.contains("size")) m_size->loadFromJson(json["size"].toObject());
    if (json.contains("weight")) m_weight->loadFromJson(json["weight"].toObject());
}

QJsonObject ThemeFont::toJson() const {
    QJsonObject json;
    json["family"] = m_family->toJson();
    json["size"] = m_size->toJson();
    json["weight"] = m_weight->toJson();
    return json;
}

void ThemeFont::copyFrom(const ThemeFont* other) {
    m_family->copyFrom(other->m_family);
    m_size->copyFrom(other->m_size);
}