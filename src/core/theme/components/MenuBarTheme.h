#ifndef MENUBARTHEME_H
#define MENUBARTHEME_H

#include <QObject>
#include "../base/SizeValue.h"

class ThemeManager;

class MenuBarTheme : public QObject {
    Q_OBJECT
    Q_PROPERTY(SizeValue* height READ height CONSTANT)

public:
    explicit MenuBarTheme(ThemeManager* manager, QObject* parent = nullptr);
    
    SizeValue* height() const { return m_height; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const MenuBarTheme* other);

signals:
    void changed();

private:
    SizeValue* m_height;
};

#endif // MENUBARTHEME_H