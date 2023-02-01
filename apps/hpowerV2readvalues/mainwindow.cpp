#include "mainwindow.h"
#include "pages/faultdialog.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qRegisterMetaType<struct can_frame>();
    ui->setupUi(this);

    // Create and start canbus on sepatate thread
    canbus_producer = std::make_shared<fake_canbus_thread>("hello", nullptr);
    std::cout << canbus_producer->getinfo() << std::endl;

    canbus_producer->start();

    // Create filters
    battery = std::make_shared<battery_filter>(canbus_producer, this);
    logger = std::make_shared<filter>(canbus_producer, this);

    // Connect data to Graphics
    connectBatteryFilterToGraphics();

    // pages

}

void MainWindow::connectBatteryFilterToGraphics(){
    connect(battery.get(), SIGNAL(new_bat_SOC(uint8_t)), this, SLOT(setSOC(uint8_t)));
    connect(battery.get(), SIGNAL(new_bat_Power(float)), this, SLOT(setPower(float)));
    connect(battery.get(), SIGNAL(new_bat_BatteryTemperature(uint8_t)), this, SLOT(setPowerTemperature(uint8_t)));
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

void MainWindow::on_pushButton_2_clicked()
{
    faultdialog *ff = new faultdialog(this);

    ff->show();
}
