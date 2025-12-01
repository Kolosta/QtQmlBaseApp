#include "Application.h"
#include <QCoreApplication>

Application::Application(QObject *parent)
    : QObject(parent)
{
}

void Application::quit()
{
    emit aboutToQuit();
    QCoreApplication::quit();
}