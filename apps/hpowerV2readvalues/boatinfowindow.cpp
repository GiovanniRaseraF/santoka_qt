#include "boatinfowindow.h"
#include "ui_boatinfowindow.h"
#include <iostream>

BoatInfoWindow::BoatInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BoatInfoWindow)
{
    ui->setupUi(this);
}



BoatInfoWindow::~BoatInfoWindow()
{
    delete ui;
}

void BoatInfoWindow::connectInformations(
        PASSSHARED_NONULL (battery_filter, _battery),
        PASSSHARED_NONULL (command_filter, _command),
        PASSSHARED_NONULL (generalinfo_filter, _generalinfo),
        PASSSHARED_NONULL (motor_filter, _motor))
{
    battery = _battery;
    command = _command;
    generalinfo = _generalinfo;
    motor = _motor;

    connect(battery.get(), SIGNAL(new_bat_SOC(uint8_t)), this, SLOT(setSOC(uint8_t)));
}

void BoatInfoWindow::setSOC(uint8_t newval){
    std::cout << newval << std::endl;
}

void BoatInfoWindow::on_pushButton_clicked()
{
    disconnect(battery.get(), SIGNAL(new_bat_SOC(uint8_t)), this, SLOT(setSOC(uint8_t)));
    this->close();
}

