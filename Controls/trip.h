#ifndef TRIP_H
#define TRIP_H

#include <QString>
#include <QDateTime>
class Trip
{
public:
    int id;
    QString name;
    QDateTime time;
    int company;
    int direction;
    int status;
    int terminal;
    int airplane;
    QString title;
public:
    Trip(int id,
    QString name,
    QDateTime time,
    int company,
    int direction,
    int status,
    int terminal,
    int airplane,
    QString title);
    Trip();
};

#endif // TRIP_H
