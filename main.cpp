#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>

#include "settings.h"
#include "autocompletionhandler.h"

#define CONFIG_FILE  "pine_bus.cfg"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;
    qmlRegisterType<AutoCompletionHandler>("sgy.pine.bus", 1, 0, "AutoCompletionHandler");

    const QUrl url(u"qrc:/BusTimetable/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    QString cfgPath = QDir::homePath() + QDir::separator() + CONFIG_FILE;
    Settings::getSettings().init(cfgPath);

    AutoCompletionHandler *ah = new AutoCompletionHandler();

    //RequestHandler *rh = new RequestHandler();
    //rh->getCompletion("neuaff");
    ah->fetchData("aff");

    return app.exec();
}
