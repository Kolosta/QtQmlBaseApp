#ifndef PREFERENCESWINDOWTHEME_H
#define PREFERENCESWINDOWTHEME_H

#include <QObject>
#include "../base/SizeValue.h"

class ThemeManager;

class PreferencesWindowTheme : public QObject {
    Q_OBJECT
    Q_PROPERTY(SizeValue* sidebarWidth READ sidebarWidth CONSTANT)

public:
    explicit PreferencesWindowTheme(ThemeManager* manager, QObject* parent = nullptr);
    
    SizeValue* sidebarWidth() const { return m_sidebarWidth; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const PreferencesWindowTheme* other);

signals:
    void changed();

private:
    SizeValue* m_sidebarWidth;
};

#endif // PREFERENCESWINDOWTHEME_H