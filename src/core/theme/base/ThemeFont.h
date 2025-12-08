#ifndef THEMEFONT_H
#define THEMEFONT_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include "SizeValue.h"

class ThemeManager;

class FontFamily : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString primary MEMBER m_primary NOTIFY changed)
    Q_PROPERTY(QString secondary MEMBER m_secondary NOTIFY changed)
    Q_PROPERTY(QString mono MEMBER m_mono NOTIFY changed)

public:
    explicit FontFamily(QObject* parent = nullptr)
        : QObject(parent)
        , m_primary("Segoe UI")
        , m_secondary("Arial")
        , m_mono("Consolas")
    {}
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const FontFamily* other);

signals:
    void changed();

private:
    QString m_primary;
    QString m_secondary;
    QString m_mono;
};

// class FontSize : public QObject {
//     Q_OBJECT

// public:
//     class TextSizes : public QObject {
//         Q_OBJECT
//         Q_PROPERTY(SizeValue* xs READ xs CONSTANT)
//         Q_PROPERTY(SizeValue* sm READ sm CONSTANT)
//         Q_PROPERTY(SizeValue* md READ md CONSTANT)
//         Q_PROPERTY(SizeValue* lg READ lg CONSTANT)

//     public:
//         explicit TextSizes(ThemeManager* manager, QObject* parent = nullptr);
        
//         SizeValue* xs() const { return m_xs; }
//         SizeValue* sm() const { return m_sm; }
//         SizeValue* md() const { return m_md; }
//         SizeValue* lg() const { return m_lg; }
        
//         void loadFromJson(const QJsonObject& json);
//         QJsonObject toJson() const;
//         void copyFrom(const TextSizes* other);

//     signals:
//         void changed();

//     private:
//         SizeValue* m_xs;
//         SizeValue* m_sm;
//         SizeValue* m_md;
//         SizeValue* m_lg;
//     };
    
//     Q_PROPERTY(TextSizes* text READ text CONSTANT)
//     Q_PROPERTY(SizeValue* heading1 READ heading1 CONSTANT)
//     Q_PROPERTY(SizeValue* heading2 READ heading2 CONSTANT)
//     Q_PROPERTY(SizeValue* heading3 READ heading3 CONSTANT)

// public:
//     explicit FontSize(ThemeManager* manager, QObject* parent = nullptr);
    
//     TextSizes* text() const { return m_text; }
//     SizeValue* heading1() const { return m_heading1; }
//     SizeValue* heading2() const { return m_heading2; }
//     SizeValue* heading3() const { return m_heading3; }
    
//     void loadFromJson(const QJsonObject& json);
//     QJsonObject toJson() const;
//     void copyFrom(const FontSize* other);

// signals:
//     void changed();

// private:
//     TextSizes* m_text;
//     SizeValue* m_heading1;
//     SizeValue* m_heading2;
//     SizeValue* m_heading3;
// };

class TextSizes : public QObject {
    Q_OBJECT
    Q_PROPERTY(SizeValue* xs READ xs CONSTANT)
    Q_PROPERTY(SizeValue* sm READ sm CONSTANT)
    Q_PROPERTY(SizeValue* md READ md CONSTANT)
    Q_PROPERTY(SizeValue* lg READ lg CONSTANT)

public:
    explicit TextSizes(ThemeManager* manager, QObject* parent = nullptr);
    
    SizeValue* xs() const { return m_xs; }
    SizeValue* sm() const { return m_sm; }
    SizeValue* md() const { return m_md; }
    SizeValue* lg() const { return m_lg; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const TextSizes* other);

signals:
    void changed();

private:
    SizeValue* m_xs;
    SizeValue* m_sm;
    SizeValue* m_md;
    SizeValue* m_lg;
};


class FontSize : public QObject {
    Q_OBJECT
    
    Q_PROPERTY(TextSizes* text READ text CONSTANT)
    Q_PROPERTY(SizeValue* heading1 READ heading1 CONSTANT)
    Q_PROPERTY(SizeValue* heading2 READ heading2 CONSTANT)
    Q_PROPERTY(SizeValue* heading3 READ heading3 CONSTANT)

public:
    explicit FontSize(ThemeManager* manager, QObject* parent = nullptr);
    
    TextSizes* text() const { return m_text; }
    SizeValue* heading1() const { return m_heading1; }
    SizeValue* heading2() const { return m_heading2; }
    SizeValue* heading3() const { return m_heading3; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const FontSize* other);

signals:
    void changed();

private:
    TextSizes* m_text;
    SizeValue* m_heading1;
    SizeValue* m_heading2;
    SizeValue* m_heading3;
};

class FontWeight : public QObject {
    Q_OBJECT
    Q_PROPERTY(int light MEMBER m_light CONSTANT)
    Q_PROPERTY(int regular MEMBER m_regular CONSTANT)
    Q_PROPERTY(int medium MEMBER m_medium CONSTANT)
    Q_PROPERTY(int bold MEMBER m_bold CONSTANT)

public:
    explicit FontWeight(QObject* parent = nullptr)
        : QObject(parent)
        , m_light(300)
        , m_regular(400)
        , m_medium(500)
        , m_bold(700)
    {}
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;

private:
    int m_light;
    int m_regular;
    int m_medium;
    int m_bold;
};

class ThemeFont : public QObject {
    Q_OBJECT
    Q_PROPERTY(FontFamily* family READ family CONSTANT)
    Q_PROPERTY(FontSize* size READ size CONSTANT)
    Q_PROPERTY(FontWeight* weight READ weight CONSTANT)

public:
    explicit ThemeFont(ThemeManager* manager, QObject* parent = nullptr);
    
    FontFamily* family() const { return m_family; }
    FontSize* size() const { return m_size; }
    FontWeight* weight() const { return m_weight; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const ThemeFont* other);

signals:
    void changed();

private:
    FontFamily* m_family;
    FontSize* m_size;
    FontWeight* m_weight;
};

#endif // THEMEFONT_H