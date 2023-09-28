#include "autocompletionhandler.h"
#include "settings.h"

#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

bool isDataRelevant(QString iconclass){
    return iconclass.contains(BUS_ICON) ||
           iconclass.contains(TRAM_ICON) ||
           iconclass.contains(TRAIN_ICON) ||
           iconclass.contains(SHIP_ICON) ||
           iconclass.contains(CABLECAR_ICON);
}

AutoCompletionHandler::AutoCompletionHandler(QObject* parent) : RequestHandler {parent}
{
    locations = new QList<QString>();
}

AutoCompletionHandler::~AutoCompletionHandler()
{
    delete(locations);
}

void AutoCompletionHandler::fetchData(QVariant term)
{
    QString sTerm = term.toString();
    QString surl = Settings::getSettings().getValue("endpoints/base").toString();
    surl += Settings::getSettings().getValue("endpoints/completion").toString();

    QUrl *url = new QUrl(surl);
    QUrlQuery *qQuery = new QUrlQuery{};
    qQuery->addQueryItem("term", sTerm);

    url->setQuery(qQuery->query());

    getRequest()->setUrl(*url);
    qDebug() << "sending html request to: " << getRequest()->url();
    getManager()->get(*getRequest());

    delete(url);
    delete(qQuery);
}

void AutoCompletionHandler::clearModel()
{
    emit beginRemoveRows(QModelIndex(), 0, locations->count() - 1);
    locations->clear();
    emit endRemoveRows();
}

int AutoCompletionHandler::rowCount(const QModelIndex &parent) const
{
    return locations->size();
}

QVariant AutoCompletionHandler::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= locations->size()){
        return QVariant();
    }

    switch(role){
        case Qt::DisplayRole:
            qDebug() << "Returning text: " << locations->at(index.row());
            return locations->at(index.row());
    }

    return QVariant();
}

void AutoCompletionHandler::requestFinished(QNetworkReply *reply)
{
    QString replyString = reply->readAll();
    qDebug() << "response: " << replyString;
    parseAutoCompletion(replyString);
}

void AutoCompletionHandler::parseAutoCompletion(QString jsonString){
    QList<QString> *tmp = new QList<QString>();
    emit beginRemoveRows(QModelIndex(), 0, locations->count() - 1);
    locations->clear();
    emit endRemoveRows();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray jsonArray = jsonDocument.array();
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
