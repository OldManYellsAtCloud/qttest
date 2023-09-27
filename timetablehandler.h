#ifndef TIMETABLEHANDLER_H
#define TIMETABLEHANDLER_H

#include "requesthandler.h"

class TimetableHandler : public RequestHandler
{
public:
    explicit TimetableHandler(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    // RequestHandler interface
public slots:
    void requestFinished(QNetworkReply *reply) override;

public:
    void fetchData(QVariant arg) override;
};

#endif // TIMETABLEHANDLER_H
