#include "timetablehandler.h"
#include "settings.h"
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

TimetableHandler::TimetableHandler(QObject *parent)
    : RequestHandler{parent}
{
}

TimetableHandler::~TimetableHandler()
{
}

void TimetableHandler::parseTimetable(QString jsonString)
{
    emit beginRemoveRows(QModelIndex(), 0, timeTableList.size() - 1);
    timeTableList.clear();
    emit endRemoveRows();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject connectionsObject = jsonDocument.object()["connections"];
    if (jsonArray.size() == 0) {
        qDebug() << "Reponse is an empty array";
        return;
    }

    QString iconclass;

    for (auto jsonValue: jsonArray){
        iconclass = jsonValue.toObject()["iconclass"].toString();
        if (isDataRelevant(iconclass)) {
            tmp->append(jsonValue.toObject()["label"].toString());
        }
    }
    emit beginInsertRows(QModelIndex(), 0, tmp->count() - 1);
    for (int i = 0; i < tmp->count(); ++i)
        locations->append(tmp->at(i));

    emit endInsertRows();
    qDebug() << "brah: " << *locations;
    delete(tmp);
}

int TimetableHandler::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant TimetableHandler::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

void TimetableHandler::requestFinished(QNetworkReply *reply)
{
    QString replyString = reply->readAll();
    qDebug() << "response: " << replyString;
    parseTimetable(replyString);
}

void TimetableHandler::fetchData(QVariant term)
{
    QString sTerm = term.toString();
    QString surl = Settings::getSettings().getValue("endpoints/base").toString();
    surl += Settings::getSettings().getValue("endpoints/stationboard").toString();

    QUrl *url = new QUrl(surl);
    QUrlQuery *qQuery = new QUrlQuery{};
    qQuery->addQueryItem("stop", sTerm);
    qQuery->addQueryItem("mode", "arrival");
    qQuery->addQueryItem("limit", "15");
    qQuery->addQueryItem("show_delays", "1");

    url->setQuery(qQuery->query());

    getRequest()->setUrl(*url);
    qDebug() << "sending html request to: " << getRequest()->url().toString(QUrl::FullyEncoded);
    getManager()->get(*getRequest());

    delete(url);
    delete(qQuery);
}
