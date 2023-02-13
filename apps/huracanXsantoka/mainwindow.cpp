#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qRegisterMetaType<struct can_frame>();
    ui->setupUi(this);

    // Create and start canbus on sepatate thread
    canbus_producer = std::make_shared<fake_canbus_thread>("fake can producer", 30, nullptr);
    one_second_producer = std::make_shared<fake_canbus_thread>("fake 1 second", 1000, nullptr);

    canbus_producer->start();
    one_second_producer->start();

    // Create filters
    logger = std::make_shared<filter>(canbus_producer, this);
    battery = std::make_shared<battery_filter>(canbus_producer, this);
    command = std::make_shared<command_filter>(canbus_producer, this);
    generalinfo = std::make_shared<generalinfo_filter>(canbus_producer, this);
    motor = std::make_shared<motor_filter>(canbus_producer, this);
    // Connect data to Graphics
    connectBatteryFilterToGraphics();
    connectMotorFilterToGraphics();

    // pages
    // boat info
}

void MainWindow::connectBatteryFilterToGraphics(){
    connect(battery.get(), SIGNAL(new_bat_SOC(uint8_t)), this, SLOT(setSOC(uint8_t)));
    connect(battery.get(), SIGNAL(new_bat_Power(float)), this, SLOT(setPower(float)));
    connect(battery.get(), SIGNAL(new_bat_BatteryTemperature(uint8_t)), this, SLOT(setPowerTemperature(uint8_t)));
}

void MainWindow::connectMotorFilterToGraphics(){
    connect(motor.get(), SIGNAL(new_drv_motorSpeed(uint16_t)), this, SLOT(setMotorSpeed(uint16_t)));
    connect(motor.get(), SIGNAL(new_drv_motorTemperature(uint8_t)), this, SLOT(setMotorTemperature(uint8_t)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Display graphics
void MainWindow::setSOC(uint8_t newSOC)
{
   ui->l_SOC_value->setText(QString::number(newSOC));
}

void MainWindow::setPowerTemperature(uint8_t newPowerTemperature)
{
   //qDebug() << newPowerTemperature ;
   ui->l_powertemp_value->setText(QString::number(newPowerTemperature));
}

void MainWindow::setPower(float newPower)
{
   ui->l_power_value->setText(QString::number(newPower));
}

void MainWindow::setSpeed(uint16_t newSpeed)
{
   ui->l_speed_value->setText(QString::number(newSpeed));
}

void MainWindow::setMotorTemperature(uint8_t newMotorTemperature)
{
   ui->l_motortemp_value->setText(QString::number(newMotorTemperature));
}

void MainWindow::setMotorSpeed(uint16_t newMotorSpeed)
{
   ui->l_RPM_value->setText(QString::number(newMotorSpeed));
}


void MainWindow::on_pb_faults_clicked()
{
    // Oper fault page
    fault_dialog = std::make_shared<faultdialog>(one_second_producer, this);

    fault_dialog->show();
}

void MainWindow::on_pb_boatinfo_clicked()
{
    boatinfo_page = std::make_shared<BoatInfoWindow>(this);

    boatinfo_page->connectInformations(battery, command, generalinfo, motor);
#ifdef SANTOKA
    boatinfo_page->showFullScreen();
#elif MACOS
    this->hide();
    boatinfo_page->show();
#else
    boatinfo_page->show();
#endif
    //boatinfo_page.reset();
}
