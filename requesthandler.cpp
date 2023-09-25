#include "requesthandler.h"
#include "settings.h"

#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

bool isDataRelevant(QString iconclass){
    return iconclass.contains(BUS_ICON) ||
           iconclass.contains(TRAM_ICON) ||
           iconclass.contains(TRAIN_ICON) ||
           iconclass.contains(SHIP_ICON) ||
           iconclass.contains(CABLECAR_ICON);
}

void parseAutoCompletion(QString jsonString){
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray jsonArray = jsonDocument.array();
    if (jsonArray.size() == 0) {
        qDebug() << "Reponse is an empty array";
        return;
    }

    QList<QString> *labels = new QList<QString>();
    QString iconclass;

    for (auto jsonValue: jsonArray){
        iconclass = jsonValue.toObject()["iconclass"].toString();
        if (isDataRelevant(iconclass))
            labels->append(jsonValue.toObject()["label"].toString().trimmed());
    }

    qDebug() << "brah: " << *labels;
    delete(labels);

}

void RequestHandler::requestFinished(QNetworkReply *reply)
{
    QString replyString = reply->readAll();
    qDebug() << "vau vau: " << replyString;
    parseAutoCompletion(replyString);
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
}

