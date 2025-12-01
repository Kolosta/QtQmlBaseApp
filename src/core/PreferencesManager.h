#ifndef PREFERENCESMANAGER_H
#define PREFERENCESMANAGER_H

#include <QObject>
#include <QSettings>
#include <QVariant>
#include <QMap>

class PreferencesManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)

public:
    explicit PreferencesManager(QObject *parent = nullptr);
    ~PreferencesManager();

    QString language() const { return m_language; }
    void setLanguage(const QString &language);
    
    Q_INVOKABLE QVariant getPreference(const QString &category, const QString &key, const QVariant &defaultValue = QVariant()) const;
    Q_INVOKABLE void setPreference(const QString &category, const QString &key, const QVariant &value);
    Q_INVOKABLE void resetPreference(const QString &category, const QString &key);
    Q_INVOKABLE void resetCategory(const QString &category);
    Q_INVOKABLE void resetAll();
    Q_INVOKABLE bool isPreferenceModified(const QString &category, const QString &key) const;
    Q_INVOKABLE QVariant getDefaultValue(const QString &category, const QString &key) const;

signals:
    void languageChanged();
    void preferenceChanged(const QString &category, const QString &key);

private:
    void loadDefaults();
    void loadPreferences();
    void savePreferences();
    QString getKey(const QString &category, const QString &key) const;
    
    QSettings *m_settings;
    QString m_language;
    QMap<QString, QVariant> m_defaults;
    QMap<QString, QVariant> m_modifiedKeys;
};

#endif // PREFERENCESMANAGER_H