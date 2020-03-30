#ifndef DIRECTION_H
#define DIRECTION_H
#include <QString>

class Direction
{
public:
    int id;
    QString name;
    QString country;
    QString city;
    QString airport;
    bool visa;
public:
    Direction(int id,
    QString name,
    QString country,
    QString city,
    QString airport,
    bool visa);
    Direction();
};

#endif // DIRECTION_H
