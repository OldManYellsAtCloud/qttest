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
    m_roleNames[LineNumberRole] = "linenumber";
    m_roleNames[TerminalRole] = "terminal";
    m_roleNames[ColorRole] = "color";
    m_roleNames[ArrivalTimeRole] = "arrivaltime";
    m_roleNames[DelayRole] = "delay";
}

TimetableHandler::~TimetableHandler()
{
}

void TimetableHandler::parseTimetable(QString jsonString)
{
    clearModel();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray connectionsArray = jsonDocument.object()["connections"].toArray();


    if (connectionsArray.size() == 0) {
        qDebug() << "Response is an empty array";
        return;
    }

    emit beginInsertRows(QModelIndex(), 0, connectionsArray.size() - 1);

    for (auto jsonValue: connectionsArray){
        struct timetableEntry t;
        // get only the hh:mm part, no need for the date
        t.arrivalTime = jsonValue.toObject()["time"].toString().mid(11, 5);
        t.terminal = jsonValue.toObject()["terminal"].toObject()["name"].toString();
        t.lineNumber = jsonValue.toObject()["line"].toString();

        if (jsonValue.toObject().contains("arr_delay")){
            t.delay = jsonValue.toObject()["arr_delay"].toString().toInt();
        } else {
            t.delay = 0;
        }
        QString colorString = jsonValue.toObject()["color"].toString().split("~")[0];
        if (colorString == "ffffff")
            colorString = "000000";
        t.color = QColor("#" + colorString);
        timeTableList.push_back(t);
    }

    emit endInsertRows();
}

int TimetableHandler::rowCount(const QModelIndex &parent) const
{
    return timeTableList.size();
}

QVariant TimetableHandler::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= timeTableList.size()){
        return QVariant();
    }

    switch(role){
        case LineNumberRole:
            return timeTableList.at(index.row()).lineNumber;
        case TerminalRole:
            return timeTableList.at(index.row()).terminal;
        case ColorRole:
            return timeTableList.at(index.row()).color;
        case ArrivalTimeRole:
            return timeTableList.at(index.row()).arrivalTime;
        case DelayRole:
            return timeTableList.at(index.row()).delay;
    }

    return QVariant();
}

QHash<int, QByteArray> TimetableHandler::roleNames() const
{
    return m_roleNames;
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

void TimetableHandler::clearModel()
{
    emit beginRemoveRows(QModelIndex(), 0, timeTableList.size() - 1);
    timeTableList.clear();
    emit endRemoveRows();
}
