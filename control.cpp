#include "control.h"
#include <QDebug>
#include <QDir>
#include <QApplication>

Control::Control()
{
        db = QSqlDatabase::addDatabase("QSQLITE");
        QString cur_path = QDir::currentPath();
        QString db_name = "airport.db3";
        for(auto & it: cur_path)
        {
            if(it == '/') it= '\\';
        }
        cur_path+="\\";
        cur_path+=db_name;

        qDebug() << cur_path << endl;
        QString db_path = "C:\\Users\\Anicate\\source\\repos\\Airport\\airport.db3";
        db.setDatabaseName(cur_path);

        db.open();
        if(!(db.isOpen())) qDebug() << "Не удалось открыть базу данных" << endl;
}

void Control::LoadTerminals()
{
    terminals.erase(terminals.begin(),terminals.end());
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM Terminal");
    //Выводим значения из запроса
    while (query.next())
    {
    QString id = query.value(0).toString();
    QString name = query.value(1).toString();
    QString stile = query.value(2).toString();
    QString escalator = query.value(3).toString();
    auto temp = new Terminal(id.toInt(), name, stile.toInt(),escalator.toInt());
    terminals.push_back(*temp);
    }

}

void Control::SaveTerminals()
{
    QSqlQuery query;
    query.exec("DELETE FROM Terminal");
    for(auto it: terminals)
    {
        QString id = QString::number(it.id);
        QString name = it.name;
        QString stile = QString::number(it.stile);
        QString escalator = QString::number(it.escalator);
        QString req = "INSERT INTO Terminal (id,name,stile,escalator)VALUES ("+ id + ",\'"+name+"\',"+stile+","+escalator+")";
        query.exec(req);
    }
}

void Control::PrintTerminals()
{
    qDebug() << "------PrintTerminals------" << endl;
    for(auto it: terminals)
    {
        qDebug() << it.id << " " << it.name << " " << it.stile << " " << it.escalator << endl;
    }
}

void Control::UpdateTerminals()
{
    SaveTerminals();
    LoadTerminals();
}

QString Control::GetDataTerminals()
{
    QString temp = "ID \tName \tStile \tEscalator\n";
    for(auto it: terminals)
    {
        QString id = QString::number(it.id);
        QString name = static_cast<QString>(it.name);
        QString stile = QString::number(it.stile);
        QString escalator = QString::number(it.escalator);
        temp+=id + " \t" + name + " \t" + stile + " \t" + escalator + "\n";
    }
    return temp;
}



void Control::LoadAirplanes()
{
    airplanes.erase(airplanes.begin(),airplanes.end());
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM Airplane");
    //Выводим значения из запроса
    while (query.next())
    {
    QString id = query.value(0).toString();
    QString name = query.value(1).toString();
    QString cruising_speed = query.value(2).toString();
    QString length = query.value(3).toString();
    QString wingspan = query.value(4).toString();
    QString max_fly_width = query.value(5).toString();
    QString chair = query.value(6).toString();
    QString crew = query.value(7).toString();
    auto temp = new Airplane(id.toInt(), name, cruising_speed.toFloat(),length.toFloat(),wingspan.toFloat(),max_fly_width.toFloat(),chair.toInt(),crew.toInt());
    airplanes.push_back(*temp);
    }

}

void Control::SaveAirplanes()
{
    QSqlQuery query;
    query.exec("DELETE FROM Airplane");
    for(auto it: airplanes)
    {
        QString id = QString::number(it.id);
        QString name = it.name;
        QString cruising_speed = QString::number(it.cruising_speed);
        QString length = QString::number(it.length);
        QString wingspan = QString::number(it.wingspan);
        QString max_fly_width = QString::number(it.max_fly_width);
        QString chair = QString::number(it.chair);
        QString crew = QString::number(it.crew);
        QString req = "INSERT INTO Airplane (id,name,cruising_speed,length,wingspan,max_fly_width,chair,crew)VALUES ("+id+",\'"+name+"\',"+cruising_speed+","+length+","+wingspan+","+max_fly_width+","+chair+","+crew+")";
        //QString req = "INSERT INTO Airplane (id,name,stile,escalator)VALUES ("+ id + ",\'"+name+"\',"+cruising_speed+","+escalator+")";
        query.exec(req);
    }
}

void Control::PrintAirplanes()
{
    qDebug() << "------PrintAirplanes------" << endl;
    for(auto it: airplanes)
    {
        qDebug() << it.id << " " << it.name << " " << it.cruising_speed << " " << it.length << " " << it.wingspan << " " << it.max_fly_width << " " << it.chair << " " << it.crew <<  endl;
    }
}

void Control::UpdateAirplanes()
{
    SaveAirplanes();
    LoadAirplanes();
}

QString Control::GetDataAirplanes()
{
    QString temp = "ID \tName \t\tSpeed \tLength \tWingspan \tWidth \tChair \tCrew \n";
    for(auto it: airplanes)
    {
        QString id = QString::number(it.id);
        QString name = it.name;
        QString cruising_speed = QString::number(it.cruising_speed);
        QString length = QString::number(it.length);
        QString wingspan = QString::number(it.wingspan);
        QString max_fly_width = QString::number(it.max_fly_width);
        QString chair = QString::number(it.chair);
        QString crew = QString::number(it.crew);
        temp+=id + " \t" + name + " \t\t" +
                cruising_speed + " \t" +
                length + " \t" +
                wingspan + " \t" +
                max_fly_width + " \t" +
                chair + " \t" +
                crew + "\n";
    }
    return temp;
}


void Control::LoadCompanies()
{
    companies.erase(companies.begin(),companies.end());
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM Company");
    //Выводим значения из запроса
    while (query.next())
    {
    QString id = query.value(0).toString();
    QString name = query.value(1).toString();
    QString year = query.value(2).toString();
    QString staff = query.value(3).toString();
    QString head = query.value(4).toString();
    QString profit = query.value(5).toString();

    auto temp = new Company(id.toInt(), name, year.toInt(), staff.toInt(), head, profit.toFloat());
    companies.push_back(*temp);
    }
}

void Control::SaveCompanies()
{
    QSqlQuery query;
    query.exec("DELETE FROM Company");

    for(auto it: companies)
    {
        QString id = QString::number(it.id);
        QString name = it.name;
        QString year = QString::number(it.year);
        QString staff = QString::number(it.staff);
        QString head = it.head;
        QString profit = QString::number(it.profit);

        QString req = "INSERT INTO Company (profit,head,staff,year,name,id)VALUES ("+profit+",\'"+head+"\',"+staff+","+year+",\'"+name+"\',"+id+")";
        query.exec(req);

    }
}

void Control::PrintCompanies()
{
    qDebug() << "------PrintCompanies------" << endl;
    for(auto it: companies)
    {
        qDebug() << it.id << " " << it.name << " " << it.year << " " << it.staff << " " << it.head << " " << it.profit <<  endl;
    }
}

void Control::UpdateCompanies()
{
SaveCompanies();
LoadCompanies();
}

QString Control::GetDataCompanies()
{
    QString temp = "ID \tName \t\tYear \t\tStaff \t\tHead \t\tProfit \n";
    for(auto it: companies)
    {
        QString id = QString::number(it.id);
        QString name = it.name;
        QString year = QString::number(it.year);
        QString staff = QString::number(it.staff);
        QString head = it.head;
        QString profit = QString::number(it.profit);
        temp+=id + " \t" + name + " \t\t" +
                year + " \t\t" +
                staff + " \t\t" +
                head + " \t" +
                profit + "\n";
    }
    return temp;
}




void Control::LoadDirections()
{
    directions.erase(directions.begin(),directions.end());
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM Direction");
    //Выводим значения из запроса
    while (query.next())
    {
    QString id = query.value(0).toString();
    QString name = query.value(1).toString();
    QString country = query.value(2).toString();
    QString city = query.value(3).toString();
    QString airport = query.value(4).toString();
    QString visa = query.value(5).toString();

    auto temp = new Direction(id.toInt(),name,country,city,airport,visa.toInt());
    directions.push_back(*temp);
    }
}

void Control::SaveDirections()
{
    QSqlQuery query;
    query.exec("DELETE FROM Direction");

    for(auto it: directions)
    {
        QString id = QString::number(it.id);
        QString name = it.name;
        QString country = it.country;
        QString city = it.city;
        QString airport = it.airport;
        QString visa = QString::number(it.visa);

        QString req = "INSERT INTO Direction (Visa,Airport,City,Country,name,id)VALUES ("+visa+",\'"+airport+"\',\'"+city+"\',\'"+country+"\',\'"+name+"\',"+id+")";
        query.exec(req);
    }
}

void Control::PrintDirections()
{
    qDebug() << "------PrintDirections------" << endl;
    for(auto it: directions)
    {
        qDebug() << it.id << " " << it.name << " " << it.country << " " << it.city << " " << it.airport << " " << it.visa <<  endl;
    }
}

void Control::UpdateDirections()
{
    SaveDirections();
    LoadDirections();
}

QString Control::GetDataDirections()
{
    QString temp = "ID \tName \t\tCountry \tCity \t\tAirport \t\t\tVisa \n";
    for(auto it: directions)
    {
        QString id = QString::number(it.id);
        QString name = it.name;
        QString country = it.country;
        QString city = it.city;
        QString airport = it.airport;
        QString visa = QString::number(it.visa);
        temp+=id + " \t" + name + " \t" +
                country + " \t" +
                city + " \t\t" +
                airport + " \t\t" +
                visa + "\t\n";
    }
    return temp;
}


void Control::LoadStatuses()
{
    statuses.erase(statuses.begin(),statuses.end());
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM Status");
    //Выводим значения из запроса
    while (query.next())
    {
    QString id = query.value(0).toString();
    QString name = query.value(1).toString();
    QString title = query.value(2).toString();


    auto temp = new Status(id.toInt(),name,title);
    statuses.push_back(*temp);
    }
}
void Control::SaveStatuses()
{
    QSqlQuery query;
    query.exec("DELETE FROM Status");

    for(auto it: statuses)
    {
        QString id = QString::number(it.id);
        QString name = it.name;
        QString title = it.title;

        QString req = "INSERT INTO Status (Title,name,id)VALUES (\'"+title+"\',\'"+name+"\',"+id+")";
        query.exec(req);
    }
}
void Control::UpdateStatuses()
{
    SaveStatuses();
    LoadStatuses();
}




void Control::LoadTrips()
{
    trips.erase(trips.begin(),trips.end());
    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT * FROM Trip");
    //Выводим значения из запроса
    qDebug() << "---------LoadTrips()--------" << endl;
    while (query.next())
    {
    QString id = query.value(0).toString();
    QString name = query.value(1).toString();
    QString time = query.value(2).toString();
    QString company = query.value(3).toString();
    QString directon = query.value(4).toString();
    QString status = query.value(5).toString();
    QString terminal = query.value(6).toString();
    QString airplane = query.value(7).toString();
    QString title = query.value(8).toString();

    qDebug() << id << time << company<< directon<< status<< terminal<< airplane<< title<< endl;
    auto dt = QDateTime();
    dt.setTime_t(time.toUInt());

    auto temp = new Trip( id.toInt(),  name,  dt,  company.toInt(),  directon.toInt(),  status.toInt(),  terminal.toInt(),  airplane.toInt(),  title);
    trips.push_back(*temp);
    }
}

void Control::SaveTrips()
{
    QSqlQuery query;
    query.exec("DELETE FROM Trip");
    qDebug() << "---------SaveTrips()--------" << endl;
    for(auto it: trips)
    {
        QString id = QString::number(it.id);
        QString name = it.name;
        QString time = QString::number(it.time.toTime_t());
        QString company = QString::number(it.company);
        QString directon = QString::number(it.direction);
        QString status = QString::number(it.status);
        QString terminal = QString::number(it.terminal);
        QString airplane = QString::number(it.airplane);
        QString title = it.title;


        qDebug() << id << time << company<< directon<< status<< terminal<< airplane<< title<< endl;

        QString req = "INSERT INTO Trip (title,airplane,terminal,status,direction,company,time,name,id)VALUES (\'"+title+"\',"+airplane+","+terminal+","+status+","+directon+","+company+","+time+",\'"+name+"\',"+id+")";
        query.exec(req);
    }
}



void Control::UpdateTrips()
{
    SaveTrips();
    LoadTrips();
}

