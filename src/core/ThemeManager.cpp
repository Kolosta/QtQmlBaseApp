#include "ThemeManager.h"
#include <QSettings>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>

ThemeManager& ThemeManager::instance() {
    static ThemeManager instance;
    return instance;
}

ThemeManager::ThemeManager(QObject *parent)
    : QObject(parent)
{
    // Initialiser les presets intégrés
    initializeBuiltinPresets();
    
    // Charger les paramètres
    loadSavedSettings();

    // Vérifier que le thème existe
    if (!m_presets.contains(m_currentThemeName)) {
        qWarning() << "Theme" << m_currentThemeName << "not found after init, using Dark";
        m_currentThemeName = "Dark";
    }
    
    // Obtenir le preset actif (avec ou sans modifications)
    ThemePreset* activePreset = m_unsavedChanges.value(m_currentThemeName, 
                                                        m_presets.value(m_currentThemeName));
    
    // Créer nos propres instances que nous allons modifier
    m_colors = new ThemeColors(this);
    m_spacing = new ThemeSpacing(this, this);
    m_font = new ThemeFont(this, this);
    m_border = new ThemeBorder(this, this);
    m_size = new ThemeSize(this, this);
    m_transition = new ThemeTransition(this);
    m_components = new ThemeComponents(this, this);

        // Copier les valeurs du preset actif
    if (activePreset) {
        m_colors->copyFrom(activePreset->colors);
        m_spacing->copyFrom(activePreset->spacing);
        m_font->copyFrom(activePreset->font);
        m_border->copyFrom(activePreset->border);
        m_size->copyFrom(activePreset->size);
        m_transition->copyFrom(activePreset->transition);
        m_components->copyFrom(activePreset->components);
        
        m_hasUnsavedChanges = m_unsavedChanges.contains(m_currentThemeName);
    }
    
    // Connecter les signaux pour détecter les modifications
    connect(m_colors, &ThemeColors::changed, this, &ThemeManager::markAsModified);
    connect(m_spacing, &ThemeSpacing::changed, this, &ThemeManager::markAsModified);
    connect(m_font, &ThemeFont::changed, this, &ThemeManager::markAsModified);
    connect(m_border, &ThemeBorder::changed, this, &ThemeManager::markAsModified);
    connect(m_size, &ThemeSize::changed, this, &ThemeManager::markAsModified);
    connect(m_transition, &ThemeTransition::changed, this, &ThemeManager::markAsModified);
    connect(m_components, &ThemeComponents::changed, this, &ThemeManager::markAsModified);
    
    qDebug() << "ThemeManager initialized with theme:" << m_currentThemeName << "scale:" << m_scale;
}

void ThemeManager::initializeBuiltinPresets() {
    // Dark (défaut)
    ThemePreset* dark = new ThemePreset("Dark", this);
    m_presets["Dark"] = dark;
    
    // ===== ARCTIC =====
    ThemePreset* arctic = new ThemePreset("Arctic", this);
    arctic->colors->background()->primary()->setDefaultColor(QColor("#e8f4f8"));
    arctic->colors->background()->secondary()->setDefaultColor(QColor("#dbeff5"));
    arctic->colors->primary()->setDefaultColor(QColor("#006494"));
    arctic->colors->primary()->setHover(QColor("#0077b6"));
    arctic->colors->text()->primary()->setDefaultColor(QColor("#001f3f"));
    m_presets["Arctic"] = arctic;
    
    // ===== BLUE =====
    ThemePreset* blue = new ThemePreset("Blue", this);
    blue->colors->background()->primary()->setDefaultColor(QColor("#0d1b2a"));
    blue->colors->primary()->setDefaultColor(QColor("#1e90ff"));
    blue->colors->text()->primary()->setDefaultColor(QColor("#e0f4ff"));
    m_presets["Blue"] = blue;
}

void ThemeManager::loadSavedSettings() {
    QSettings settings;
    m_currentThemeName = settings.value("theme/current", "Dark").toString();

    // Sécurité: Si le thème enregistré n'existe plus, revenir à "Dark"
    if (!m_presets.contains(m_currentThemeName)) {
        qWarning() << "Theme" << m_currentThemeName << "not found. Reverting to Dark.";
        m_currentThemeName = "Dark";
    }


    m_scale = settings.value("theme/scale", 1.0).toReal();
    
    // Charger les modifications par thème
    for (const QString& themeName : m_presets.keys()) {
        QString key = QString("theme/modifications/%1").arg(themeName);
        if (settings.contains(key)) {
            QString jsonStr = settings.value(key).toString();
            QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
            if (!doc.isNull()) {
                ThemePreset* modified = new ThemePreset(themeName, this);
                modified->copyFrom(m_presets[themeName]); // Partir du preset de base
                modified->loadFromJson(doc.object()); // Appliquer les overrides
                m_unsavedChanges[themeName] = modified;
            }
        }
    }
}

void ThemeManager::saveSettings() {
    QSettings settings;
    settings.setValue("theme/current", m_currentThemeName);
    settings.setValue("theme/scale", m_scale);
    
    // Sauvegarder les modifications
    for (auto it = m_unsavedChanges.constBegin(); it != m_unsavedChanges.constEnd(); ++it) {
        QString key = QString("theme/modifications/%1").arg(it.key());
        QJsonDocument doc(it.value()->toJson());
        settings.setValue(key, QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
    }
    
    settings.sync();
}

void ThemeManager::setCurrentTheme(const QString& theme) {
    if (m_currentThemeName == theme || !m_presets.contains(theme)) return;
    
    if (m_hasUnsavedChanges) {
        saveCurrentThemeChanges();
    }
    
    m_currentThemeName = theme;
    applyTheme(theme);
    
    saveSettings();
    emit currentThemeChanged();
}

void ThemeManager::applyTheme(const QString& themeName) {
    ThemePreset* activePreset = m_unsavedChanges.value(themeName, m_presets.value(themeName));
    if (!activePreset) return;
    
    // Déconnecter temporairement
    disconnect(m_colors, &ThemeColors::changed, this, &ThemeManager::markAsModified);
    disconnect(m_spacing, &ThemeSpacing::changed, this, &ThemeManager::markAsModified);
    disconnect(m_font, &ThemeFont::changed, this, &ThemeManager::markAsModified);
    disconnect(m_border, &ThemeBorder::changed, this, &ThemeManager::markAsModified);
    disconnect(m_size, &ThemeSize::changed, this, &ThemeManager::markAsModified);
    disconnect(m_transition, &ThemeTransition::changed, this, &ThemeManager::markAsModified);
    disconnect(m_components, &ThemeComponents::changed, this, &ThemeManager::markAsModified);
    
    // Copier les valeurs
    m_colors->copyFrom(activePreset->colors);
    m_spacing->copyFrom(activePreset->spacing);
    m_font->copyFrom(activePreset->font);
    m_border->copyFrom(activePreset->border);
    m_size->copyFrom(activePreset->size);
    m_transition->copyFrom(activePreset->transition);
    m_components->copyFrom(activePreset->components);
    
    // Reconnecter
    connect(m_colors, &ThemeColors::changed, this, &ThemeManager::markAsModified);
    connect(m_spacing, &ThemeSpacing::changed, this, &ThemeManager::markAsModified);
    connect(m_font, &ThemeFont::changed, this, &ThemeManager::markAsModified);
    connect(m_border, &ThemeBorder::changed, this, &ThemeManager::markAsModified);
    connect(m_size, &ThemeSize::changed, this, &ThemeManager::markAsModified);
    connect(m_transition, &ThemeTransition::changed, this, &ThemeManager::markAsModified);
    connect(m_components, &ThemeComponents::changed, this, &ThemeManager::markAsModified);
    
    m_hasUnsavedChanges = m_unsavedChanges.contains(themeName);
    emit hasUnsavedChangesChanged();
}

QStringList ThemeManager::availableThemes() const {
    return m_presets.keys();
}

void ThemeManager::setScale(qreal s) {
    s = qBound(0.5, s, 3.0);
    if (qAbs(m_scale - s) < 0.001) return;
    
    m_scale = s;
    
    qDebug() << "Scale changed to:" << m_scale;
    
    // Notifier tous les SizeValue via leurs parents
    emit m_spacing->changed();
    emit m_font->changed();
    emit m_border->changed();
    emit m_size->changed();
    emit m_components->changed();
    
    // Sauvegarder immédiatement le scale
    saveSettings();
    emit scaleChanged();
}

void ThemeManager::markAsModified() {
    // Ne marquer comme modifié que si ce n'est pas déjà le cas
    // Cela évite les signaux en cascade
    // if (m_hasUnsavedChanges) return;
    
    // m_hasUnsavedChanges = true;
    // qDebug() << "Theme marked as modified";
    // emit hasUnsavedChangesChanged();
    // emit themeModified();
}

void ThemeManager::saveCurrentThemeChanges() {
    // Créer ou mettre à jour le preset modifié
    ThemePreset* modified = m_unsavedChanges.value(m_currentThemeName);
    if (!modified) {
        modified = new ThemePreset(m_currentThemeName, this);
        m_unsavedChanges[m_currentThemeName] = modified;
    }
    
    // Sauvegarder l'état actuel
    modified->colors->copyFrom(m_colors);
    modified->spacing->copyFrom(m_spacing);
    modified->font->copyFrom(m_font);
    modified->border->copyFrom(m_border);
    modified->size->copyFrom(m_size);
    modified->transition->copyFrom(m_transition);
    modified->components->copyFrom(m_components);
    
    m_hasUnsavedChanges = false;
    emit hasUnsavedChangesChanged();
    
    qDebug() << "Theme changes saved for:" << m_currentThemeName;
    
    saveSettings();
}
void ThemeManager::discardCurrentThemeChanges() {
    if (!m_hasUnsavedChanges) return;
    
    m_unsavedChanges.remove(m_currentThemeName);
    applyTheme(m_currentThemeName);
    
    m_hasUnsavedChanges = false;
    emit hasUnsavedChangesChanged();
    
    saveSettings();
}

bool ThemeManager::exportTheme(const QString& filePath) {
    QString cleanPath = filePath;
    if (cleanPath.startsWith("file:///")) cleanPath = cleanPath.mid(8);
    
    ThemePreset* current = m_unsavedChanges.value(m_currentThemeName, 
                                                   m_presets.value(m_currentThemeName));
    if (!current) return false;
    
    QFile file(cleanPath);
    if (!file.open(QIODevice::WriteOnly)) return false;
    
    QJsonDocument doc(current->toJson());
    file.write(doc.toJson(QJsonDocument::Indented));
    return true;
}

bool ThemeManager::importTheme(const QString& filePath) {
    QString cleanPath = filePath;
    if (cleanPath.startsWith("file:///")) cleanPath = cleanPath.mid(8);
    
    QFile file(cleanPath);
    if (!file.open(QIODevice::ReadOnly)) return false;
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isNull()) return false;
    
    ThemePreset* imported = new ThemePreset("Imported", this);
    imported->loadFromJson(doc.object());
    
    // Nom unique
    QString themeName = imported->name;
    int suffix = 1;
    while (m_presets.contains(themeName)) {
        themeName = QString("%1 (%2)").arg(imported->name).arg(suffix++);
    }
    imported->name = themeName;
    
    m_presets[themeName] = imported;
    emit availableThemesChanged();
    
    setCurrentTheme(themeName);
    return true;
}

void ThemeManager::resetToDefaults() {
    m_unsavedChanges.clear();
    setCurrentTheme("Dark");
    setScale(1.0);
    saveSettings();
}

QColor ThemeManager::getThemePreviewPrimary(const QString& themeName) const {
    ThemePreset* preset = m_presets.value(themeName);
    return preset ? preset->colors->primary()->defaultColor() : QColor("#0d7377");
}

QColor ThemeManager::getThemePreviewBackground(const QString& themeName) const {
    ThemePreset* preset = m_presets.value(themeName);
    return preset ? preset->colors->background()->primary()->defaultColor() : QColor("#1e1e1e");
}
