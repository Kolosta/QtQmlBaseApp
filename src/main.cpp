#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QIcon>

#include "core/Application.h"
#include "core/ThemeManager.h"
// #include "core/PreferencesManager.h"
#include "core/KeymapManager.h"
#include "models/TimeModel.h"
#include "models/ThemePropertyModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    // Set application metadata
    app.setOrganizationName("Koebi");
    app.setOrganizationDomain("yourcompany.com");
    app.setApplicationName("QtQmlBaseApp");
    app.setApplicationVersion("1.0.0");
    
    // Set application icon
    app.setWindowIcon(QIcon(":/resources/icons/app_icon.svg"));
    
    QQuickStyle::setStyle("Basic");
    
    QQmlApplicationEngine engine;
    
    // Create and register singleton instances
    Application *application = new Application(&app);
    // ThemeManager *themeManager = new ThemeManager(&app);
    // PreferencesManager *preferencesManager = new PreferencesManager(&app);
    KeymapManager *keymapManager = new KeymapManager(&app);
    TimeModel *timeModel = new TimeModel(&app);

    // Exposer le ThemeManager comme Singleton au contexte QML
    // Enregistrement des types C++
    ThemeManager& themeManager = ThemeManager::instance();
    // Exposition au contexte QML (inutile ? car singleton)
    // engine.rootContext()->setContextProperty("ThemeManager", &themeManager);

    // Enregistrer les types C++ pour QML
    // qmlRegisterType<ThemePropertyModel>("QtQmlBaseApp.Core", 1, 0, "ThemePropertyModel");
    
    // Register types
    qmlRegisterSingletonInstance("QtQmlBaseApp.Core", 1, 0, "Application", application);
    qmlRegisterSingletonInstance("QtQmlBaseApp.Core", 1, 0, "ThemeManager", &themeManager); 
    // qmlRegisterSingletonInstance("QtQmlBaseApp.Core", 1, 0, "PreferencesManager", preferencesManager);
    qmlRegisterSingletonInstance("QtQmlBaseApp.Core", 1, 0, "KeymapManager", keymapManager);
    qmlRegisterSingletonInstance("QtQmlBaseApp.Models", 1, 0, "TimeModel", timeModel);
    
    // Load main QML
    const QUrl url(QStringLiteral("qrc:/qt/qml/QtQmlBaseApp/qml/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    
    engine.load(url);
    
    return app.exec();
}