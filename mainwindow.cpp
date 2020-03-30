#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "control.h"
#include <QDebug>
#include <QSqlTableModel>
#include <QVector>
#include <iterator>
#include <QThread>
#include <QTimer>

Control *ctr = new Control();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdNumber->display(QTime::currentTime().toString("hh:mm"));


    ctr->LoadStatuses();
    ctr->LoadDirections();
    ctr->LoadCompanies();
    ctr->LoadAirplanes();
    ctr->LoadTerminals();
    ctr->LoadTrips();
    //***************TERMINAL***************//

    UpdateTerminalControl();
    //*****************КОНЕЦ****************//

    //***************AIRPLANE***************//

    UpdateAirplaneControl();
    //*****************КОНЕЦ****************//

    //***************Company****************//

    UpdateCompanyControl();
    //*****************КОНЕЦ****************//

    //***************Direction**************//

    UpdateDirectionControl();
    //*****************КОНЕЦ****************//

    //****************Status****************//

    UpdateStatusControl();
    //*****************КОНЕЦ****************//

    UpdateTripControl();


    UpdateTable();
    tmr = new QTimer(this);
    tmr->setInterval(500);
    connect(tmr,SIGNAL(timeout()),this,SLOT(updateTimer()));
    tmr->start();
}

MainWindow::~MainWindow()
{
    ctr->SaveTerminals();
    ctr->SaveAirplanes();
    ctr->SaveCompanies();
    ctr->SaveDirections();
    ctr->SaveStatuses();
    ctr->SaveTrips();
    delete ui;
}

//***************TERMINAL***************/
//Обновление окна управления терминалами
void MainWindow::UpdateTerminalControl()
{
    //Комбобокс
    int index = ui->comboBox_edit_trip_number_2->currentIndex();
    ui->comboBox_edit_trip_number_2->clear();
    for(auto it : ctr->terminals)ui->comboBox_edit_trip_number_2->addItem(it.name);
    ui->comboBox_edit_trip_number_2->setCurrentIndex(index);
    QString cur_t = ui->comboBox_edit_trip_number_2->currentText();

    //Главное окно с инфой
    ctr->UpdateTerminals();
    QSqlTableModel * model = new QSqlTableModel(this,ctr->db);
    model->setTable("Terminal");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0,Qt::Horizontal,tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("Терминал"));
    model->setHeaderData(2,Qt::Horizontal,tr("Турникетов"));
    model->setHeaderData(3,Qt::Horizontal,tr("Эскалатор"));
    ui->tableView_4->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_4->setModel(model);
    ui->tableView_4->show();


    int stile;
    bool escalator;
    for(auto it: ctr->terminals)
    {
        if(it.name == cur_t)
        {
            stile = it.stile;
            escalator = it.escalator;
        }
    }
    ui->spinBox_airplane_add_chair_3->setValue(stile);
    if(escalator)ui->checkBox_3->setChecked(true);
    else ui->checkBox_3->setChecked(false);


}
//При изменении комбобокса
void MainWindow::on_comboBox_edit_trip_number_2_currentIndexChanged(const QString &arg1)
{
    int stile;
    bool escalator;
    for(auto it: ctr->terminals)
    {
        if(it.name == arg1)
        {
            stile = it.stile;
            escalator = it.escalator;
        }
    }
    ui->spinBox_airplane_add_chair_3->setValue(stile);
    if(escalator)ui->checkBox_3->setChecked(true);
    else ui->checkBox_3->setChecked(false);
}
//При клике на удаление элемента
void MainWindow::on_pushButton_airplane_remove_4_clicked()
{
    QString cur_t = ui->comboBox_edit_trip_number_2->currentText();

    int id = -1;

    auto field = ctr->terminals;
    for(auto &it : field )
    {
        if(it.name == cur_t)
        {
            id = it.id;
            field.erase(&it);

            for(auto &tr: ctr->trips)
            {
                if(tr.terminal == id)
                {
                    qDebug() << "Удалил рейс " << tr.name << endl;
                    ctr->trips.erase(&tr);
                }
            }
        }

    }

    UpdateTerminalControl();
}
//При клике на изменение элемента
void MainWindow::on_pushButton_9_clicked()
{
    QString cur_t = ui->comboBox_edit_trip_number_2->currentText();
    int stile = ui->spinBox_airplane_add_chair_3->text().toInt();
    for(int i = 0; i < ctr->terminals.size(); i++)
    {
        if(ctr->terminals[i].name == cur_t)
        {
            ctr->terminals[i].stile = stile;
            if(ui->checkBox_3->isChecked()) ctr->terminals[i].escalator = true;
            else ctr->terminals[i].escalator = false;
        }
    }
    UpdateTerminalControl();
}
//При клике на добавление элемента
void MainWindow::on_pushButton_10_clicked()
{

    QSqlQuery query;

    int id = (ctr->terminals.end()-1)->id+1;
    QString name = ui->lineEdit_37->text();
    int stile = ui->spinBox_airplane_add_chair_2->text().toInt();
    bool escalator = ui->checkBox_4->isChecked();

    bool correct = true;

    for(auto it: ctr->terminals)if(it.name == name)correct = false;

    if(correct)ctr->terminals.push_back(Terminal(id,name,stile,escalator));
    UpdateTerminalControl();
}
/*****************КОНЕЦ*****************/


//***************AIRPLANE***************/
//Обновление окна управления терминалами
void MainWindow::UpdateAirplaneControl()
{

    //Главное окно с инфой
    ctr->UpdateAirplanes();
    QSqlTableModel * model = new QSqlTableModel(this,ctr->db);
    model->setTable("Airplane");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0,Qt::Horizontal,tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("Название"));
    model->setHeaderData(2,Qt::Horizontal,tr("Крейсерская скорость"));
    model->setHeaderData(3,Qt::Horizontal,tr("Длина"));
    model->setHeaderData(4,Qt::Horizontal,tr("Размах крыльев"));
    model->setHeaderData(5,Qt::Horizontal,tr("Максимальный взлётный вес"));
    model->setHeaderData(6,Qt::Horizontal,tr("Мест"));
    model->setHeaderData(7,Qt::Horizontal,tr("Экипажа"));

    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_2->setModel(model);
    ui->tableView_2->show();

    //Комбобокс
    int index = ui->comboBox_lineEdit_airplane_edit_name->currentIndex();
    ui->comboBox_lineEdit_airplane_edit_name->clear();
    for(auto it : ctr->airplanes)ui->comboBox_lineEdit_airplane_edit_name->addItem(it.name);
    ui->comboBox_lineEdit_airplane_edit_name->setCurrentIndex(index);
    QString cur_t = ui->comboBox_lineEdit_airplane_edit_name->currentText();


    QString name;
    float cruising_speed;
    float length;
    float wingspan;
    float max_fly_width;
    int chair;
    int crew;

    for(auto it: ctr->airplanes)
    {
        if(it.name == cur_t)
        {
            cruising_speed = it.cruising_speed;
            length = it.length;
            wingspan = it.wingspan;
            max_fly_width = it.max_fly_width;
            chair = it.chair;
            crew = it.crew;
        }
    }

    ui->doubleSpinBox_airplane_edit_cruising_speed->setValue(cruising_speed);
    ui->doubleSpinBox_airplane_edit_length->setValue(length);
    ui->doubleSpinBox_airplane_edit_wingspan->setValue(wingspan);
    ui->doubleSpinBox_airplane_edit_max_fly_width->setValue(max_fly_width);
    ui->spinBox_airplane_edit_crew->setValue(chair);
    ui->spinBox_airplane_edit_crew_2->setValue(crew);

}
//При изменении комбобокса
void MainWindow::on_comboBox_lineEdit_airplane_edit_name_currentIndexChanged(const QString &arg1)
{
    float cruising_speed;
    float length;
    float wingspan;
    float max_fly_width;
    int chair;
    int crew;
    for(auto it: ctr->airplanes)
    {
        if(it.name == arg1)
        {
            cruising_speed = it.cruising_speed;
            length = it.length;
            wingspan = it.wingspan;
            max_fly_width = it.max_fly_width;
            chair = it.chair;
            crew = it.crew;
        }
    }
    ui->doubleSpinBox_airplane_edit_cruising_speed->setValue(cruising_speed);
    ui->doubleSpinBox_airplane_edit_length->setValue(length);
    ui->doubleSpinBox_airplane_edit_wingspan->setValue(wingspan);
    ui->doubleSpinBox_airplane_edit_max_fly_width->setValue(max_fly_width);
    ui->spinBox_airplane_edit_crew->setValue(chair);
    ui->spinBox_airplane_edit_crew_2->setValue(crew);
}

//При клике на удаление элемента
void MainWindow::on_pushButton_airplane_remove_clicked()
{
    QString cur_t = ui->comboBox_lineEdit_airplane_edit_name->currentText();
    int id = -1;

    auto field = ctr->airplanes;
    for(auto &it : field )
    {
        if(it.name == cur_t)
        {
            id = it.id;
            field.erase(&it);

            for(auto &tr: ctr->trips)
            {
                if(tr.airplane == id)
                {
                    qDebug() << "Удалил рейс " << tr.name <<  endl;
                    ctr->trips.erase(&tr);
                }
            }
        }

    }
    UpdateAirplaneControl();
}

//При клике на изменение элемента
void MainWindow::on_pushButton_airplane_edit_clicked()
{
    QString cur_t = ui->comboBox_lineEdit_airplane_edit_name->currentText();

    float cruising_speed = ui->doubleSpinBox_airplane_edit_cruising_speed->value();
    float length = ui->doubleSpinBox_airplane_edit_length->value();
    float wingspan = ui->doubleSpinBox_airplane_edit_wingspan->value();
    float max_fly_width = ui->doubleSpinBox_airplane_edit_max_fly_width->value();
    int chair = ui->spinBox_airplane_edit_crew->value();
    int crew = ui->spinBox_airplane_edit_crew_2->value();

    for(int i = 0; i < ctr->airplanes.size(); i++)
    {
        if(ctr->airplanes[i].name == cur_t)
        {
            ctr->airplanes[i].cruising_speed = cruising_speed;
            ctr->airplanes[i].length = length;
            ctr->airplanes[i].wingspan = wingspan;
            ctr->airplanes[i].max_fly_width = max_fly_width;
            ctr->airplanes[i].chair = chair;
            ctr->airplanes[i].crew = crew;
        }
    }
    UpdateAirplaneControl();
}

//При клике на добавление элемента
void MainWindow::on_pushButton_airplane_add_clicked()
{

    int id = (ctr->airplanes.end()-1)->id+1;
    QString name = ui->lineEdit_airplane_add_name->text();
    float cruising_speed = ui->doubleSpinBox_airplane_add_cruising_speed->value();
    float length = ui->doubleSpinBox_airplane_add_length->value();
    float wingspan = ui->doubleSpinBox_airplane_add_wingspan->value();
    float max_fly_width = ui->doubleSpinBox_airplane_add_max_fly_width->value();
    int chair = ui->spinBox_airplane_add_chair->value();
    int crew = ui->spinBox_airplane_add_crew->value();

    bool correct = true;

    for(auto it: ctr->airplanes)if(it.name == name)correct = false;

    if(correct)ctr->airplanes.push_back(Airplane(id, name, cruising_speed, length, wingspan, max_fly_width, chair, crew));
    UpdateAirplaneControl();
}
/*****************КОНЕЦ*****************/


void MainWindow::UpdateCompanyControl()
{
    //Главное окно с инфой
    //Главное окно с инфой
    ctr->UpdateCompanies();
    QSqlTableModel * model = new QSqlTableModel(this,ctr->db);
    model->setTable("Company");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0,Qt::Horizontal,tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("Название"));
    model->setHeaderData(2,Qt::Horizontal,tr("Год создания"));
    model->setHeaderData(3,Qt::Horizontal,tr("Сотрудники"));
    model->setHeaderData(4,Qt::Horizontal,tr("Глава"));
    model->setHeaderData(5,Qt::Horizontal,tr("Оборот"));



    ui->tableView_3->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_3->setModel(model);
    ui->tableView_3->show();

    //Комбобокс
    int index = ui->comboBox_edit_trip_number_3->currentIndex();
    ui->comboBox_edit_trip_number_3->clear();
    for(auto it : ctr->companies)ui->comboBox_edit_trip_number_3->addItem(it.name);
    ui->comboBox_edit_trip_number_3->setCurrentIndex(index);
    QString cur_t = ui->comboBox_edit_trip_number_3->currentText();


    int year;
    int staff;
    QString head;
    float profit;

    for(auto it: ctr->companies)
    {
        if(it.name == cur_t)
        {
            year = it.year;
            staff = it.staff;
            head = it.head;
            profit = it.profit;
        }
    }

    ui->spinBox_airplane_add_chair_6->setValue(year);
    ui->spinBox_airplane_add_chair_7->setValue(staff);
    ui->lineEdit_20->setText(head);
    ui->doubleSpinBox_airplane_add_max_fly_width_3->setValue(profit);
}
void MainWindow::on_comboBox_edit_trip_number_3_currentIndexChanged(const QString &arg1)
{

    int year;
    int staff;
    QString head;
    float profit;
    for(auto it: ctr->companies)
    {
        if(it.name == arg1)
        {
            year = it.year;
            staff = it.staff;
            head = it.head;
            profit = it.profit;
        }
    }
    ui->spinBox_airplane_add_chair_6->setValue(year);
    ui->spinBox_airplane_add_chair_7->setValue(staff);
    ui->lineEdit_20->setText(head);
    ui->doubleSpinBox_airplane_add_max_fly_width_3->setValue(profit);
}
void MainWindow::on_pushButton_airplane_remove_2_clicked()
{
    QString cur_t = ui->comboBox_edit_trip_number_3->currentText();

    int id = -1;

    auto field = ctr->companies;
    for(auto &it : field )
    {
        if(it.name == cur_t)
        {
            id = it.id;
            field.erase(&it);

            for(auto &tr: ctr->trips)
            {
                if(tr.company == id)
                {
                    qDebug() << "Удалил рейс " << tr.name << endl;
                    ctr->trips.erase(&tr);
                }
            }
        }

    }
    UpdateCompanyControl();
}
void MainWindow::on_pushButton_airplane_edit_2_clicked()
{
    QString cur_t = ui->comboBox_edit_trip_number_3->currentText();



    int year = ui->spinBox_airplane_add_chair_6->value();
    int staff = ui->spinBox_airplane_add_chair_7->value();
    QString head = ui->lineEdit_20->text();
    float profit = ui->doubleSpinBox_airplane_add_max_fly_width_3->value();

    for(int i = 0; i < ctr->companies.size(); i++)
    {
        if(ctr->companies[i].name == cur_t)
        {
            ctr->companies[i].year = year;
            ctr->companies[i].staff = staff;
            ctr->companies[i].head = head;
            ctr->companies[i].profit = profit;
        }
    }
    UpdateCompanyControl();
}
void MainWindow::on_pushButton_6_clicked()
{
    int id = (ctr->companies.end()-1)->id+1;
    QString name = ui->lineEdit_29->text();
    int year = ui->spinBox_airplane_add_chair_4->value();
    int staff = ui->spinBox_airplane_add_chair_5->value();
    QString head = ui->lineEdit_26->text();
    float profit = ui->doubleSpinBox_airplane_add_max_fly_width_2->value();

    bool correct = true;

    for(auto it: ctr->companies)if(it.name == name)correct = false;

    if(correct)ctr->companies.push_back(Company( id,  name,  year,  staff,  head, profit));
    UpdateCompanyControl();
}



void MainWindow::UpdateDirectionControl()
{

    ctr->UpdateDirections();
    QSqlTableModel * model = new QSqlTableModel(this,ctr->db);
    model->setTable("Direction");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0,Qt::Horizontal,tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("Направление"));
    model->setHeaderData(2,Qt::Horizontal,tr("Страна"));
    model->setHeaderData(3,Qt::Horizontal,tr("Город"));
    model->setHeaderData(4,Qt::Horizontal,tr("Аэропорт"));
    model->setHeaderData(5,Qt::Horizontal,tr("Виза"));
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setModel(model);
    ui->tableView->show();



    //Комбобокс
    int index = ui->comboBox_edit_trip_number_4->currentIndex();
    ui->comboBox_edit_trip_number_4->clear();
    for(auto it : ctr->directions)ui->comboBox_edit_trip_number_4->addItem(it.name);
    ui->comboBox_edit_trip_number_4->setCurrentIndex(index);
    QString cur_t = ui->comboBox_edit_trip_number_4->currentText();

    QString name;
    QString country;
    QString city;
    QString airport;
    bool visa;

    for(auto it: ctr->directions)
    {
        if(it.name == cur_t)
        {
            country = it.country;
            city = it.city;
            airport = it.airport;
            visa = it.visa;
        }
    }

    ui->lineEdit_24->setText(country);
    ui->lineEdit_23->setText(city);
    ui->lineEdit_32->setText(airport);
    if(visa)ui->checkBox_2->setChecked(true);
    else ui->checkBox_2->setChecked(false);
}
void MainWindow::on_comboBox_edit_trip_number_4_currentIndexChanged(const QString &arg1)
{

    QString country;
    QString city;
    QString airport;
    bool visa;

    for(auto it: ctr->directions)
    {
        if(it.name == arg1)
        {
            country = it.country;
            city = it.city;
            airport = it.airport;
            visa = it.visa;
        }
    }

    ui->lineEdit_24->setText(country);
    ui->lineEdit_23->setText(city);
    ui->lineEdit_32->setText(airport);
    if(visa)ui->checkBox_2->setChecked(true);
    else ui->checkBox_2->setChecked(false);
}
void MainWindow::on_pushButton_airplane_remove_3_clicked()
{
    QString cur_t = ui->comboBox_edit_trip_number_4->currentText();

    int id = -1;

    auto field = ctr->directions;
    for(auto &it : field )
    {
        if(it.name == cur_t)
        {
            id = it.id;
            field.erase(&it);

            for(auto &tr: ctr->trips)
            {
                if(tr.direction == id)
                {
                    qDebug() << "Удалил рейс " << tr.name << endl;
                    ctr->trips.erase(&tr);
                }
            }
        }

    }
    UpdateDirectionControl();
}
void MainWindow::on_pushButton_airplane_edit_3_clicked()
{
    QString cur_t = ui->comboBox_edit_trip_number_4->currentText();


    QString country = ui->lineEdit_24->text();
    QString city = ui->lineEdit_23->text();
    QString airport = ui->lineEdit_32->text();
    bool visa;
    if(ui->checkBox_2->isChecked()) visa = true;
    else visa = false;

    for(int i = 0; i < ctr->directions.size(); i++)
    {
        if(ctr->directions[i].name == cur_t)
        {
            ctr->directions[i].country = country;
            ctr->directions[i].city = city;
            ctr->directions[i].airport = airport;
            ctr->directions[i].visa = visa;
            break;
        }
    }
    UpdateDirectionControl();
}
void MainWindow::on_pushButton_8_clicked()
{
    int id = (ctr->directions.end()-1)->id+1;
    QString name = ui->lineEdit_31->text();
    QString country = ui->lineEdit_24->text();
    QString city = ui->lineEdit_23->text();
    QString airport = ui->lineEdit_32->text();
    bool visa;
    if(ui->checkBox->isChecked()) visa = true;
    else visa = false;

    bool correct = true;

    for(auto it: ctr->directions)if(it.name == name)correct = false;

    if(correct)ctr->directions.push_back(Direction( id,  name,  country,  city,  airport,  visa));
    UpdateDirectionControl();
}


void MainWindow::UpdateStatusControl()
{
    ctr->UpdateStatuses();
    QSqlTableModel * model = new QSqlTableModel(this,ctr->db);
    model->setTable("Status");
    //model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    /*
    model->setHeaderData(0,Qt::Horizontal,tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("Направление"));
    model->setHeaderData(2,Qt::Horizontal,tr("Страна"));
    model->setHeaderData(3,Qt::Horizontal,tr("Город"));
    model->setHeaderData(4,Qt::Horizontal,tr("Аэропорт"));
    model->setHeaderData(5,Qt::Horizontal,tr("Виза"));
    */
    ui->tableView_5->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_5->setModel(model);
    ui->tableView_5->show();



    //Комбобокс
    int index = ui->comboBox_edit_trip_number_6->currentIndex();
    ui->comboBox_edit_trip_number_6->clear();
    for(auto it : ctr->statuses)ui->comboBox_edit_trip_number_6->addItem(it.name);
    ui->comboBox_edit_trip_number_6->setCurrentIndex(index);
    QString cur_t = ui->comboBox_edit_trip_number_6->currentText();

    QString name;
    QString title;

    for(auto it: ctr->statuses)
    {
        if(it.name == cur_t)
        {
            title = it.title;
            break;
        }
    }

    ui->lineEdit_41->setText(title);
}
void MainWindow::on_comboBox_edit_trip_number_6_currentIndexChanged(const QString &arg1)
{
    QString title;

    for(auto it: ctr->statuses)
    {
        if(it.name == arg1)
        {
            title = it.title;
        }
    }

    ui->lineEdit_41->setText(title);
}
void MainWindow::on_pushButton_airplane_remove_5_clicked()
{
    QString cur_t = ui->comboBox_edit_trip_number_6->currentText();

    int id = -1;

    auto field = ctr->statuses;
    for(auto &it : field )
    {
        if(it.name == cur_t)
        {
            id = it.id;
            field.erase(&it);

            for(auto &tr: ctr->trips)
            {
                if(tr.status == id)
                {
                    qDebug() << "Удалил рейс " << tr.name << endl;
                    ctr->trips.erase(&tr);
                }
            }
        }

    }
    UpdateStatusControl();
}
void MainWindow::on_pushButton_11_clicked()
{
    QString cur_t = ui->comboBox_edit_trip_number_6->currentText();


    QString title = ui->lineEdit_41->text();

    for(int i = 0; i < ctr->statuses.size(); i++)
    {
        if(ctr->statuses[i].name == cur_t)
        {
            ctr->statuses[i].title = title;
            break;
        }
    }
    UpdateStatusControl();
}
void MainWindow::on_pushButton_12_clicked()
{
    int id = (ctr->statuses.end()-1)->id+1;
    QString name = ui->lineEdit_44->text();
    QString title = ui->lineEdit_47->text();


    bool correct = true;

    for(auto it: ctr->statuses)if(it.name == name)correct = false;

    if(correct)ctr->statuses.push_back(Status( id, name, title));
    UpdateStatusControl();
}


void MainWindow::UpdateTripControl()
{


    /*
    model->setHeaderData(0,Qt::Horizontal,tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("Наименование"));
    model->setHeaderData(2,Qt::Horizontal,tr("Страна"));
    model->setHeaderData(3,Qt::Horizontal,tr("Город"));
    model->setHeaderData(4,Qt::Horizontal,tr("Аэропорт"));
    model->setHeaderData(5,Qt::Horizontal,tr("Виза"));
    */

    int index = ui->comboBox_edit_trip_number->currentIndex();
    ui->comboBox_edit_trip_number->clear();
    for(auto it : ctr->trips)ui->comboBox_edit_trip_number->addItem(it.name);
    ui->comboBox_edit_trip_number->setCurrentIndex(index);
    QString cur_t = ui->comboBox_edit_trip_number->currentText();

    QDateTime time;

    for(auto it: ctr->trips)
    {
        if(it.name == cur_t)
        {
            time = it.time;
            break;
        }
    }


    ui->dateTimeEdit_2->setDate(time.date());
    ui->dateTimeEdit_2->setTime(time.time());

    int tempindex = ui->comboBox_edit_trip_aircompany->currentIndex();
    ui->comboBox_edit_trip_aircompany->clear();
    for(auto it: ctr->companies)ui->comboBox_edit_trip_aircompany->addItem(it.name);
    ui->comboBox_edit_trip_aircompany->setCurrentIndex(tempindex);

    tempindex = ui->comboBox_edit_trip_direction->currentIndex();
    ui->comboBox_edit_trip_direction->clear();
    for(auto it: ctr->directions)ui->comboBox_edit_trip_direction->addItem(it.name);
    ui->comboBox_edit_trip_direction->setCurrentIndex(tempindex);

    tempindex = ui->comboBox_edit_trip_status->currentIndex();
    ui->comboBox_edit_trip_status->clear();
    for(auto it: ctr->statuses)ui->comboBox_edit_trip_status->addItem(it.name);
    ui->comboBox_edit_trip_status->setCurrentIndex(tempindex);

    tempindex = ui->comboBox_22->currentIndex();
    ui->comboBox_22->clear();
    for(auto it: ctr->airplanes)ui->comboBox_22->addItem(it.name);
    ui->comboBox_22->setCurrentIndex(tempindex);

    tempindex = ui->comboBox_edit_trip_terminal->currentIndex();
    ui->comboBox_edit_trip_terminal->clear();
    for(auto it: ctr->terminals)ui->comboBox_edit_trip_terminal->addItem(it.name);
    ui->comboBox_edit_trip_terminal->setCurrentIndex(tempindex);
    /*************************************************************/
    tempindex = ui->comboBox_4->currentIndex();
    ui->comboBox_4->clear();
    for(auto it: ctr->companies)ui->comboBox_4->addItem(it.name);
    ui->comboBox_4->setCurrentIndex(tempindex);

    tempindex = ui->comboBox_5->currentIndex();
    ui->comboBox_5->clear();
    for(auto it: ctr->directions)ui->comboBox_5->addItem(it.name);
    ui->comboBox_5->setCurrentIndex(tempindex);

    tempindex = ui->comboBox_6->currentIndex();
    ui->comboBox_6->clear();
    for(auto it: ctr->statuses)ui->comboBox_6->addItem(it.name);
    ui->comboBox_6->setCurrentIndex(tempindex);

    tempindex = ui->comboBox_7->currentIndex();
    ui->comboBox_7->clear();
    for(auto it: ctr->terminals)ui->comboBox_7->addItem(it.name);
    ui->comboBox_7->setCurrentIndex(tempindex);

    tempindex = ui->comboBox_21->currentIndex();
    ui->comboBox_21->clear();
    for(auto it: ctr->airplanes)ui->comboBox_21->addItem(it.name);
    ui->comboBox_21->setCurrentIndex(tempindex);


}

void MainWindow::on_comboBox_edit_trip_number_currentIndexChanged(const QString &arg1)
{
    QDateTime time;
    int company;
    int direction;
    int status;
    int terminal;
    int airplane;
    QString title;

    for(auto it: ctr->trips)
    {
        if(it.name == arg1)
        {
            time = it.time;
            company = it.company;
            direction = it.direction;
            status = it.status;
            terminal = it.terminal;
            airplane = it.airplane;
            title = it.title;

        }
    }

    Company tcompany;
    Airplane tairplane;
    Direction tdirection;
    Status tstatus;
    Terminal tterminal;

    for(auto it: ctr->companies)if(it.id==company)tcompany = it;
    for(auto it: ctr->airplanes)if(it.id==airplane)tairplane = it;
    for(auto it: ctr->directions)if(it.id==direction)tdirection = it;
    for(auto it: ctr->statuses)if(it.id==status)tstatus = it;
    for(auto it: ctr->terminals)if(it.id==terminal)tterminal = it;


    ui->dateTimeEdit_2->setDate(time.date());
    ui->dateTimeEdit_2->setTime(time.time());

    ui->comboBox_edit_trip_aircompany->setCurrentText(tcompany.name);
    ui->comboBox_edit_trip_direction->setCurrentText(tdirection.name);
    ui->comboBox_edit_trip_status->setCurrentText(tstatus.name);
    ui->comboBox_22->setCurrentText(tairplane.name);
    ui->comboBox_edit_trip_terminal->setCurrentText(tterminal.name);
    ui->lineEdit_3->setText(title);


}

void MainWindow::on_pushButton_3_clicked()
{
    QString cur_t = ui->comboBox_edit_trip_number->currentText();

    for(int i = 0; i < ctr->trips.size(); i++)
    {
        if(ctr->trips[i].name == cur_t)ctr->trips.remove(i);
    }
    UpdateTripControl();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString cur_t = ui->comboBox_edit_trip_number->currentText();

    for(int i = 0; i < ctr->trips.size(); i++)
    {
        if(ctr->trips[i].name == cur_t)
        {
            ctr->trips[i].time = ui->dateTimeEdit_2->dateTime();
            for(auto it: ctr->companies)if(ui->comboBox_edit_trip_aircompany->currentText()==it.name)ctr->trips[i].company = it.id;
            for(auto it: ctr->directions)if(ui->comboBox_edit_trip_direction->currentText()==it.name)ctr->trips[i].direction = it.id;
            for(auto it: ctr->statuses)if(ui->comboBox_edit_trip_status->currentText()==it.name)ctr->trips[i].status = it.id;
            for(auto it: ctr->terminals)if(ui->comboBox_edit_trip_terminal->currentText()==it.name)ctr->trips[i].terminal = it.id;
            for(auto it: ctr->airplanes)if(ui->comboBox_22->currentText()==it.name)ctr->trips[i].airplane = it.id;
            ctr->trips[i].title = ui->lineEdit_3->text();
        }
    }



    UpdateTripControl();
}

void MainWindow::on_pushButton_clicked()
{

    Trip temp;

    int id = (ctr->trips.end()-1)->id+1;
    QString name = ui->lineEdit_4->text();
    QDateTime time;
    int company;
    int directon;
    int status;
    int terminal;
    int airplane;
    QString title = ui->lineEdit_2->text();


     time = ui->dateTimeEdit->dateTime();
     for(auto it: ctr->companies)if(ui->comboBox_4->currentText()==it.name)company = it.id;
     for(auto it: ctr->directions)if(ui->comboBox_5->currentText()==it.name)directon = it.id;
     for(auto it: ctr->statuses)if(ui->comboBox_6->currentText()==it.name)status = it.id;
     for(auto it: ctr->terminals)if(ui->comboBox_7->currentText()==it.name)terminal = it.id;
     for(auto it: ctr->airplanes)if(ui->comboBox_21->currentText()==it.name)airplane = it.id;





    bool correct = true;

    if(ui->comboBox_4->currentText() == "")correct = false;
    if(ui->lineEdit_4->text()=="")correct = false;
    if(ui->comboBox_5->currentText() == "")correct = false;
    if(ui->comboBox_6->currentText() == "")correct = false;
    if(ui->comboBox_7->currentText() == "")correct = false;
    if(ui->comboBox_21->currentText() == "")correct = false;
    for(auto it: ctr->statuses)if(it.name == name)correct = false;

    if(correct)ctr->trips.push_back(Trip( id,  name,  time,  company,  directon,  status,  terminal,  airplane,  title));
    UpdateTripControl();
}

void MainWindow::on_tabWidget_2_tabBarClicked(int index)
{
    if(index == 0)UpdateTable();
    if(index == 1)UpdateTripControl();
}


void MainWindow::UpdateTable()
{
    //ctr->UpdateTrips();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(7);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    int k = 0;
    for(auto it: ctr->trips)
    {
        ui->tableWidget->insertRow(k);
        ui->tableWidget->setItem(k,0,new QTableWidgetItem(it.name));
        ui->tableWidget->setItem(k,1,new QTableWidgetItem(it.time.toString("hh:mm yyyy")));
        ui->tableWidget->setItem(k,2,new QTableWidgetItem((std::find_if( ctr->terminals.begin() , ctr->terminals.end() , [&](const Terminal &t)->bool{return t.id == it.terminal;}))->name));
        ui->tableWidget->setItem(k,3,new QTableWidgetItem((std::find_if( ctr->companies.begin() , ctr->companies.end() , [&](const Company &t)->bool{return t.id == it.company;}))->name));
        ui->tableWidget->setItem(k,4,new QTableWidgetItem((std::find_if( ctr->directions .begin() , ctr->directions.end() , [&](const Direction &t)->bool{return t.id == it.direction;}))->name));
        ui->tableWidget->setItem(k,5,new QTableWidgetItem((std::find_if( ctr->statuses .begin() , ctr->statuses.end() , [&](const Status &t)->bool{return t.id == it.status;}))->name));
        ui->tableWidget->setItem(k,6,new QTableWidgetItem(it.title));

        k++;
    }



    ui->tableWidget->show();

}

void MainWindow::on_calendarWidget_activated(const QDate &date)
{
    ui->dateTimeEdit->setDate(date);
    ui->dateTimeEdit->setTime(QTime::currentTime());

}


void MainWindow::updateTimer()
{
    ui->lcdNumber->display(QTime::currentTime().toString("hh:mm"));

}



