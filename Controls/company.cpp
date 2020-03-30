#include "company.h"


Company::Company(int id, QString name, int year, int staff, QString head, float profit)
{
    this->id = id;
    this->name = name;
    this->year = year;
    this->staff = staff;
    this->head = head;
    this->profit = profit;
}

Company::Company()
{

}
