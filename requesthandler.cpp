#include "requesthandler.h"

#include <QDebug>

RequestHandler::RequestHandler(QObject* parent)
{
    manager = new QNetworkAccessManager();
    request = new QNetworkRequest();

    connect(manager, &QNetworkAccessManager::finished, this, &RequestHandler::requestFinished);
}

QNetworkAccessManager* RequestHandler::getManager()
{
    return manager;
}

QNetworkRequest* RequestHandler::getRequest()
{
    return request;
}
