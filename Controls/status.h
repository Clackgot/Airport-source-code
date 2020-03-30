#ifndef STATUS_H
#define STATUS_H

#include <QString>

class Status
{
public:
    int id;
    QString name;
    QString title;
public:
    Status(int id,QString name,QString title);
    Status();
};

#endif // STATUS_H
