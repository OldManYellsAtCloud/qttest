#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>

#include "settings.h"
#include "requesthandler.h"



int main(int argc, char *argv[])
{




    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/BusTimetable/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);


    QString cfgPath = QDir::homePath() + QDir::separator() + "pine_bus.cfg";
    Settings::getSettings().init(cfgPath);

    RequestHandler *rh = new RequestHandler();
    rh->getCompletion("neuaff");

    return app.exec();
}
