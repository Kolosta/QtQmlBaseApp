#include "ThemeManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QDir>
#include <QDebug>
#include <QStandardPaths>
#include <QDirIterator>

ThemeManager::ThemeManager(QObject *parent)
    : QObject(parent)
    , m_currentTheme("")
{
    loadDefaultTheme();
    discoverThemes();
    
    QSettings settings;
    QString savedTheme = settings.value("theme/current", "dark").toString();
    setCurrentTheme(savedTheme);
}

void ThemeManager::loadDefaultTheme()
{
    const QString path = QStringLiteral(":/resources/themes/default.json");
    
    QFile file(path);
    
    if (!file.exists()) {
        qWarning() << "Default theme file does not exist at path:" << path;
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open default theme file:" << file.errorString();
        return;
    }

    QByteArray data = file.readAll();
    file.close();
    
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return;
    }
    
    if (!doc.isObject()) {
        qWarning() << "Default theme JSON is not an object";
        return;
    }
    
    m_defaultTheme = doc.object().toVariantMap();
}

void ThemeManager::discoverThemes()
{
    m_availableThemes.clear();
    
    QStringList themeNames = {
        "dark", "light", "grey", "muted_green", 
        "blue", "sepia", "snow", "arctic"
    };
    
    for (const QString &themeName : themeNames) {
        QString path = QString(":/resources/themes/%1.json").arg(themeName);
        if (QFile::exists(path)) {
            m_availableThemes.append(themeName);
        }
    }
    
    QString userThemesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/themes";
    QDir userThemesDir(userThemesPath);
    
    if (userThemesDir.exists()) {
        QStringList filters;
        filters << "*.json";
        QFileInfoList files = userThemesDir.entryInfoList(filters, QDir::Files);
        
        for (const QFileInfo &fileInfo : files) {
            QString themeName = fileInfo.baseName();
            if (!m_availableThemes.contains(themeName)) {
                m_availableThemes.append(themeName);
            }
        }
    }
    
    emit availableThemesChanged();
}

void ThemeManager::setCurrentTheme(const QString &theme)
{
    if (m_currentTheme == theme)
        return;
    
    m_currentTheme = theme;
    loadTheme(theme);
    loadUserOverrides();
    
    m_effectiveTheme = mergeThemes(m_defaultTheme, m_currentThemeBase);
    m_effectiveTheme = mergeThemes(m_effectiveTheme, m_userOverrides);
    
    QSettings settings;
    settings.setValue("theme/current", theme);
    
    emit currentThemeChanged();
    emit themePropertiesChanged();
}

void ThemeManager::loadTheme(const QString &themeName)
{
    QString filePath = QString(":/resources/themes/%1.json").arg(themeName);
    QFile file(filePath);
    
    if (!file.exists()) {
        QString userThemesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/themes";
        filePath = QString("%1/%2.json").arg(userThemesPath, themeName);
        file.setFileName(filePath);
    }
    
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open theme file:" << filePath;
        m_currentThemeBase = QVariantMap();
        return;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    m_currentThemeBase = doc.object().toVariantMap();
    file.close();
}

void ThemeManager::loadUserOverrides()
{
    QSettings settings;
    settings.beginGroup(QString("theme/overrides/%1").arg(m_currentTheme));
    
    m_userOverrides.clear();
    QStringList keys = settings.allKeys();
    for (const QString &key : keys) {
        m_userOverrides[key] = settings.value(key);
    }
    
    settings.endGroup();
}

void ThemeManager::saveUserOverrides()
{
    QSettings settings;
    settings.beginGroup(QString("theme/overrides/%1").arg(m_currentTheme));
    
    settings.remove("");
    
    for (auto it = m_userOverrides.constBegin(); it != m_userOverrides.constEnd(); ++it) {
        settings.setValue(it.key(), it.value());
    }
    
    settings.endGroup();
    settings.sync();
}

QVariantMap ThemeManager::mergeThemes(const QVariantMap &base, const QVariantMap &override) const
{
    QVariantMap result = base;
    
    for (auto it = override.constBegin(); it != override.constEnd(); ++it) {
        result[it.key()] = it.value();
    }
    
    return result;
}

QColor ThemeManager::getColor(const QString &key) const
{
    QVariant value = m_effectiveTheme.value(key);
    if (value.type() == QVariant::String) {
        return QColor(value.toString());
    } else if (value.canConvert<QColor>()) {
        return value.value<QColor>();
    }
    return QColor("#000000");
}

int ThemeManager::getInt(const QString &key) const
{
    int result = m_effectiveTheme.value(key, 0).toInt();
    return result;
}

QVariantMap ThemeManager::getAllProperties() const
{
    return m_effectiveTheme;
}

QVariant ThemeManager::getProperty(const QString &key) const
{
    return m_effectiveTheme.value(key);
}

void ThemeManager::setProperty(const QString &key, const QVariant &value)
{
    // Obtenir la valeur originale du thème
    QVariant originalValue = m_currentThemeBase.value(key);
    if (!originalValue.isValid()) {
        originalValue = m_defaultTheme.value(key);
    }
    
    // Normaliser les valeurs pour la comparaison
    QVariant normalizedValue = normalizeValue(value);
    QVariant normalizedOriginal = normalizeValue(originalValue);
    
    // Si la valeur est identique à l'originale, supprimer l'override
    if (valuesAreEqual(normalizedValue, normalizedOriginal)) {
        m_userOverrides.remove(key);
    } else {
        // Sinon, ajouter/mettre à jour l'override
        m_userOverrides[key] = normalizedValue;
    }
    
    m_effectiveTheme[key] = normalizedValue;
    saveUserOverrides();
    emit themePropertiesChanged();
}

void ThemeManager::resetProperty(const QString &key)
{
    m_userOverrides.remove(key);
    
    QVariant baseValue = m_currentThemeBase.value(key);
    if (baseValue.isValid()) {
        m_effectiveTheme[key] = baseValue;
    } else {
        m_effectiveTheme[key] = m_defaultTheme.value(key);
    }
    
    saveUserOverrides();
    emit themePropertiesChanged();
}

void ThemeManager::resetAllProperties()
{
    m_userOverrides.clear();
    m_effectiveTheme = mergeThemes(m_defaultTheme, m_currentThemeBase);
    saveUserOverrides();
    emit themePropertiesChanged();
}

bool ThemeManager::isPropertyModified(const QString &key) const
{
    // Vérifier si la clé existe dans les overrides
    if (!m_userOverrides.contains(key)) {
        return false;
    }
    
    // Obtenir la valeur actuelle et la valeur originale
    QVariant currentValue = m_userOverrides.value(key);
    QVariant originalValue = m_currentThemeBase.value(key);
    if (!originalValue.isValid()) {
        originalValue = m_defaultTheme.value(key);
    }
    
    // Normaliser et comparer
    QVariant normalizedCurrent = normalizeValue(currentValue);
    QVariant normalizedOriginal = normalizeValue(originalValue);
    
    return !valuesAreEqual(normalizedCurrent, normalizedOriginal);
}

QVariant ThemeManager::getOriginalValue(const QString &key) const
{
    QVariant value = m_currentThemeBase.value(key);
    if (value.isValid()) {
        return value;
    }
    return m_defaultTheme.value(key);
}

QVariant ThemeManager::normalizeValue(const QVariant &value) const
{
    // Normaliser les couleurs en format #RRGGBB majuscule
    if (value.type() == QVariant::String) {
        QString str = value.toString();
        if (QColor::isValidColor(str)) {
            QColor color(str);
            return color.name(QColor::HexRgb).toUpper();
        }
    } else if (value.canConvert<QColor>()) {
        QColor color = value.value<QColor>();
        return color.name(QColor::HexRgb).toUpper();
    }
    
    return value;
}

bool ThemeManager::valuesAreEqual(const QVariant &v1, const QVariant &v2) const
{
    // Comparaison directe pour les types simples
    if (v1.type() == v2.type()) {
        return v1 == v2;
    }
    
    // Comparaison spéciale pour les couleurs
    if ((v1.type() == QVariant::String || v1.canConvert<QColor>()) &&
        (v2.type() == QVariant::String || v2.canConvert<QColor>())) {
        
        QString color1 = normalizeValue(v1).toString();
        QString color2 = normalizeValue(v2).toString();
        
        return color1.compare(color2, Qt::CaseInsensitive) == 0;
    }
    
    // Comparaison après conversion
    if (v1.canConvert(v2.type())) {
        QVariant converted = v1;
        converted.convert(v2.type());
        return converted == v2;
    }
    
    return false;
}

bool ThemeManager::importTheme(const QString &filePath)
{
    QString cleanPath = filePath;
    if (cleanPath.startsWith("file:///")) {
        cleanPath = cleanPath.mid(8);
    } else if (cleanPath.startsWith("file://")) {
        cleanPath = cleanPath.mid(7);
    }
    
    QFile file(cleanPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for import:" << cleanPath;
        return false;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    
    if (doc.isNull() || !doc.isObject()) {
        qWarning() << "Invalid theme file format";
        return false;
    }
    
    QFileInfo fileInfo(cleanPath);
    QString themeName = fileInfo.baseName();
    
    QString userThemesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/themes";
    QDir().mkpath(userThemesPath);
    
    QString destPath = QString("%1/%2.json").arg(userThemesPath, themeName);
    
    if (QFile::exists(destPath)) {
        QFile::remove(destPath);
    }
    
    if (!QFile::copy(cleanPath, destPath)) {
        qWarning() << "Failed to copy theme file to" << destPath;
        return false;
    }
    
    discoverThemes();
    setCurrentTheme(themeName);
    
    return true;
}

bool ThemeManager::exportTheme(const QString &filePath) const
{
    QString cleanPath = filePath;
    if (cleanPath.startsWith("file:///")) {
        cleanPath = cleanPath.mid(8);
    } else if (cleanPath.startsWith("file://")) {
        cleanPath = cleanPath.mid(7);
    }
    
    QJsonObject themeObj = QJsonObject::fromVariantMap(m_effectiveTheme);
    QJsonDocument doc(themeObj);
    
    QFile file(cleanPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file for export:" << cleanPath;
        return false;
    }
    
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    
    return true;
}

QString ThemeManager::getPropertyType(const QString &key) const
{
    QVariant value = m_effectiveTheme.value(key);
    
    if (value.type() == QVariant::String && QColor::isValidColor(value.toString())) {
        return "color";
    } else if (value.type() == QVariant::Int || value.type() == QVariant::Double) {
        return "number";
    } else if (value.type() == QVariant::String) {
        return "string";
    } else if (value.type() == QVariant::Bool) {
        return "boolean";
    }
    
    return "unknown";
}

QColor ThemeManager::getThemePreviewBackground(const QString &themeName) const
{
    QSettings settings;
    QVariantMap userOverrides;
    settings.beginGroup(QString("theme/overrides/%1").arg(themeName));
    QStringList keys = settings.allKeys();
    for (const QString &key : keys) {
        userOverrides[key] = settings.value(key);
    }
    settings.endGroup();
    
    if (userOverrides.contains("background")) {
        QVariant value = userOverrides["background"];
        if (value.type() == QVariant::String) {
            return QColor(value.toString());
        }
    }
    
    QString filePath = QString(":/resources/themes/%1.json").arg(themeName);
    QFile file(filePath);
    
    if (!file.exists()) {
        QString userThemesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/themes";
        filePath = QString("%1/%2.json").arg(userThemesPath, themeName);
        file.setFileName(filePath);
    }
    
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        QVariantMap themeData = doc.object().toVariantMap();
        
        if (themeData.contains("background")) {
            return QColor(themeData["background"].toString());
        }
    }
    
    if (m_defaultTheme.contains("background")) {
        return QColor(m_defaultTheme["background"].toString());
    }
    
    return QColor("#1e1e1e");
}

QColor ThemeManager::getThemePreviewPrimary(const QString &themeName) const
{
    QSettings settings;
    QVariantMap userOverrides;
    settings.beginGroup(QString("theme/overrides/%1").arg(themeName));
    QStringList keys = settings.allKeys();
    for (const QString &key : keys) {
        userOverrides[key] = settings.value(key);
    }
    settings.endGroup();
    
    if (userOverrides.contains("primary")) {
        QVariant value = userOverrides["primary"];
        if (value.type() == QVariant::String) {
            return QColor(value.toString());
        }
    }
    
    QString filePath = QString(":/resources/themes/%1.json").arg(themeName);
    QFile file(filePath);
    
    if (!file.exists()) {
        QString userThemesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/themes";
        filePath = QString("%1/%2.json").arg(userThemesPath, themeName);
        file.setFileName(filePath);
    }
    
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        QVariantMap themeData = doc.object().toVariantMap();
        
        if (themeData.contains("primary")) {
            return QColor(themeData["primary"].toString());
        }
    }
    
    if (m_defaultTheme.contains("primary")) {
        return QColor(m_defaultTheme["primary"].toString());
    }
    
    return QColor("#0d7377");
}