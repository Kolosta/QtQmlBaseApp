#include "ThemePalette.h"
#include <QJsonObject>
#include <QMetaProperty>

ThemePalette::ThemePalette(QObject *parent)
    : QObject(parent)
{
}

void ThemePalette::loadFromJson(const QJsonObject& json) {
    if (json.isEmpty()) return;
    
    const QMetaObject* meta = metaObject();
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) {
        QMetaProperty prop = meta->property(i);
        QString propName = prop.name();
        
        if (propName == "objectName") continue;
        
        // Convertir camelCase en snake_case pour le JSON
        // ex: backgroundPrimary -> background_primary
        QString jsonKey;
        for (int j = 0; j < propName.length(); ++j) {
            QChar c = propName[j];
            if (c.isUpper() && j > 0) {
                jsonKey += '_';
                jsonKey += c.toLower();
            } else {
                jsonKey += c.toLower();
            }
        }
        
        if (json.contains(jsonKey)) {
            QString colorStr = json[jsonKey].toString();
            QColor color(colorStr);
            if (color.isValid()) {
                prop.write(this, color);
            }
        }
    }
    
    emit changed();
}

QJsonObject ThemePalette::toJson() const {
    QJsonObject json;
    const QMetaObject* meta = metaObject();
    
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) {
        QMetaProperty prop = meta->property(i);
        QString propName = prop.name();
        
        if (propName == "objectName") continue;
        
        // Convertir camelCase en snake_case
        QString jsonKey;
        for (int j = 0; j < propName.length(); ++j) {
            QChar c = propName[j];
            if (c.isUpper() && j > 0) {
                jsonKey += '_';
                jsonKey += c.toLower();
            } else {
                jsonKey += c.toLower();
            }
        }
        
        QColor color = prop.read(this).value<QColor>();
        json[jsonKey] = color.name();
    }
    
    return json;
}

void ThemePalette::resetToDefaults() {
    // Recréer les couleurs par défaut
    m_backgroundPrimary = QColor("#1e1e1e");
    m_backgroundSecondary = QColor("#252525");
    m_backgroundTertiary = QColor("#2a2a2a");
    
    m_surfacePrimary = QColor("#2d2d2d");
    m_surfaceSecondary = QColor("#353535");
    m_surfaceHover = QColor("#3d3d3d");
    m_surfaceActive = QColor("#4d4d4d");
    m_surfaceDisabled = QColor("#252525");
    
    m_primaryBase = QColor("#0d7377");
    m_primaryHover = QColor("#14a0a5");
    m_primaryActive = QColor("#0a5b5e");
    m_primaryDisabled = QColor("#084648");
    
    m_textPrimary = QColor("#ffffff");
    m_textSecondary = QColor("#b0b0b0");
    m_textTertiary = QColor("#808080");
    m_textDisabled = QColor("#666666");
    m_textOnPrimary = QColor("#ffffff");
    
    m_borderPrimary = QColor("#3d3d3d");
    m_borderSecondary = QColor("#454545");
    m_borderFocus = QColor("#4a9eff");
    m_borderDisabled = QColor("#2d2d2d");
    
    m_accentBase = QColor("#4a9eff");
    m_accentHover = QColor("#6bb0ff");
    m_accentActive = QColor("#2a7edf");
    
    m_statusError = QColor("#f44336");
    m_statusErrorHover = QColor("#f55a4e");
    m_statusSuccess = QColor("#4caf50");
    m_statusSuccessHover = QColor("#66bb6a");
    m_statusWarning = QColor("#ff9800");
    m_statusWarningHover = QColor("#ffa726");
    m_statusInfo = QColor("#2196f3");
    m_statusInfoHover = QColor("#42a5f5");
    
    emit changed();
}