#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <QString>

class Airplane
{
public:
    int id;
    QString name;
    float cruising_speed;
    float length;
    float wingspan;
    float max_fly_width;
    int chair;
    int crew;
public:
    Airplane(int id,QString name,float cruising_speed,float length,float wingspan,float max_fly_width,int chair,int crew);
    Airplane();
};

#endif // AIRPLANE_H
