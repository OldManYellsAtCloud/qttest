#include "requesthandler.h"
#include "settings.h"

#include <QDebug>
#include <QUrl>
#include <QUrlQuery>

void RequestHandler::requestFinished(QNetworkReply *reply)
{
    qDebug() << "vau vau: " << reply->readAll();
}

void RequestHandler::requestError(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug() << "Error happened: " << reply->readAll();
    for (int i = 0; i < errors.count(); ++i)
        qDebug() << errors.at(i).errorString();
}

RequestHandler::RequestHandler()
{
    manager = new QNetworkAccessManager();
    request = new QNetworkRequest();

    connect(manager, &QNetworkAccessManager::finished, this, &RequestHandler::requestFinished);
    connect(manager, &QNetworkAccessManager::sslErrors, this, &RequestHandler::requestError);
}

void RequestHandler::getCompletion(QString s)
{
    QString surl = Settings::getSettings().getValue("endpoints/base").toString();
    surl += Settings::getSettings().getValue("endpoints/completion").toString();

    QUrl *url = new QUrl(surl);
    QUrlQuery *qQuery = new QUrlQuery{};
    qQuery->addQueryItem("term", s);

    url->setQuery(qQuery->query());

    request->setUrl(*url);
    qDebug() << "about to send a request: " << request->url();
    manager->get(*request);
    //qDebug() << "vau vau: " << response->readAll();
}

