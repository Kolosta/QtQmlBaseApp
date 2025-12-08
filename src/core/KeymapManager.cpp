#include "KeymapManager.h"
#include <QDebug>

KeymapManager::KeymapManager(QObject *parent)
    : QObject(parent)
    , m_settings(new QSettings("YourCompany", "QtQmlBaseApp", this))
{
    loadDefaults();
    loadUserKeymaps();
}

void KeymapManager::loadDefaults()
{
    // Categories
    m_categoryLabels["file"] = "File";
    m_categoryLabels["edit"] = "Edit";
    m_categoryLabels["view"] = "View";
    m_categoryLabels["window"] = "Window";
    m_categoryLabels["help"] = "Help";
    
    // File actions
    registerAction("file", "file.new", "New", "Ctrl+N");
    registerAction("file", "file.open", "Open", "Ctrl+O");
    registerAction("file", "file.save", "Save", "Ctrl+S");
    registerAction("file", "file.saveAs", "Save As", "Ctrl+Shift+S");
    registerAction("file", "file.close", "Close", "Ctrl+W");
    registerAction("file", "file.quit", "Quit", "Ctrl+Q");
    
    // Edit actions
    registerAction("edit", "edit.undo", "Undo", "Ctrl+Z");
    registerAction("edit", "edit.redo", "Redo", "Ctrl+Shift+Z");
    registerAction("edit", "edit.cut", "Cut", "Ctrl+X");
    registerAction("edit", "edit.copy", "Copy", "Ctrl+C");
    registerAction("edit", "edit.paste", "Paste", "Ctrl+V");
    registerAction("edit", "edit.selectAll", "Select All", "Ctrl+A");
    registerAction("edit", "edit.preferences", "Preferences", "Ctrl+,");
    
    // View actions
    registerAction("view", "view.zoomIn", "Zoom In", "Ctrl++");
    registerAction("view", "view.zoomOut", "Zoom Out", "Ctrl+-");
    registerAction("view", "view.zoomReset", "Reset Zoom", "Ctrl+0");
    registerAction("view", "view.fullscreen", "Toggle Fullscreen", "F11");
    
    // Window actions
    registerAction("window", "window.minimize", "Minimize", "");
    registerAction("window", "window.maximize", "Maximize", "");
    registerAction("window", "window.close", "Close Window", "Alt+F4");
    
    // Help actions
    registerAction("help", "help.documentation", "Documentation", "F1");
    registerAction("help", "help.about", "About", "");
}

void KeymapManager::registerAction(const QString &category, const QString &id, const QString &label, const QString &shortcut)
{
    Action action;
    action.id = id;
    action.label = label;
    action.category = category;
    action.defaultShortcut = QKeySequence(shortcut);
    action.currentShortcut = QKeySequence(shortcut);
    
    m_actions[id] = action;
}

void KeymapManager::loadUserKeymaps()
{
    m_settings->beginGroup("keymaps");
    
    for (auto it = m_actions.begin(); it != m_actions.end(); ++it) {
        QString savedShortcut = m_settings->value(it.key()).toString();
        if (!savedShortcut.isEmpty()) {
            it->currentShortcut = QKeySequence(savedShortcut);
        }
    }
    
    m_settings->endGroup();
}

void KeymapManager::saveUserKeymaps()
{
    m_settings->beginGroup("keymaps");
    
    for (auto it = m_actions.constBegin(); it != m_actions.constEnd(); ++it) {
        if (it->currentShortcut != it->defaultShortcut) {
            m_settings->setValue(it.key(), it->currentShortcut.toString());
        } else {
            m_settings->remove(it.key());
        }
    }
    
    m_settings->endGroup();
    m_settings->sync();
}

QString KeymapManager::getShortcut(const QString &actionId) const
{
    if (!m_actions.contains(actionId))
        return QString();
    
    return m_actions[actionId].currentShortcut.toString();
}

QString KeymapManager::getShortcutDisplay(const QString &actionId) const
{
    if (!m_actions.contains(actionId))
        return QString();
    
    return m_actions[actionId].currentShortcut.toString(QKeySequence::NativeText);
}

void KeymapManager::setShortcut(const QString &actionId, const QString &shortcut)
{
    if (!m_actions.contains(actionId))
        return;
    
    m_actions[actionId].currentShortcut = QKeySequence(shortcut);
    saveUserKeymaps();
    emit shortcutChanged(actionId);
}

void KeymapManager::resetShortcut(const QString &actionId)
{
    if (!m_actions.contains(actionId))
        return;
    
    m_actions[actionId].currentShortcut = m_actions[actionId].defaultShortcut;
    saveUserKeymaps();
    emit shortcutChanged(actionId);
}

void KeymapManager::resetAll()
{
    for (auto it = m_actions.begin(); it != m_actions.end(); ++it) {
        it->currentShortcut = it->defaultShortcut;
    }
    
    saveUserKeymaps();
    emit keymapReset();
}

bool KeymapManager::isShortcutModified(const QString &actionId) const
{
    if (!m_actions.contains(actionId))
        return false;
    
    return m_actions[actionId].currentShortcut != m_actions[actionId].defaultShortcut;
}

QString KeymapManager::getDefaultShortcut(const QString &actionId) const
{
    if (!m_actions.contains(actionId))
        return QString();
    
    return m_actions[actionId].defaultShortcut.toString();
}

QVariantList KeymapManager::getCategories() const
{
    QVariantList result;
    
    for (auto it = m_categoryLabels.constBegin(); it != m_categoryLabels.constEnd(); ++it) {
        QVariantMap category;
        category["id"] = it.key();
        category["label"] = it.value();
        result.append(category);
    }
    
    return result;
}

QVariantList KeymapManager::getActionsForCategory(const QString &categoryId) const
{
    QVariantList result;
    
    for (auto it = m_actions.constBegin(); it != m_actions.constEnd(); ++it) {
        if (it->category == categoryId) {
            QVariantMap action;
            action["id"] = it->id;
            action["label"] = it->label;
            action["shortcut"] = it->currentShortcut.toString();
            action["defaultShortcut"] = it->defaultShortcut.toString();
            action["isModified"] = (it->currentShortcut != it->defaultShortcut);
            result.append(action);
        }
    }
    
    return result;
}

QVariantMap KeymapManager::getAllActions() const
{
    QVariantMap result;
    
    for (auto it = m_actions.constBegin(); it != m_actions.constEnd(); ++it) {
        QVariantMap action;
        action["id"] = it->id;
        action["label"] = it->label;
        action["category"] = it->category;
        action["shortcut"] = it->currentShortcut.toString();
        action["defaultShortcut"] = it->defaultShortcut.toString();
        action["isModified"] = (it->currentShortcut != it->defaultShortcut);
        result[it.key()] = action;
    }
    
    return result;
}

QString KeymapManager::getActionUsingShortcut(const QString &shortcut) const
{
    QKeySequence seq(shortcut);
    
    for (auto it = m_actions.constBegin(); it != m_actions.constEnd(); ++it) {
        if (it->currentShortcut == seq) {
            return it.key();
        }
    }
    
    return QString();
}

bool KeymapManager::isShortcutAvailable(const QString &shortcut, const QString &excludeActionId) const
{
    if (shortcut.isEmpty())
        return true;
    
    QKeySequence seq(shortcut);
    
    for (auto it = m_actions.constBegin(); it != m_actions.constEnd(); ++it) {
        if (it.key() == excludeActionId)
            continue;
        
        if (it->currentShortcut == seq)
            return false;
    }
    
    return true;
}