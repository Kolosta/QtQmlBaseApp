#ifndef THEMECOMPONENTS_H
#define THEMECOMPONENTS_H

#include <QObject>
#include "MenuBarTheme.h"
#include "ButtonTheme.h"
#include "PreferencesWindowTheme.h"

class ThemeManager;

class ThemeComponents : public QObject {
    Q_OBJECT
    Q_PROPERTY(MenuBarTheme* menuBar READ menuBar CONSTANT)
    Q_PROPERTY(ButtonTheme* button READ button CONSTANT)
    Q_PROPERTY(PreferencesWindowTheme* preferencesWindow READ preferencesWindow CONSTANT)

public:
    explicit ThemeComponents(ThemeManager* manager, QObject* parent = nullptr);
    
    MenuBarTheme* menuBar() const { return m_menuBar; }
    ButtonTheme* button() const { return m_button; }
    PreferencesWindowTheme* preferencesWindow() const { return m_preferencesWindow; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const ThemeComponents* other);

signals:
    void changed();

private:
    MenuBarTheme* m_menuBar;
    ButtonTheme* m_button;
    PreferencesWindowTheme* m_preferencesWindow;
};

#endif // THEMECOMPONENTS_H