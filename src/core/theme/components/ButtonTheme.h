#ifndef BUTTONTHEME_H
#define BUTTONTHEME_H

#include <QObject>
#include "../base/SizeValue.h"

class ThemeManager;

class ButtonTheme : public QObject {
    Q_OBJECT
    Q_PROPERTY(SizeValue* minWidth READ minWidth CONSTANT)
    Q_PROPERTY(SizeValue* minHeight READ minHeight CONSTANT)

public:
    explicit ButtonTheme(ThemeManager* manager, QObject* parent = nullptr);
    
    SizeValue* minWidth() const { return m_minWidth; }
    SizeValue* minHeight() const { return m_minHeight; }
    
    void loadFromJson(const QJsonObject& json);
    QJsonObject toJson() const;
    void copyFrom(const ButtonTheme* other);

signals:
    void changed();

private:
    SizeValue* m_minWidth;
    SizeValue* m_minHeight;
};

#endif // BUTTONTHEME_H