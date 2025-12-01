#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QGuiApplication>

class Application : public QObject
{
    Q_OBJECT

public:
    explicit Application(QObject *parent = nullptr);
    
    Q_INVOKABLE void quit();

signals:
    void aboutToQuit();
};

#endif // APPLICATION_H