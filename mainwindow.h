#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void UpdateTerminalControl();
    void UpdateAirplaneControl();
    void UpdateCompanyControl();
    void UpdateDirectionControl();
    void UpdateStatusControl();

    void UpdateTripControl();

    void UpdateTable();

private slots:
    /*********ТЕРМИНАЛ**********/
    void on_comboBox_edit_trip_number_2_currentIndexChanged(const QString &arg1);

    void on_pushButton_airplane_remove_4_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();
    /*********КОНЕЦ**********/

    void on_comboBox_lineEdit_airplane_edit_name_currentIndexChanged(const QString &arg1);

    void on_pushButton_airplane_remove_clicked();

    void on_pushButton_airplane_edit_clicked();

    void on_pushButton_airplane_add_clicked();

    void on_comboBox_edit_trip_number_3_currentIndexChanged(const QString &arg1);

    void on_pushButton_airplane_remove_2_clicked();

    void on_pushButton_airplane_edit_2_clicked();

    void on_pushButton_6_clicked();

    void on_comboBox_edit_trip_number_4_currentIndexChanged(const QString &arg1);

    void on_pushButton_airplane_remove_3_clicked();

    void on_pushButton_airplane_edit_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_11_clicked();

    void on_comboBox_edit_trip_number_6_currentIndexChanged(const QString &arg1);

    void on_pushButton_airplane_remove_5_clicked();

    void on_pushButton_12_clicked();


    void on_comboBox_edit_trip_number_currentIndexChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_tabWidget_2_tabBarClicked(int index);

    void on_calendarWidget_activated(const QDate &date);

    void updateTimer();

private:
    Ui::MainWindow *ui;
    QTimer *tmr;
};
#endif // MAINWINDOW_H
