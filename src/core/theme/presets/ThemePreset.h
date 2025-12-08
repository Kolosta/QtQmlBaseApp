#ifndef THEMEPRESET_H
#define THEMEPRESET_H

#include <QString>
#include <QJsonObject>
#include "../base/ThemeColors.h"
#include "../base/ThemeSpacing.h"
#include "../base/ThemeFont.h"
#include "../base/ThemeBorder.h"
#include "../base/ThemeSize.h"
#include "../base/ThemeTransition.h"
#include "../components/ThemeComponents.h"

class ThemeManager;

// Représente un thème complet (base + composants)
class ThemePreset {
public:
    QString name;
    
    // Propriétés de base
    ThemeColors* colors;
    ThemeSpacing* spacing;
    ThemeFont* font;
    ThemeBorder* border;
    ThemeSize* size;
    ThemeTransition* transition;
    
    // Composants
    ThemeComponents* components;
    
    explicit ThemePreset(const QString& themeName, ThemeManager* manager);
    ~ThemePreset();
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const ThemePreset* other);
};

#endif // THEMEPRESET_H