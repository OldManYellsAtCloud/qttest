#ifndef AUTOCOMPLETIONHANDLER_H
#define AUTOCOMPLETIONHANDLER_H

#include "requesthandler.h"

#define TRAM_ICON "sl-icon-type-bus"
#define BUS_ICON "sl-icon-type-tram"
#define TRAIN_ICON "sl-icon-type-train"
#define SHIP_ICON "sl-icon-type-ship"
#define CABLECAR_ICON "sl-icon-type-cablecar"

class AutoCompletionHandler : public RequestHandler
{
private:
    void parseAutoCompletion(QString jsonString);
    QList<QString> *locations;
public:
    explicit AutoCompletionHandler(QObject *parent = nullptr);
    ~AutoCompletionHandler();
    void fetchData(QVariant term) override;
    void clearModel() override;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    // RequestHandler interface
// public slots:
    void requestFinished(QNetworkReply *reply) override;
};

#endif // AUTOCOMPLETIONHANDLER_H
