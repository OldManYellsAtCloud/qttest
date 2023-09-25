#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <QList>

#define TRAM_ICON "sl-icon-type-bus"
#define BUS_ICON "sl-icon-type-tram"
#define TRAIN_ICON "sl-icon-type-train"
#define SHIP_ICON "sl-icon-type-ship"
#define CABLECAR_ICON "sl-icon-type-cablecar"

class RequestHandler: public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager *manager;
    QNetworkRequest *request;
public slots:
    void requestFinished(QNetworkReply *reply);
    void requestError(QNetworkReply *reply, QList<QSslError> const &errors);
public:
    RequestHandler();
    void getCompletion(QString s);
};

#endif // REQUESTHANDLER_H
