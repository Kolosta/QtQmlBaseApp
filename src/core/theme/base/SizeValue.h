#ifndef SIZEVALUE_H
#define SIZEVALUE_H

#include <QObject>
#include <cmath>

class ThemeManager;

class SizeValue : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY changed)
    Q_PROPERTY(int scaled READ scaled NOTIFY changed)

public:
    explicit SizeValue(int baseValue, ThemeManager* manager, QObject* parent = nullptr)
        : QObject(parent), m_baseValue(baseValue), m_manager(manager) {}
    
    int value() const { return m_baseValue; }
    void setValue(int v) { m_baseValue = v; emit changed(); }
    
    int scaled() const;
    
    void loadFromJson(int value) { m_baseValue = value; emit changed(); }
    int toJson() const { return m_baseValue; }
    void copyFrom(const SizeValue* other) { m_baseValue = other->m_baseValue; emit changed(); }

signals:
    void changed();

private:
    int m_baseValue;
    ThemeManager* m_manager;
};

#endif // SIZEVALUE_H