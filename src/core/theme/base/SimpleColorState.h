#ifndef SIMPLECOLORSTATE_H
#define SIMPLECOLORSTATE_H

#include <QObject>
#include <QColor>
#include <QJsonObject>

class SimpleColorState : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(QColor defaultColor READ defaultColor WRITE setDefaultColor NOTIFY changed)

public:
    explicit SimpleColorState(QObject* parent = nullptr, QColor def = QColor())
        : QObject(parent), m_default(def) {}
    
    QColor defaultColor() const { return m_default; }
    void setDefaultColor(const QColor& c) { m_default = c; emit changed(); }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const SimpleColorState* other);

signals:
    void changed();

private:
    QColor m_default;
};

#endif // SIMPLECOLORSTATE_H