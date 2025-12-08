#ifndef COLORSTATE_H
#define COLORSTATE_H

#include <QObject>
#include <QColor>
#include <QJsonObject>

// Représente un ensemble d'états pour une couleur (default, hover, active, etc.)
class ColorState : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(QColor defaultColor READ defaultColor WRITE setDefaultColor NOTIFY changed)
    Q_PROPERTY(QColor hover READ hover WRITE setHover NOTIFY changed)
    Q_PROPERTY(QColor active READ active WRITE setActive NOTIFY changed)
    Q_PROPERTY(QColor disabled READ disabled WRITE setDisabled NOTIFY changed)
    Q_PROPERTY(QColor pressed READ pressed WRITE setPressed NOTIFY changed)

public:
    explicit ColorState(QObject* parent = nullptr,
                       QColor def = QColor(),
                       QColor hov = QColor(),
                       QColor act = QColor(),
                       QColor dis = QColor(),
                       QColor prs = QColor())
        : QObject(parent)
        , m_default(def)
        , m_hover(hov.isValid() ? hov : def)
        , m_active(act.isValid() ? act : def)
        , m_disabled(dis.isValid() ? dis : def)
        , m_pressed(prs.isValid() ? prs : def)
    {}
    
    QColor defaultColor() const { return m_default; }
    void setDefaultColor(const QColor& c) { m_default = c; emit changed(); }
    
    QColor hover() const { return m_hover; }
    void setHover(const QColor& c) { m_hover = c; emit changed(); }
    
    QColor active() const { return m_active; }
    void setActive(const QColor& c) { m_active = c; emit changed(); }
    
    QColor disabled() const { return m_disabled; }
    void setDisabled(const QColor& c) { m_disabled = c; emit changed(); }
    
    QColor pressed() const { return m_pressed; }
    void setPressed(const QColor& c) { m_pressed = c; emit changed(); }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const ColorState* other);

signals:
    void changed();

private:
    QColor m_default;
    QColor m_hover;
    QColor m_active;
    QColor m_disabled;
    QColor m_pressed;
};

#endif // COLORSTATE_H