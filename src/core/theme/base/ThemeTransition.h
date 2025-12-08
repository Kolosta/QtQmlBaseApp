#ifndef THEMETRANSITION_H
#define THEMETRANSITION_H

#include <QObject>

class TransitionDuration : public QObject {
    Q_OBJECT
    Q_PROPERTY(int fast MEMBER m_fast CONSTANT)
    Q_PROPERTY(int md MEMBER m_md CONSTANT)
    Q_PROPERTY(int slow MEMBER m_slow CONSTANT)

public:
    explicit TransitionDuration(QObject* parent = nullptr)
        : QObject(parent)
        , m_fast(100)
        , m_md(200)
        , m_slow(300)
    {}
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;

private:
    int m_fast;
    int m_md;
    int m_slow;
};

class ThemeTransition : public QObject {
    Q_OBJECT
    Q_PROPERTY(TransitionDuration* duration READ duration CONSTANT)

public:
    explicit ThemeTransition(QObject* parent = nullptr);
    
    TransitionDuration* duration() const { return m_duration; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const ThemeTransition* other);

signals:
    void changed();

private:
    TransitionDuration* m_duration;
};

#endif // THEMETRANSITION_H