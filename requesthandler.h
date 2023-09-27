#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QString>
#include <QAbstractListModel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QList>

class RequestHandler: public QAbstractListModel
{
    Q_OBJECT
private:
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
public slots:
    virtual void requestFinished(QNetworkReply *reply) = 0;
public:
    explicit RequestHandler(QObject *parent = nullptr);
//    virtual void parseResponse() = 0;
    QNetworkAccessManager* getManager();
    QNetworkRequest* getRequest();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override = 0;
    virtual QVariant data(const QModelIndex &index, int role) const override = 0;

};

#endif // REQUESTHANDLER_H
