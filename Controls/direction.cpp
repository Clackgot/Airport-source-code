#include "direction.h"


Direction::Direction(int id, QString name, QString country, QString city, QString airport, bool visa)
{
    this->id = id;
    this->name = name;
    this->country = country;
    this->city = city;
    this->airport = airport;
    this->visa = visa;
}

Direction::Direction()
{

}
