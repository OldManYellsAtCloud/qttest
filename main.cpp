#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QDir>

#include "settings.h"
#include "autocompletionhandler.h"
#include "timetablehandler.h"

#define CONFIG_FILE  "pine_bus.cfg"


int main(int argc, char *argv[])
{

    QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);

    qmlRegisterType<AutoCompletionHandler>("sgy.pine.bus", 1, 0, "AutoCompletionHandler");
    qmlRegisterType<TimetableHandler>("sgy.pine.bus", 1, 0, "TimetableHandler");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/BusTimetable/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    QString cfgPath = QDir::homePath() + QDir::separator() + CONFIG_FILE;
    Settings::getSettings().init(cfgPath);

    TimetableHandler *th = new TimetableHandler();
    th->fetchData("Zürich, Neuaffoltern");

    return app.exec();
}
