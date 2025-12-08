#ifndef KEYMAPMANAGER_H
#define KEYMAPMANAGER_H

#include <QObject>
#include <QVariantMap>
#include <QKeySequence>
#include <QSettings>

class KeymapManager : public QObject
{
    Q_OBJECT

public:
    struct Action {
        QString id;
        QString label;
        QString category;
        QKeySequence defaultShortcut;
        QKeySequence currentShortcut;
    };

    explicit KeymapManager(QObject *parent = nullptr);
    
    Q_INVOKABLE QString getShortcut(const QString &actionId) const;
    Q_INVOKABLE QString getShortcutDisplay(const QString &actionId) const;
    Q_INVOKABLE void setShortcut(const QString &actionId, const QString &shortcut);
    Q_INVOKABLE void resetShortcut(const QString &actionId);
    Q_INVOKABLE void resetAll();
    Q_INVOKABLE bool isShortcutModified(const QString &actionId) const;
    Q_INVOKABLE QString getDefaultShortcut(const QString &actionId) const;
    
    Q_INVOKABLE QVariantList getCategories() const;
    Q_INVOKABLE QVariantList getActionsForCategory(const QString &categoryId) const;
    Q_INVOKABLE QVariantMap getAllActions() const;
    
    // Check if shortcut is already in use
    Q_INVOKABLE QString getActionUsingShortcut(const QString &shortcut) const;
    Q_INVOKABLE bool isShortcutAvailable(const QString &shortcut, const QString &excludeActionId = QString()) const;

signals:
    void shortcutChanged(const QString &actionId);
    void keymapReset();

private:
    void loadDefaults();
    void loadUserKeymaps();
    void saveUserKeymaps();
    
    void registerAction(const QString &category, const QString &id, const QString &label, const QString &shortcut);
    
    QMap<QString, Action> m_actions;
    QMap<QString, QString> m_categoryLabels;
    QSettings *m_settings;
};

#endif // KEYMAPMANAGER_H