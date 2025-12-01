#include "SettingsManager.h"

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent)
    , m_settings(new QSettings("YourCompany", "QtQmlBaseApp", this))
    , m_theme("dark")
    , m_language("English")
{
    load();
}

SettingsManager::~SettingsManager()
{
    save();
}

QString SettingsManager::theme() const
{
    return m_theme;
}

void SettingsManager::setTheme(const QString &theme)
{
    if (m_theme != theme) {
        m_theme = theme;
        emit themeChanged();
        save();
    }
}

QString SettingsManager::language() const
{
    return m_language;
}

void SettingsManager::setLanguage(const QString &language)
{
    if (m_language != language) {
        m_language = language;
        emit languageChanged();
        save();
    }
}

void SettingsManager::save()
{
    m_settings->setValue("theme", m_theme);
    m_settings->setValue("language", m_language);
    m_settings->sync();
}

void SettingsManager::load()
{
    m_theme = m_settings->value("theme", "dark").toString();
    m_language = m_settings->value("language", "English").toString();
    
    emit themeChanged();
    emit languageChanged();
}