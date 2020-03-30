#include "trip.h"



Trip::Trip(int id, QString name, QDateTime time, int company, int directon, int status, int terminal, int airplane, QString title)
{
    this->id = id;
    this->name = name;
    this->time = time;
    this->company = company;
    this->direction = directon;
    this->status = status;
    this->terminal = terminal;
    this->airplane = airplane;
    this->title = title;
}

Trip::Trip()
{

}
