#ifndef THEMEPROPERTYMODEL_H
#define THEMEPROPERTYMODEL_H

#include <QAbstractListModel>
#include <QMetaProperty>
#include <QVector>

class ThemePropertyModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QObject* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        LabelRole,       // Nom affiché (ex: "Background Primary")
        TypeRole,        // "color", "int", "bool"
        ValueRole,
        IsModifiedRole,  // Si c'est un override
        OriginalValueRole
    };

    explicit ThemePropertyModel(QObject *parent = nullptr);
    
    QObject* target() const { return m_target; }
    void setTarget(QObject* obj);
    
    QString category() const { return m_category; }
    void setCategory(const QString& cat);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    
    // Méthode appelable depuis QML pour mettre à jour une propriété
    Q_INVOKABLE void updateProperty(int row, const QVariant& value);
    
    // Reset une propriété à sa valeur par défaut
    Q_INVOKABLE void resetProperty(int row);
    
    // Vérifier si modifié (pour composants avec std::optional)
    Q_INVOKABLE bool isPropertyModified(int row) const;

signals:
    void targetChanged();
    void categoryChanged();

private:
    QString propertyToLabel(const QString& propName) const;
    QString propertyType(const QMetaProperty& prop) const;
    bool checkIfModified(const QString& propName) const;
    
    QObject* m_target = nullptr;
    QString m_category;
    QVector<QMetaProperty> m_properties;
};

#endif // THEMEPROPERTYMODEL_H