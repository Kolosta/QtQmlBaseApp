#include "SimpleColorState.h"
#include <QJsonObject>

void SimpleColorState::loadFromJson(const QJsonObject& json) {
    if (json.contains("default")) m_default = QColor(json["default"].toString());
    // else if (json.isString()) m_default = QColor(json.toString()); // Support direct
    emit changed();
}

QJsonObject SimpleColorState::toJson() const {
    QJsonObject json;
    json["default"] = m_default.name();
    return json;
}

void SimpleColorState::copyFrom(const SimpleColorState* other) {
    m_default = other->m_default;
    emit changed();
}