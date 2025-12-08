#ifndef THEMESIZE_H
#define THEMESIZE_H

#include <QObject>
#include "SizeValue.h"

class ThemeManager;

class IconSize : public QObject {
    Q_OBJECT
    Q_PROPERTY(SizeValue* sm READ sm CONSTANT)
    Q_PROPERTY(SizeValue* md READ md CONSTANT)
    Q_PROPERTY(SizeValue* lg READ lg CONSTANT)

public:
    explicit IconSize(ThemeManager* manager, QObject* parent = nullptr);
    
    SizeValue* sm() const { return m_sm; }
    SizeValue* md() const { return m_md; }
    SizeValue* lg() const { return m_lg; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const IconSize* other);

signals:
    void changed();

private:
    SizeValue* m_sm;
    SizeValue* m_md;
    SizeValue* m_lg;
};

class ThemeSize : public QObject {
    Q_OBJECT
    Q_PROPERTY(IconSize* icon READ icon CONSTANT)

public:
    explicit ThemeSize(ThemeManager* manager, QObject* parent = nullptr);
    
    IconSize* icon() const { return m_icon; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const ThemeSize* other);

signals:
    void changed();

private:
    IconSize* m_icon;
};

#endif // THEMESIZE_H