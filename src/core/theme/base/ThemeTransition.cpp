#include "ThemeTransition.h"
#include <QJsonObject>

// === TransitionDuration ===
void TransitionDuration::loadFromJson(const QJsonObject& json) {
    if (json.contains("fast")) m_fast = json["fast"].toInt();
    if (json.contains("md")) m_md = json["md"].toInt();
    if (json.contains("slow")) m_slow = json["slow"].toInt();
}

QJsonObject TransitionDuration::toJson() const {
    QJsonObject json;
    json["fast"] = m_fast;
    json["md"] = m_md;
    json["slow"] = m_slow;
    return json;
}

// === ThemeTransition ===
ThemeTransition::ThemeTransition(QObject* parent)
    : QObject(parent)
{
    m_duration = new TransitionDuration(this);
}

void ThemeTransition::loadFromJson(const QJsonObject& json) {
    if (json.contains("duration")) m_duration->loadFromJson(json["duration"].toObject());
}

QJsonObject ThemeTransition::toJson() const {
    QJsonObject json;
    json["duration"] = m_duration->toJson();
    return json;
}

void ThemeTransition::copyFrom(const ThemeTransition* other) {
    // TransitionDuration n'a pas de copyFrom car ce sont des constantes
    // Mais on peut les copier manuellement si nécessaire
}
