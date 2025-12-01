#include "PreferencesManager.h"

PreferencesManager::PreferencesManager(QObject *parent)
    : QObject(parent)
    , m_settings(new QSettings("YourCompany", "QtQmlBaseApp", this))
    , m_language("English")
{
    loadDefaults();
    loadPreferences();
}

PreferencesManager::~PreferencesManager()
{
    savePreferences();
}

void PreferencesManager::loadDefaults()
{
    // Define default values for all preferences
    m_defaults["general/language"] = "English";
    m_defaults["general/autosave"] = true;
    m_defaults["general/autosaveInterval"] = 5;
    // Add more defaults as needed
}

void PreferencesManager::loadPreferences()
{
    //Log loading preferences
    qDebug() << "Loading preferences";
    m_settings->beginGroup("preferences");
    QStringList keys = m_settings->allKeys();
    
    for (const QString &key : keys) {
        m_modifiedKeys[key] = m_settings->value(key);
    }
    
    m_settings->endGroup();
    
    // Load language
    m_language = getPreference("general", "language", "English").toString();
}

void PreferencesManager::savePreferences()
{
    //Log saving preferences
    qDebug() << "Saving modified preferences";
    m_settings->beginGroup("preferences");
    m_settings->remove(""); // Clear all
    
    for (auto it = m_modifiedKeys.constBegin(); it != m_modifiedKeys.constEnd(); ++it) {
        m_settings->setValue(it.key(), it.value());
    }
    
    m_settings->endGroup();
    m_settings->sync();
}

void PreferencesManager::setLanguage(const QString &language)
{
    if (m_language != language) {
        m_language = language;
        setPreference("general", "language", language);
        emit languageChanged();
    }
}

QString PreferencesManager::getKey(const QString &category, const QString &key) const
{
    //Log key construction
    qDebug() << "Constructing key for category: " << category << " and key: " << key;
    return QString("%1/%2").arg(category, key);
}

QVariant PreferencesManager::getPreference(const QString &category, const QString &key, const QVariant &defaultValue) const
{
    //Log retrieval of preference
    qDebug() << "Retrieving preference: " << category << "/" << key;
    QString fullKey = getKey(category, key);
    
    if (m_modifiedKeys.contains(fullKey)) {
        return m_modifiedKeys[fullKey];
    }
    
    if (m_defaults.contains(fullKey)) {
        return m_defaults[fullKey];
    }
    
    return defaultValue;
}

void PreferencesManager::setPreference(const QString &category, const QString &key, const QVariant &value)
{
    //Log setting of preference
    qDebug() << "Setting preference: " << category << "/" << key << " to " << value;
    QString fullKey = getKey(category, key);
    m_modifiedKeys[fullKey] = value;
    savePreferences();
    emit preferenceChanged(category, key);
}

void PreferencesManager::resetPreference(const QString &category, const QString &key)
{
    QString fullKey = getKey(category, key);
    m_modifiedKeys.remove(fullKey);
    savePreferences();
    
    // Update language if it was reset
    if (category == "general" && key == "language") {
        m_language = m_defaults[fullKey].toString();
        emit languageChanged();
    }
    
    emit preferenceChanged(category, key);
}

void PreferencesManager::resetCategory(const QString &category)
{
    QStringList keysToRemove;
    QString prefix = category + "/";
    
    for (auto it = m_modifiedKeys.constBegin(); it != m_modifiedKeys.constEnd(); ++it) {
        if (it.key().startsWith(prefix)) {
            keysToRemove.append(it.key());
        }
    }
    
    for (const QString &key : keysToRemove) {
        m_modifiedKeys.remove(key);
    }
    
    savePreferences();
    
    // Reload language if general category was reset
    if (category == "general") {
        m_language = m_defaults["general/language"].toString();
        emit languageChanged();
    }
}

void PreferencesManager::resetAll()
{
    m_modifiedKeys.clear();
    savePreferences();
    
    m_language = m_defaults["general/language"].toString();
    emit languageChanged();
}

bool PreferencesManager::isPreferenceModified(const QString &category, const QString &key) const
{
    // Log if the preference has been modified from its default value
    qDebug() << "Checking if preference is modified: " << category << "/" << key;
    QString fullKey = getKey(category, key);
    return m_modifiedKeys.contains(fullKey);
}

QVariant PreferencesManager::getDefaultValue(const QString &category, const QString &key) const
{
    //Log retrieval of default value
    qDebug() << "Retrieving default value for: " << category << "/" << key;
    QString fullKey = getKey(category, key);
    return m_defaults.value(fullKey);
}