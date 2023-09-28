#ifndef TIMETABLEHANDLER_H
#define TIMETABLEHANDLER_H

#include "requesthandler.h"

struct timetableEntry {
    QString *lineNumber;
    QString *terminal;
    QTime *arrivalTime;
    QTime *delay;
};

class TimetableHandler : public RequestHandler
{
private:
    std::vector<timetableEntry> timeTableList;
    void parseTimetable(QString jsonString);

public:
    explicit TimetableHandler(QObject *parent = nullptr);
    ~TimetableHandler();

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
