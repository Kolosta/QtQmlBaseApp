#include "ColorState.h"

void ColorState::loadFromJson(const QJsonObject& json) {
    if (json.contains("default")) m_default = QColor(json["default"].toString());
    if (json.contains("hover")) m_hover = QColor(json["hover"].toString());
    if (json.contains("active")) m_active = QColor(json["active"].toString());
    if (json.contains("disabled")) m_disabled = QColor(json["disabled"].toString());
    if (json.contains("pressed")) m_pressed = QColor(json["pressed"].toString());
    emit changed();
}

QJsonObject ColorState::toJson() const {
    QJsonObject json;
    json["default"] = m_default.name();
    if (m_hover.isValid()) json["hover"] = m_hover.name();
    if (m_active.isValid()) json["active"] = m_active.name();
    if (m_disabled.isValid()) json["disabled"] = m_disabled.name();
    if (m_pressed.isValid()) json["pressed"] = m_pressed.name();
    return json;
}

void ColorState::copyFrom(const ColorState* other) {
    m_default = other->m_default;
    m_hover = other->m_hover;
    m_active = other->m_active;
    m_disabled = other->m_disabled;
    m_pressed = other->m_pressed;
    emit changed();
}