#ifndef THEMESPACING_H
#define THEMESPACING_H

#include <QObject>
#include "SizeValue.h"

class ThemeManager;

class MarginSpacing : public QObject {
    Q_OBJECT
    Q_PROPERTY(SizeValue* none READ none CONSTANT)
    Q_PROPERTY(SizeValue* xxxs READ xxxs CONSTANT)
    Q_PROPERTY(SizeValue* xxs READ xxs CONSTANT)
    Q_PROPERTY(SizeValue* xs READ xs CONSTANT)
    Q_PROPERTY(SizeValue* sm READ sm CONSTANT)
    Q_PROPERTY(SizeValue* md READ md CONSTANT)
    Q_PROPERTY(SizeValue* lg READ lg CONSTANT)
    Q_PROPERTY(SizeValue* xl READ xl CONSTANT)
    Q_PROPERTY(SizeValue* xxl READ xxl CONSTANT)
    Q_PROPERTY(SizeValue* xxxl READ xxxl CONSTANT)

public:
    explicit MarginSpacing(ThemeManager* manager, QObject* parent = nullptr);
    
    SizeValue* none() const { return m_none; }
    SizeValue* xxxs() const { return m_xxxs; }
    SizeValue* xxs() const { return m_xxs; }
    SizeValue* xs() const { return m_xs; }
    SizeValue* sm() const { return m_sm; }
    SizeValue* md() const { return m_md; }
    SizeValue* lg() const { return m_lg; }
    SizeValue* xl() const { return m_xl; }
    SizeValue* xxl() const { return m_xxl; }
    SizeValue* xxxl() const { return m_xxxl; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const MarginSpacing* other);

signals:
    void changed();

private:
    SizeValue* m_none;
    SizeValue* m_xxxs;
    SizeValue* m_xxs;
    SizeValue* m_xs;
    SizeValue* m_sm;
    SizeValue* m_md;
    SizeValue* m_lg;
    SizeValue* m_xl;
    SizeValue* m_xxl;
    SizeValue* m_xxxl;
};

class PaddingSpacing : public QObject {
    Q_OBJECT
    Q_PROPERTY(SizeValue* none READ none CONSTANT)
    Q_PROPERTY(SizeValue* xxxs READ xxxs CONSTANT)
    Q_PROPERTY(SizeValue* xxs READ xxs CONSTANT)
    Q_PROPERTY(SizeValue* xs READ xs CONSTANT)
    Q_PROPERTY(SizeValue* sm READ sm CONSTANT)
    Q_PROPERTY(SizeValue* md READ md CONSTANT)
    Q_PROPERTY(SizeValue* lg READ lg CONSTANT)
    Q_PROPERTY(SizeValue* xl READ xl CONSTANT)
    Q_PROPERTY(SizeValue* xxl READ xxl CONSTANT)
    Q_PROPERTY(SizeValue* xxxl READ xxxl CONSTANT)

public:
    explicit PaddingSpacing(ThemeManager* manager, QObject* parent = nullptr);
    
    SizeValue* none() const { return m_none; }
    SizeValue* xxxs() const { return m_xxxs; }
    SizeValue* xxs() const { return m_xxs; }
    SizeValue* xs() const { return m_xs; }
    SizeValue* sm() const { return m_sm; }
    SizeValue* md() const { return m_md; }
    SizeValue* lg() const { return m_lg; }
    SizeValue* xl() const { return m_xl; }
    SizeValue* xxl() const { return m_xxl; }
    SizeValue* xxxl() const { return m_xxxl; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const PaddingSpacing* other);

signals:
    void changed();

private:
    SizeValue* m_none;
    SizeValue* m_xxxs;
    SizeValue* m_xxs;
    SizeValue* m_xs;
    SizeValue* m_sm;
    SizeValue* m_md;
    SizeValue* m_lg;
    SizeValue* m_xl;
    SizeValue* m_xxl;
    SizeValue* m_xxxl;
};

class GapSpacing : public QObject {
    Q_OBJECT
    Q_PROPERTY(SizeValue* xs READ xs CONSTANT)
    Q_PROPERTY(SizeValue* sm READ sm CONSTANT)
    Q_PROPERTY(SizeValue* md READ md CONSTANT)

public:
    explicit GapSpacing(ThemeManager* manager, QObject* parent = nullptr);
    
    SizeValue* xs() const { return m_xs; }
    SizeValue* sm() const { return m_sm; }
    SizeValue* md() const { return m_md; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const GapSpacing* other);

signals:
    void changed();

private:
    SizeValue* m_xs;
    SizeValue* m_sm;
    SizeValue* m_md;
};

class ThemeSpacing : public QObject {
    Q_OBJECT
    Q_PROPERTY(MarginSpacing* margin READ margin CONSTANT)
    Q_PROPERTY(PaddingSpacing* padding READ padding CONSTANT)
    Q_PROPERTY(GapSpacing* gap READ gap CONSTANT)

public:
    explicit ThemeSpacing(ThemeManager* manager, QObject* parent = nullptr);
    
    MarginSpacing* margin() const { return m_margin; }
    PaddingSpacing* padding() const { return m_padding; }
    GapSpacing* gap() const { return m_gap; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const ThemeSpacing* other);

signals:
    void changed();

private:
    MarginSpacing* m_margin;
    PaddingSpacing* m_padding;
    GapSpacing* m_gap;
};

#endif // THEMESPACING_H