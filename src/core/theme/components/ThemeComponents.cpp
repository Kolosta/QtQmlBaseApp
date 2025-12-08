#include "ThemeComponents.h"
#include <QJsonObject>
#include <QJsonValue>

ThemeComponents::ThemeComponents(ThemeManager* manager, QObject* parent)
    : QObject(parent)
{
    m_menuBar = new MenuBarTheme(manager, this);
    m_button = new ButtonTheme(manager, this);
    m_preferencesWindow = new PreferencesWindowTheme(manager, this);
    
    connect(m_menuBar, &MenuBarTheme::changed, this, &ThemeComponents::changed);
    connect(m_button, &ButtonTheme::changed, this, &ThemeComponents::changed);
    connect(m_preferencesWindow, &PreferencesWindowTheme::changed, this, &ThemeComponents::changed);
}

void ThemeComponents::loadFromJson(const QJsonObject& json) {
    if (json.contains("menuBar")) m_menuBar->loadFromJson(json["menuBar"].toObject());
    if (json.contains("button")) m_button->loadFromJson(json["button"].toObject());
    if (json.contains("preferencesWindow")) m_preferencesWindow->loadFromJson(json["preferencesWindow"].toObject());
}

QJsonObject ThemeComponents::toJson() const {
    QJsonObject json;
    json["menuBar"] = m_menuBar->toJson();
    json["button"] = m_button->toJson();
    json["preferencesWindow"] = m_preferencesWindow->toJson();
    return json;
}

void ThemeComponents::copyFrom(const ThemeComponents* other) {
    m_menuBar->copyFrom(other->m_menuBar);
    m_button->copyFrom(other->m_button);
    m_preferencesWindow->copyFrom(other->m_preferencesWindow);
}