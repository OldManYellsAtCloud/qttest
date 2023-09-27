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

void AutoCompletionHandler::fetchData(QString term)
{
    QString surl = Settings::getSettings().getValue("endpoints/base").toString();
    surl += Settings::getSettings().getValue("endpoints/completion").toString();

    QUrl *url = new QUrl(surl);
    QUrlQuery *qQuery = new QUrlQuery{};
    qQuery->addQueryItem("term", term);

    url->setQuery(qQuery->query());

    getRequest()->setUrl(*url);
    qDebug() << "about to send a request: " << getRequest()->url();
    getManager()->get(*getRequest());

    //delete(url);
    //delete(qQuery);
    qDebug() << "still not dead";
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
            return locations->at(index.row());
    }

    return QVariant();
}

void AutoCompletionHandler::requestFinished(QNetworkReply *reply)
{
    QString replyString = reply->readAll();
    qDebug() << "vau vau: " << replyString;
    parseAutoCompletion(replyString);
}

void AutoCompletionHandler::parseAutoCompletion(QString jsonString){
    locations->clear();
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
            locations->append(jsonValue.toObject()["label"].toString());
        }
    }

    qDebug() << "brah: " << *locations;

}
