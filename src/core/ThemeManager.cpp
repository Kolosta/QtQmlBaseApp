#include "ThemeManager.h"
#include "core/theme/ThemePresets.h"
#include <QSettings>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

ThemeManager& ThemeManager::instance() {
    static ThemeManager instance;
    return instance;
}

ThemeManager::ThemeManager(QObject *parent)
    : QObject(parent)
{
    // Créer les atomes
    m_colorAtom = new ColorAtom(this);
    m_sizeAtom = new SizeAtom(this);
    m_weightAtom = new WeightAtom(this);
    
    // Créer les molécules
    m_surfaceMolecule = new SurfaceMolecule(m_colorAtom, m_sizeAtom, this, this);
    m_fontMolecule = new FontMolecule(m_colorAtom, m_weightAtom, m_sizeAtom, this, this);
    m_borderMolecule = new BorderMolecule(m_colorAtom, m_sizeAtom, this, this);
    
    // Charger les paramètres sauvegardés
    loadSavedSettings();
}

void ThemeManager::setCurrentTheme(const QString& theme) {
    if (m_currentTheme == theme) return;
    
    m_currentTheme = theme;
    
    // Appliquer le preset compilé
    ThemeRegistry::applyTheme(theme, m_colorAtom, m_sizeAtom);
    
    // Notifier tous les modules
    emit m_surfaceMolecule->changed();
    emit m_fontMolecule->changed();
    emit m_borderMolecule->changed();
    
    saveSettings();
    emit currentThemeChanged();
}

QStringList ThemeManager::availableThemes() const {
    return ThemeRegistry::availableThemes();
}

void ThemeManager::setScale(qreal s) {
    s = qBound(0.5, s, 3.0);
    
    if (qAbs(m_scale - s) < 0.001) return;
    
    m_scale = s;
    
    // Notifier toutes les molécules qui dépendent du scale
    emit m_surfaceMolecule->changed();
    emit m_fontMolecule->changed();
    emit m_borderMolecule->changed();
    
    saveSettings();
    emit scaleChanged();
}

void ThemeManager::loadSavedSettings() {
    QSettings settings;
    
    // Charger le thème
    QString savedTheme = settings.value("theme/current", "Dark").toString();
    
    // Charger le scale
    qreal savedScale = settings.value("theme/scale", 1.0).toReal();
    m_scale = savedScale;
    
    // Appliquer le thème
    ThemeRegistry::applyTheme(savedTheme, m_colorAtom, m_sizeAtom);
    m_currentTheme = savedTheme;
}

void ThemeManager::saveSettings() {
    QSettings settings;
    settings.setValue("theme/current", m_currentTheme);
    settings.setValue("theme/scale", m_scale);
    settings.sync();
}

QColor ThemeManager::getThemePreviewPrimary(const QString& themeName) const {
    return ThemeRegistry::getPreviewPrimary(themeName);
}

QColor ThemeManager::getThemePreviewBackground(const QString& themeName) const {
    return ThemeRegistry::getPreviewBackground(themeName);
}

void ThemeManager::resetToDefaults() {
    setCurrentTheme("Dark");
    setScale(1.0);
}

// ===== EXPORT/IMPORT JSON (Optionnel) =====
bool ThemeManager::exportToJson(const QString& filePath) const {
    QJsonObject root;
    root["name"] = m_currentTheme;
    root["version"] = "3.0";

    QJsonObject colors;

    // Background
    colors["bg_primary"] = m_colorAtom->m_bgPrimary.name();
    colors["bg_secondary"] = m_colorAtom->m_bgSecondary.name();
    colors["bg_tertiary"] = m_colorAtom->m_bgTertiary.name();

    // Surface
    colors["surf_primary"] = m_colorAtom->m_surfPrimary.name();
    colors["surf_secondary"] = m_colorAtom->m_surfSecondary.name();
    colors["surf_hover"] = m_colorAtom->m_surfHover.name();
    colors["surf_active"] = m_colorAtom->m_surfActive.name();
    colors["surf_disabled"] = m_colorAtom->m_surfDisabled.name();

    // Primary
    colors["prim_base"] = m_colorAtom->m_primBase.name();
    colors["prim_hover"] = m_colorAtom->m_primHover.name();
    colors["prim_active"] = m_colorAtom->m_primActive.name();
    colors["prim_disabled"] = m_colorAtom->m_primDisabled.name();

    // Text
    colors["text_primary"] = m_colorAtom->m_textPrimary.name();
    colors["text_secondary"] = m_colorAtom->m_textSecondary.name();
    colors["text_tertiary"] = m_colorAtom->m_textTertiary.name();
    colors["text_disabled"] = m_colorAtom->m_textDisabled.name();
    colors["text_on_primary"] = m_colorAtom->m_textOnPrimary.name();

    // Border
    colors["border_primary"] = m_colorAtom->m_borderPrimary.name();
    colors["border_secondary"] = m_colorAtom->m_borderSecondary.name();
    colors["border_focus"] = m_colorAtom->m_borderFocus.name();
    colors["border_disabled"] = m_colorAtom->m_borderDisabled.name();

    // Accent
    colors["accent_base"] = m_colorAtom->m_accentBase.name();
    colors["accent_hover"] = m_colorAtom->m_accentHover.name();
    colors["accent_active"] = m_colorAtom->m_accentActive.name();

    // Status
    colors["stat_error"] = m_colorAtom->m_statError.name();
    colors["stat_error_hover"] = m_colorAtom->m_statErrorHover.name();
    colors["stat_success"] = m_colorAtom->m_statSuccess.name();
    colors["stat_success_hover"] = m_colorAtom->m_statSuccessHover.name();
    colors["stat_warning"] = m_colorAtom->m_statWarning.name();
    colors["stat_warning_hover"] = m_colorAtom->m_statWarningHover.name();
    colors["stat_info"] = m_colorAtom->m_statInfo.name();
    colors["stat_info_hover"] = m_colorAtom->m_statInfoHover.name();

    root["colors"] = colors;

    // Sizes
    QJsonObject sizes;
    sizes["small"] = m_sizeAtom->m_small;
    sizes["medium"] = m_sizeAtom->m_medium;
    sizes["large"] = m_sizeAtom->m_large;
    root["sizes"] = sizes;

    QString cleanPath = filePath;
    if (cleanPath.startsWith("file:///")) cleanPath = cleanPath.mid(8);

    QFile file(cleanPath);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    return true;
}


bool ThemeManager::importFromJson(const QString& filePath) {
    QString cleanPath = filePath;
    if (cleanPath.startsWith("file:///")) cleanPath = cleanPath.mid(8);

    QFile file(cleanPath);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) return false;

    QJsonObject root = doc.object();
    if (root.contains("colors")) {
        QJsonObject c = root["colors"].toObject();

        // Background
        if (c.contains("bg_primary"))      m_colorAtom->m_bgPrimary = QColor(c["bg_primary"].toString());
        if (c.contains("bg_secondary"))    m_colorAtom->m_bgSecondary = QColor(c["bg_secondary"].toString());
        if (c.contains("bg_tertiary"))     m_colorAtom->m_bgTertiary = QColor(c["bg_tertiary"].toString());

        // Surface
        if (c.contains("surf_primary"))    m_colorAtom->m_surfPrimary = QColor(c["surf_primary"].toString());
        if (c.contains("surf_secondary"))  m_colorAtom->m_surfSecondary = QColor(c["surf_secondary"].toString());
        if (c.contains("surf_hover"))      m_colorAtom->m_surfHover = QColor(c["surf_hover"].toString());
        if (c.contains("surf_active"))     m_colorAtom->m_surfActive = QColor(c["surf_active"].toString());
        if (c.contains("surf_disabled"))   m_colorAtom->m_surfDisabled = QColor(c["surf_disabled"].toString());

        // Primary
        if (c.contains("prim_base"))       m_colorAtom->m_primBase = QColor(c["prim_base"].toString());
        if (c.contains("prim_hover"))      m_colorAtom->m_primHover = QColor(c["prim_hover"].toString());
        if (c.contains("prim_active"))     m_colorAtom->m_primActive = QColor(c["prim_active"].toString());
        if (c.contains("prim_disabled"))   m_colorAtom->m_primDisabled = QColor(c["prim_disabled"].toString());

        // Text
        if (c.contains("text_primary"))    m_colorAtom->m_textPrimary = QColor(c["text_primary"].toString());
        if (c.contains("text_secondary"))  m_colorAtom->m_textSecondary = QColor(c["text_secondary"].toString());
        if (c.contains("text_tertiary"))   m_colorAtom->m_textTertiary = QColor(c["text_tertiary"].toString());
        if (c.contains("text_disabled"))   m_colorAtom->m_textDisabled = QColor(c["text_disabled"].toString());
        if (c.contains("text_on_primary")) m_colorAtom->m_textOnPrimary = QColor(c["text_on_primary"].toString());

        // Border
        if (c.contains("border_primary"))   m_colorAtom->m_borderPrimary = QColor(c["border_primary"].toString());
        if (c.contains("border_secondary")) m_colorAtom->m_borderSecondary = QColor(c["border_secondary"].toString());
        if (c.contains("border_focus"))     m_colorAtom->m_borderFocus = QColor(c["border_focus"].toString());
        if (c.contains("border_disabled"))  m_colorAtom->m_borderDisabled = QColor(c["border_disabled"].toString());

        // Accent
        if (c.contains("accent_base"))     m_colorAtom->m_accentBase = QColor(c["accent_base"].toString());
        if (c.contains("accent_hover"))    m_colorAtom->m_accentHover = QColor(c["accent_hover"].toString());
        if (c.contains("accent_active"))   m_colorAtom->m_accentActive = QColor(c["accent_active"].toString());

        // Status
        if (c.contains("stat_error"))       m_colorAtom->m_statError = QColor(c["stat_error"].toString());
        if (c.contains("stat_error_hover")) m_colorAtom->m_statErrorHover = QColor(c["stat_error_hover"].toString());
        if (c.contains("stat_success"))     m_colorAtom->m_statSuccess = QColor(c["stat_success"].toString());
        if (c.contains("stat_success_hover")) m_colorAtom->m_statSuccessHover = QColor(c["stat_success_hover"].toString());
        if (c.contains("stat_warning"))     m_colorAtom->m_statWarning = QColor(c["stat_warning"].toString());
        if (c.contains("stat_warning_hover")) m_colorAtom->m_statWarningHover = QColor(c["stat_warning_hover"].toString());
        if (c.contains("stat_info"))        m_colorAtom->m_statInfo = QColor(c["stat_info"].toString());
        if (c.contains("stat_info_hover"))  m_colorAtom->m_statInfoHover = QColor(c["stat_info_hover"].toString());

        emit m_colorAtom->changed();
    }

    if (root.contains("sizes")) {
        QJsonObject s = root["sizes"].toObject();
        if (s.contains("small"))  m_sizeAtom->m_small = s["small"].toInt();
        if (s.contains("medium")) m_sizeAtom->m_medium = s["medium"].toInt();
        if (s.contains("large"))  m_sizeAtom->m_large = s["large"].toInt();
        emit m_sizeAtom->changed();
    }

    // Notifier
    emit m_surfaceMolecule->changed();
    emit m_fontMolecule->changed();
    emit m_borderMolecule->changed();

    m_currentTheme = root["name"].toString("Imported");
    emit currentThemeChanged();

    return true;
}


// #include "ThemeManager.h"
// #include <QFile>
// #include <QJsonDocument>
// #include <QJsonObject>
// #include <QStandardPaths>
// #include <QDir>
// #include <QSettings>
// #include <QDebug>

// ThemeManager& ThemeManager::instance() {
//     static ThemeManager instance;
//     return instance;
// }

// ThemeManager::ThemeManager(QObject *parent)
//     : QObject(parent)
// {
//     // Créer les sous-systèmes
//     m_colors = new ThemePalette(this);
//     m_sizes = new ThemeSizes(this, this);
    
//     // Créer les composants
//     m_prefWindow = new PreferencesWindowStyle(m_colors, m_sizes, this, this);
//     m_menuBar = new MenuBarStyle(m_colors, m_sizes, this, this);
//     m_button = new ButtonStyle(m_colors, m_sizes, this, this);
    
//     // Découvrir les thèmes disponibles
//     discoverThemes();
    
//     // Charger le thème sauvegardé
//     QSettings settings;
//     QString savedTheme = settings.value("theme/current", "dark").toString();
//     qreal savedScale = settings.value("theme/scale", 1.0).toReal();
    
//     m_scale = savedScale;
//     loadTheme(savedTheme);
//     loadUserOverrides();
// }

// void ThemeManager::setCurrentTheme(const QString& theme) {
//     if (m_currentTheme == theme) return;
    
//     m_currentTheme = theme;
//     loadTheme(theme);
//     loadUserOverrides();
    
//     QSettings settings;
//     settings.setValue("theme/current", theme);
    
//     emit currentThemeChanged();
// }

// void ThemeManager::setScale(qreal s) {
//     s = qBound(0.5, s, 3.0);
    
//     if (qAbs(m_scale - s) < 0.001) return;
    
//     m_scale = s;
    
//     QSettings settings;
//     settings.setValue("theme/scale", s);
    
//     // Forcer le rafraîchissement de toutes les valeurs scalées
//     emit m_sizes->changed();
//     emit m_prefWindow->changed();
//     emit m_menuBar->changed();
//     emit m_button->changed();
    
//     emit scaleChanged();
// }

// void ThemeManager::discoverThemes() {
//     m_availableThemes.clear();
    
//     // Thèmes intégrés
//     QStringList builtinThemes = {
//         "dark", "light", "grey", "muted_green",
//         "blue", "sepia", "snow", "arctic"
//     };
    
//     for (const QString &themeName : builtinThemes) {
//         QString path = QString(":/resources/themes/%1.json").arg(themeName);
//         if (QFile::exists(path)) {
//             m_availableThemes.append(themeName);
//         }
//     }
    
//     // Thèmes utilisateur
//     QString userThemesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/themes";
//     QDir userThemesDir(userThemesPath);
    
//     if (userThemesDir.exists()) {
//         QStringList filters{"*.json"};
//         QFileInfoList files = userThemesDir.entryInfoList(filters, QDir::Files);
        
//         for (const QFileInfo &fileInfo : files) {
//             QString themeName = fileInfo.baseName();
//             if (!m_availableThemes.contains(themeName)) {
//                 m_availableThemes.append(themeName);
//             }
//         }
//     }
    
//     emit availableThemesChanged();
// }

// bool ThemeManager::loadTheme(const QString& themeName) {
//     // Chercher d'abord dans les ressources
//     QString filePath = QString(":/resources/themes/%1.json").arg(themeName);
//     QFile file(filePath);
    
//     // Sinon dans le dossier utilisateur
//     if (!file.exists()) {
//         QString userThemesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/themes";
//         filePath = QString("%1/%2.json").arg(userThemesPath, themeName);
//         file.setFileName(filePath);
//     }
    
//     if (!file.open(QIODevice::ReadOnly)) {
//         qWarning() << "Could not open theme file:" << filePath;
//         return false;
//     }
    
//     QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
//     file.close();
    
//     if (doc.isNull() || !doc.isObject()) {
//         qWarning() << "Invalid theme file format:" << filePath;
//         return false;
//     }
    
//     QJsonObject root = doc.object();
    
//     // Charger les couleurs
//     if (root.contains("colors")) {
//         m_colors->loadFromJson(root["colors"].toObject());
//     }
    
//     // Charger les tailles/spacing/radius/etc
//     if (root.contains("sizes")) {
//         m_sizes->loadFromJson(root["sizes"].toObject());
//     }
    
//     // Charger les composants
//     if (root.contains("components")) {
//         QJsonObject components = root["components"].toObject();
        
//         if (components.contains("pref_window")) {
//             m_prefWindow->loadFromJson(components["pref_window"].toObject());
//         }
//         if (components.contains("menu_bar")) {
//             m_menuBar->loadFromJson(components["menu_bar"].toObject());
//         }
//         if (components.contains("button")) {
//             m_button->loadFromJson(components["button"].toObject());
//         }
//     }
    
//     m_currentTheme = themeName;
//     return true;
// }

// void ThemeManager::loadUserOverrides() {
//     QSettings settings;
//     settings.beginGroup(QString("theme/overrides/%1").arg(m_currentTheme));
    
//     // Charger les overrides utilisateur depuis QSettings
//     // Format: "colors/backgroundPrimary", "components/prefWindow/sidebarWidth", etc.
    
//     QStringList keys = settings.allKeys();
//     for (const QString &key : keys) {
//         QVariant value = settings.value(key);
        
//         // Parser le chemin (ex: "colors/backgroundPrimary")
//         QStringList parts = key.split('/');
//         if (parts.size() < 2) continue;
        
//         QString section = parts[0];
        
//         if (section == "colors") {
//             // Appliquer directement via Q_PROPERTY
//             QString propName = parts[1];
//             m_colors->setProperty(propName.toLatin1().constData(), value);
//         }
//         else if (section == "sizes") {
//             QString propName = parts[1];
//             m_sizes->setProperty(propName.toLatin1().constData(), value);
//         }
//         else if (section == "components") {
//             if (parts.size() < 3) continue;
//             QString componentName = parts[1];
//             QString propName = parts[2];
            
//             if (componentName == "prefWindow") {
//                 m_prefWindow->setProperty(propName.toLatin1().constData(), value);
//             }
//             else if (componentName == "menuBar") {
//                 m_menuBar->setProperty(propName.toLatin1().constData(), value);
//             }
//             else if (componentName == "button") {
//                 m_button->setProperty(propName.toLatin1().constData(), value);
//             }
//         }
//     }
    
//     settings.endGroup();
// }

// void ThemeManager::saveUserOverrides() {
//     QSettings settings;
//     settings.beginGroup(QString("theme/overrides/%1").arg(m_currentTheme));
//     settings.remove(""); // Clear all
    
//     // Sauvegarder les overrides de chaque composant
//     QJsonObject prefWindowJson = m_prefWindow->toJson();
//     for (auto it = prefWindowJson.begin(); it != prefWindowJson.end(); ++it) {
//         settings.setValue(QString("components/prefWindow/%1").arg(it.key()), it.value().toVariant());
//     }
    
//     QJsonObject menuBarJson = m_menuBar->toJson();
//     for (auto it = menuBarJson.begin(); it != menuBarJson.end(); ++it) {
//         settings.setValue(QString("components/menuBar/%1").arg(it.key()), it.value().toVariant());
//     }
    
//     QJsonObject buttonJson = m_button->toJson();
//     for (auto it = buttonJson.begin(); it != buttonJson.end(); ++it) {
//         settings.setValue(QString("components/button/%1").arg(it.key()), it.value().toVariant());
//     }
    
//     settings.endGroup();
//     settings.sync();
// }

// bool ThemeManager::saveTheme(const QString& themeName) {
//     QString userThemesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/themes";
//     QDir().mkpath(userThemesPath);
    
//     QString filePath = QString("%1/%2.json").arg(userThemesPath, themeName);
    
//     QJsonObject root;
//     root["name"] = themeName;
//     root["version"] = "2.0";
    
//     // Sauvegarder tout
//     root["colors"] = m_colors->toJson();
//     root["sizes"] = m_sizes->toJson();
    
//     QJsonObject components;
//     components["pref_window"] = m_prefWindow->toJson();
//     components["menu_bar"] = m_menuBar->toJson();
//     components["button"] = m_button->toJson();
//     root["components"] = components;
    
//     QJsonDocument doc(root);
//     QFile file(filePath);
    
//     if (!file.open(QIODevice::WriteOnly)) {
//         qWarning() << "Could not save theme file:" << filePath;
//         return false;
//     }
    
//     file.write(doc.toJson(QJsonDocument::Indented));
//     file.close();
    
//     discoverThemes();
//     return true;
// }

// bool ThemeManager::importTheme(const QString& filePath) {
//     QString cleanPath = filePath;
//     if (cleanPath.startsWith("file:///")) {
//         cleanPath = cleanPath.mid(8);
//     } else if (cleanPath.startsWith("file://")) {
//         cleanPath = cleanPath.mid(7);
//     }
    
//     QFile file(cleanPath);
//     if (!file.open(QIODevice::ReadOnly)) {
//         qWarning() << "Could not open file for import:" << cleanPath;
//         return false;
//     }
    
//     QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
//     file.close();
    
//     if (doc.isNull() || !doc.isObject()) {
//         qWarning() << "Invalid theme file format";
//         return false;
//     }
    
//     QFileInfo fileInfo(cleanPath);
//     QString themeName = fileInfo.baseName();
    
//     QString userThemesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/themes";
//     QDir().mkpath(userThemesPath);
    
//     QString destPath = QString("%1/%2.json").arg(userThemesPath, themeName);
    
//     if (QFile::exists(destPath)) {
//         QFile::remove(destPath);
//     }
    
//     if (!QFile::copy(cleanPath, destPath)) {
//         qWarning() << "Failed to copy theme file to" << destPath;
//         return false;
//     }
    
//     discoverThemes();
//     setCurrentTheme(themeName);
    
//     return true;
// }

// bool ThemeManager::exportTheme(const QString& filePath) {
//     return saveTheme(QFileInfo(filePath).baseName());
// }

// void ThemeManager::resetAllToDefaults() {
//     m_colors->resetToDefaults();
//     m_sizes->resetToDefaults();
//     resetComponentsToDefaults();
// }

// void ThemeManager::resetComponentsToDefaults() {
//     m_prefWindow->resetAll();
//     m_menuBar->resetAll();
//     m_button->resetAll();
    
//     saveUserOverrides();
// }

// QColor ThemeManager::getThemePreviewPrimary(const QString& themeName) const {
//     QString filePath = QString(":/resources/themes/%1.json").arg(themeName);
//     QFile file(filePath);
    
//     if (!file.exists()) {
//         QString userThemesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/themes";
//         filePath = QString("%1/%2.json").arg(userThemesPath, themeName);
//         file.setFileName(filePath);
//     }
    
//     if (file.open(QIODevice::ReadOnly)) {
//         QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
//         file.close();
        
//         QJsonObject root = doc.object();
//         if (root.contains("colors")) {
//             QJsonObject colors = root["colors"].toObject();
//             if (colors.contains("primary_base")) {
//                 return QColor(colors["primary_base"].toString());
//             }
//         }
//     }
    
//     return QColor("#0d7377");
// }

// QColor ThemeManager::getThemePreviewBackground(const QString& themeName) const {
//     QString filePath = QString(":/resources/themes/%1.json").arg(themeName);
//     QFile file(filePath);
    
//     if (!file.exists()) {
//         QString userThemesPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/themes";
//         filePath = QString("%1/%2.json").arg(userThemesPath, themeName);
//         file.setFileName(filePath);
//     }
    
//     if (file.open(QIODevice::ReadOnly)) {
//         QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
//         file.close();
        
//         QJsonObject root = doc.object();
//         if (root.contains("colors")) {
//             QJsonObject colors = root["colors"].toObject();
//             if (colors.contains("background_primary")) {
//                 return QColor(colors["background_primary"].toString());
//             }
//         }
//     }
    
//     return QColor("#1e1e1e");
// }