#include "timetablehandler.h"
#include "settings.h"
#include <QUrl>
#include <QUrlQuery>

TimetableHandler::TimetableHandler(QObject *parent)
    : RequestHandler{parent}
{

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
