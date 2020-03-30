#include "airplane.h"


Airplane::Airplane()
{

}
Airplane::Airplane(int id, QString name, float cruising_speed, float length, float wingspan, float max_fly_width, int chair, int crew)
{
    this->id = id;
    this->name = name;
    this->cruising_speed = cruising_speed;
    this->length = length;
    this->wingspan = wingspan;
    this->max_fly_width = max_fly_width;
    this->chair = chair;
    this->crew = crew;
}
