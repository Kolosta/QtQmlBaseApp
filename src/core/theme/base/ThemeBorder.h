#ifndef THEMEBORDER_H
#define THEMEBORDER_H

#include <QObject>
#include "SizeValue.h"

class ThemeManager;

class BorderWidth : public QObject {
    Q_OBJECT
    Q_PROPERTY(SizeValue* thin READ thin CONSTANT)
    Q_PROPERTY(SizeValue* md READ md CONSTANT)
    Q_PROPERTY(SizeValue* thick READ thick CONSTANT)

public:
    explicit BorderWidth(ThemeManager* manager, QObject* parent = nullptr);
    
    SizeValue* thin() const { return m_thin; }
    SizeValue* md() const { return m_md; }
    SizeValue* thick() const { return m_thick; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const BorderWidth* other);

signals:
    void changed();

private:
    SizeValue* m_thin;
    SizeValue* m_md;
    SizeValue* m_thick;
};

class BorderRadius : public QObject {
    Q_OBJECT
    Q_PROPERTY(SizeValue* xs READ xs CONSTANT)
    Q_PROPERTY(SizeValue* sm READ sm CONSTANT)
    Q_PROPERTY(SizeValue* md READ md CONSTANT)
    Q_PROPERTY(SizeValue* lg READ lg CONSTANT)
    Q_PROPERTY(SizeValue* full READ full CONSTANT)

public:
    explicit BorderRadius(ThemeManager* manager, QObject* parent = nullptr);
    
    SizeValue* xs() const { return m_xs; }
    SizeValue* sm() const { return m_sm; }
    SizeValue* md() const { return m_md; }
    SizeValue* lg() const { return m_lg; }
    SizeValue* full() const { return m_full; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const BorderRadius* other);

signals:
    void changed();

private:
    SizeValue* m_xs;
    SizeValue* m_sm;
    SizeValue* m_md;
    SizeValue* m_lg;
    SizeValue* m_full;
};

class ThemeBorder : public QObject {
    Q_OBJECT
    Q_PROPERTY(BorderWidth* width READ width CONSTANT)
    Q_PROPERTY(BorderRadius* radius READ radius CONSTANT)

public:
    explicit ThemeBorder(ThemeManager* manager, QObject* parent = nullptr);
    
    BorderWidth* width() const { return m_width; }
    BorderRadius* radius() const { return m_radius; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const ThemeBorder* other);

signals:
    void changed();

private:
    BorderWidth* m_width;
    BorderRadius* m_radius;
};

#endif // THEMEBORDER_H