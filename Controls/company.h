#ifndef COMPANY_H
#define COMPANY_H
#include <QString>

class Company
{
public:
    int id;
    QString name;
    int year;
    int staff;
    QString head;
    float profit;

    Company(int id,
    QString name,
    int year,
    int staff,
    QString head,
    float profit);
    Company();
};

#endif // COMPANY_H
