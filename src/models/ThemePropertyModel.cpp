#include "ThemePropertyModel.h"
#include <QMetaObject>
#include <QColor>
#include <QDebug>

ThemePropertyModel::ThemePropertyModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void ThemePropertyModel::setTarget(QObject* obj) {
    if (m_target == obj) return;
    
    beginResetModel();
    m_target = obj;
    m_properties.clear();
    
    if (m_target) {
        const QMetaObject* meta = m_target->metaObject();
        
        // Scanner toutes les propriétés
        for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) {
            QMetaProperty prop = meta->property(i);
            QString name = prop.name();
            
            // Ignorer les propriétés système
            if (name == "objectName") continue;
            
            m_properties.append(prop);
        }
    }
    
    endResetModel();
    emit targetChanged();
}

void ThemePropertyModel::setCategory(const QString& cat) {
    if (m_category == cat) return;
    m_category = cat;
    emit categoryChanged();
}

int ThemePropertyModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid() || !m_target) return 0;
    return m_properties.size();
}

QVariant ThemePropertyModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || !m_target || index.row() >= m_properties.size()) {
        return {};
    }
    
    const QMetaProperty& prop = m_properties[index.row()];
    
    switch(role) {
        case NameRole:
            return prop.name();
            
        case LabelRole:
            return propertyToLabel(prop.name());
            
        case TypeRole:
            return propertyType(prop);
            
        case ValueRole:
            return prop.read(m_target);
            
        case IsModifiedRole:
            return checkIfModified(prop.name());
            
        case OriginalValueRole:
            // TODO: Récupérer la valeur par défaut depuis le thème de base
            return prop.read(m_target);
    }
    
    return {};
}

QHash<int, QByteArray> ThemePropertyModel::roleNames() const {
    return {
        {NameRole, "name"},
        {LabelRole, "label"},
        {TypeRole, "type"},
        {ValueRole, "value"},
        {IsModifiedRole, "isModified"},
        {OriginalValueRole, "originalValue"}
    };
}

void ThemePropertyModel::updateProperty(int row, const QVariant& value) {
    if (row < 0 || row >= m_properties.size() || !m_target) return;
    
    const QMetaProperty& prop = m_properties[row];
    
    if (prop.write(m_target, value)) {
        QModelIndex idx = index(row);
        emit dataChanged(idx, idx);
        
        // Sauvegarder les changements utilisateur
        // (à implémenter selon le contexte - appeler ThemeManager::saveUserOverrides)
    }
}

void ThemePropertyModel::resetProperty(int row) {
    if (row < 0 || row >= m_properties.size() || !m_target) return;
    
    const QMetaProperty& prop = m_properties[row];
    QString propName = prop.name();
    
    // Appeler la méthode reset du composant si elle existe
    QString resetMethod = QString("reset%1%2")
        .arg(propName[0].toUpper())
        .arg(propName.mid(1));
    
    int methodIndex = m_target->metaObject()->indexOfMethod(resetMethod.toLatin1().constData());
    if (methodIndex != -1) {
        QMetaMethod method = m_target->metaObject()->method(methodIndex);
        method.invoke(m_target);
        
        QModelIndex idx = index(row);
        emit dataChanged(idx, idx);
    }
}

bool ThemePropertyModel::isPropertyModified(int row) const {
    if (row < 0 || row >= m_properties.size() || !m_target) return false;
    
    const QMetaProperty& prop = m_properties[row];
    return checkIfModified(prop.name());
}

QString ThemePropertyModel::propertyToLabel(const QString& propName) const {
    // Convertir camelCase en "Title Case"
    // Ex: backgroundPrimary -> "Background Primary"
    QString result;
    bool wasLower = false;
    
    for (int i = 0; i < propName.length(); ++i) {
        QChar c = propName[i];
        
        if (i == 0) {
            result += c.toUpper();
            wasLower = c.isLower();
        } else {
            if (c.isUpper() && wasLower) {
                result += ' ';
            }
            result += c;
            wasLower = c.isLower();
        }
    }
    
    return result;
}

QString ThemePropertyModel::propertyType(const QMetaProperty& prop) const {
    QString typeName = prop.typeName();
    
    if (typeName == "QColor") return "color";
    if (typeName == "int") return "int";
    if (typeName == "qreal" || typeName == "double") return "real";
    if (typeName == "bool") return "bool";
    if (typeName == "QString") return "string";
    
    return "unknown";
}

bool ThemePropertyModel::checkIfModified(const QString& propName) const {
    if (!m_target) return false;
    
    // Vérifier si le composant a une méthode `isXxxOverridden()`
    QString checkMethod = QString("is%1%2Overridden")
        .arg(propName[0].toUpper())
        .arg(propName.mid(1));
    
    int methodIndex = m_target->metaObject()->indexOfMethod(checkMethod.toLatin1().constData());
    if (methodIndex != -1) {
        QMetaMethod method = m_target->metaObject()->method(methodIndex);
        bool result = false;
        method.invoke(m_target, Q_RETURN_ARG(bool, result));
        return result;
    }
    
    return false;
}