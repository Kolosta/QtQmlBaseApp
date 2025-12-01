#include "TimeModel.h"
#include <QDateTime>

TimeModel::TimeModel(QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout, this, &TimeModel::updateTime);
    m_timer->start(1000); // Update every second
    updateTime(); // Initialize immediately
}

QString TimeModel::currentTime() const
{
    return m_currentTime;
}

void TimeModel::updateTime()
{
    m_currentTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    emit currentTimeChanged();
}