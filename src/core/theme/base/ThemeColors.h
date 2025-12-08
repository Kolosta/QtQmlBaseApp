#ifndef THEMECOLORS_H
#define THEMECOLORS_H

#include <QObject>
#include "ColorState.h"
#include "SimpleColorState.h"

// Couleurs de texte
class TextColors : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(SimpleColorState* primary READ primary CONSTANT)
    Q_PROPERTY(SimpleColorState* secondary READ secondary CONSTANT)
    Q_PROPERTY(SimpleColorState* disabled READ disabled CONSTANT)
    Q_PROPERTY(SimpleColorState* onPrimary READ onPrimary CONSTANT)
    Q_PROPERTY(SimpleColorState* onSecondary READ onSecondary CONSTANT)
    Q_PROPERTY(SimpleColorState* onBackground READ onBackground CONSTANT)

public:
    explicit TextColors(QObject* parent = nullptr);
    
    SimpleColorState* primary() const { return m_primary; }
    SimpleColorState* secondary() const { return m_secondary; }
    SimpleColorState* disabled() const { return m_disabled; }
    SimpleColorState* onPrimary() const { return m_onPrimary; }
    SimpleColorState* onSecondary() const { return m_onSecondary; }
    SimpleColorState* onBackground() const { return m_onBackground; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const TextColors* other);

signals:
    void changed();

private:
    SimpleColorState* m_primary;
    SimpleColorState* m_secondary;
    SimpleColorState* m_disabled;
    SimpleColorState* m_onPrimary;
    SimpleColorState* m_onSecondary;
    SimpleColorState* m_onBackground;
};

// Couleurs de background
class BackgroundColors : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(SimpleColorState* primary READ primary CONSTANT)
    Q_PROPERTY(SimpleColorState* secondary READ secondary CONSTANT)
    Q_PROPERTY(SimpleColorState* tertiary READ tertiary CONSTANT)

public:
    explicit BackgroundColors(QObject* parent = nullptr);
    
    SimpleColorState* primary() const { return m_primary; }
    SimpleColorState* secondary() const { return m_secondary; }
    SimpleColorState* tertiary() const { return m_tertiary; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const BackgroundColors* other);

signals:
    void changed();

private:
    SimpleColorState* m_primary;
    SimpleColorState* m_secondary;
    SimpleColorState* m_tertiary;
};

// Couleurs de surface
class SurfaceColors : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(SimpleColorState* primary READ primary CONSTANT)
    Q_PROPERTY(SimpleColorState* secondary READ secondary CONSTANT)
    Q_PROPERTY(ColorState* hover READ hover CONSTANT)
    Q_PROPERTY(ColorState* active READ active CONSTANT)
    Q_PROPERTY(SimpleColorState* disabled READ disabled CONSTANT)

public:
    explicit SurfaceColors(QObject* parent = nullptr);
    
    SimpleColorState* primary() const { return m_primary; }
    SimpleColorState* secondary() const { return m_secondary; }
    ColorState* hover() const { return m_hover; }
    ColorState* active() const { return m_active; }
    SimpleColorState* disabled() const { return m_disabled; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const SurfaceColors* other);

signals:
    void changed();

private:
    SimpleColorState* m_primary;
    SimpleColorState* m_secondary;
    ColorState* m_hover;
    ColorState* m_active;
    SimpleColorState* m_disabled;
};

// Couleurs de bordure
class BorderColors : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(SimpleColorState* defaultColor READ defaultColor CONSTANT)
    Q_PROPERTY(SimpleColorState* focus READ focus CONSTANT)
    Q_PROPERTY(SimpleColorState* active READ active CONSTANT)
    Q_PROPERTY(SimpleColorState* pressed READ pressed CONSTANT)
    Q_PROPERTY(SimpleColorState* disabled READ disabled CONSTANT)

public:
    explicit BorderColors(QObject* parent = nullptr);
    
    SimpleColorState* defaultColor() const { return m_default; }
    SimpleColorState* focus() const { return m_focus; }
    SimpleColorState* active() const { return m_active; }
    SimpleColorState* pressed() const { return m_pressed; }
    SimpleColorState* disabled() const { return m_disabled; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const BorderColors* other);

signals:
    void changed();

private:
    SimpleColorState* m_default;
    SimpleColorState* m_focus;
    SimpleColorState* m_active;
    SimpleColorState* m_pressed;
    SimpleColorState* m_disabled;
};

// Classe principale des couleurs
class ThemeColors : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(ColorState* primary READ primary CONSTANT)
    Q_PROPERTY(ColorState* secondary READ secondary CONSTANT)
    Q_PROPERTY(ColorState* accent READ accent CONSTANT)
    Q_PROPERTY(ColorState* success READ success CONSTANT)
    Q_PROPERTY(ColorState* warning READ warning CONSTANT)
    Q_PROPERTY(ColorState* error READ error CONSTANT)
    Q_PROPERTY(ColorState* info READ info CONSTANT)
    
    Q_PROPERTY(TextColors* text READ text CONSTANT)
    Q_PROPERTY(BackgroundColors* background READ background CONSTANT)
    Q_PROPERTY(SurfaceColors* surface READ surface CONSTANT)
    Q_PROPERTY(BorderColors* border READ border CONSTANT)

public:
    explicit ThemeColors(QObject* parent = nullptr);
    
    ColorState* primary() const { return m_primary; }
    ColorState* secondary() const { return m_secondary; }
    ColorState* accent() const { return m_accent; }
    ColorState* success() const { return m_success; }
    ColorState* warning() const { return m_warning; }
    ColorState* error() const { return m_error; }
    ColorState* info() const { return m_info; }
    
    TextColors* text() const { return m_text; }
    BackgroundColors* background() const { return m_background; }
    SurfaceColors* surface() const { return m_surface; }
    BorderColors* border() const { return m_border; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const ThemeColors* other);
    void initDefaults(); // Thème Dark par défaut

signals:
    void changed();

private:
    ColorState* m_primary;
    ColorState* m_secondary;
    ColorState* m_accent;
    ColorState* m_success;
    ColorState* m_warning;
    ColorState* m_error;
    ColorState* m_info;
    
    TextColors* m_text;
    BackgroundColors* m_background;
    SurfaceColors* m_surface;
    BorderColors* m_border;
};

#endif // THEMECOLORS_H