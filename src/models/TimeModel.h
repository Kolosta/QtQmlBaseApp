#ifndef TIMEMODEL_H
#define TIMEMODEL_H

#include <QObject>
#include <QTimer>
#include <QString>

class TimeModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentTime READ currentTime NOTIFY currentTimeChanged)

public:
    explicit TimeModel(QObject *parent = nullptr);
    
    QString currentTime() const;

signals:
    void currentTimeChanged();

private slots:
    void updateTime();

private:
    QTimer *m_timer;
    QString m_currentTime;
};

#endif // TIMEMODEL_H