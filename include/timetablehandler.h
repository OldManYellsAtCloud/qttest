#ifndef TIMETABLEHANDLER_H
#define TIMETABLEHANDLER_H

#include "requesthandler.h"
#include <QColor>

struct timetableEntry {
    QString lineNumber;
    QString terminal;
    QColor color;
    QString arrivalTime;
    qint16 delay;
};

class TimetableHandler : public RequestHandler
{
private:
    std::vector<timetableEntry> timeTableList;
    void parseTimetable(QString jsonString);

    QHash<int, QByteArray> m_roleNames;

public:
    explicit TimetableHandler(QObject *parent = nullptr);
    ~TimetableHandler();

    enum RoleNames {
        LineNumberRole = Qt::UserRole,
        TerminalRole = Qt::UserRole + 2,
        ColorRole = Qt::UserRole + 3,
        ArrivalTimeRole = Qt::UserRole + 4,
        DelayRole = Qt::UserRole + 5
    };


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    // RequestHandler interface
public slots:
    void requestFinished(QNetworkReply *reply) override;

public:
    void fetchData(QVariant arg) override;


    // RequestHandler interface
public:
    void clearModel() override;
};

#endif // TIMETABLEHANDLER_H
