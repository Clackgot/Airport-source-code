#ifndef CONTROL_H
#define CONTROL_H

#include <QVector>
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlDatabase"

#include "Controls/terminal.h"
#include "Controls/airplane.h"
#include "Controls/company.h"
#include "Controls/direction.h"
#include "Controls/status.h"
#include "Controls/trip.h"

class Control
{
public:
    QVector<Trip> trips;
    QSqlDatabase db;
    QVector<Terminal> terminals;
    QVector<Airplane> airplanes;
    QVector<Company> companies;
    QVector<Direction> directions;
    QVector<Status> statuses;

    void LoadTerminals();
    void SaveTerminals();
    void PrintTerminals();
    void UpdateTerminals();
    QString GetDataTerminals();

    void LoadAirplanes();
    void SaveAirplanes();
    void PrintAirplanes();
    void UpdateAirplanes();
    QString GetDataAirplanes();

    void LoadCompanies();
    void SaveCompanies();
    void PrintCompanies();
    void UpdateCompanies();
    QString GetDataCompanies();

    void LoadDirections();
    void SaveDirections();
    void PrintDirections();
    void UpdateDirections();
    QString GetDataDirections();

    void LoadStatuses();
    void SaveStatuses();
    void UpdateStatuses();

    void LoadTrips();
    void SaveTrips();
    void UpdateTrips();

    Control();
};

#endif // CONTROL_H
