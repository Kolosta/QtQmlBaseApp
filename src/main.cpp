#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QQuickStyle>

#include "core/Application.h"
#include "core/ThemeManager.h"
#include "core/PreferencesManager.h"
#include "models/TimeModel.h"

int main(int argc, char *argv[])
{
    // IMPORTANT: Définir le style AVANT de créer QGuiApplication
    QQuickStyle::setStyle("Basic");
    
    QGuiApplication app(argc, argv);
    
    // Configuration de l'application
    app.setOrganizationName("YourCompany");
    app.setOrganizationDomain("yourcompany.com");
    app.setApplicationName("QtQmlBaseApp");
    app.setApplicationVersion("0.1.0");
    app.setWindowIcon(QIcon(":/resources/icons/app_icon.svg"));
    
    // Création des singletons
    Application appManager;
    ThemeManager themeManager;
    PreferencesManager preferencesManager;
    TimeModel timeModel;
    
    // Configuration du moteur QML
    QQmlApplicationEngine engine;
    
    // Enregistrement des types C++ pour QML
    qmlRegisterSingletonInstance("QtQmlBaseApp.Core", 1, 0, "Application", &appManager);
    qmlRegisterSingletonInstance("QtQmlBaseApp.Core", 1, 0, "ThemeManager", &themeManager);
    qmlRegisterSingletonInstance("QtQmlBaseApp.Core", 1, 0, "PreferencesManager", &preferencesManager);
    qmlRegisterSingletonInstance("QtQmlBaseApp.Models", 1, 0, "TimeModel", &timeModel);
    
    // Gestion des erreurs de création d'objets
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
    );
    
    // Chargement du QML principal
    engine.loadFromModule("QtQmlBaseApp", "Main");
    
    return app.exec();
}