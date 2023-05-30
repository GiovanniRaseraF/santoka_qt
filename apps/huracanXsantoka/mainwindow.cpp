#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDateTime>
#include <QProcess>

#include "pages/battery_moreinfopage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qRegisterMetaType<struct can_frame>();
    ui->setupUi(this);

    // Create and start canbus on sepatate thread
#ifdef SANTOKA
    canbus_producer = std::make_shared<canbus_thread>(nullptr);
#else
    canbus_producer = 		std::make_shared<fake_canbus_thread>("fake can producer", 10, nullptr);
    one_second_producer = 	std::make_shared<fake_canbus_thread>("fake 1 second", 50, nullptr);
    one_second_producer->start();
#endif

    canbus_producer->start();

    // Create filters
    logger = 		std::make_shared<filter>(canbus_producer, this);
    battery = 		std::make_shared<battery_filter>(canbus_producer, this);
    command = 		std::make_shared<command_filter>(canbus_producer, this);
    generalinfo = 	std::make_shared<generalinfo_filter>(canbus_producer, this);
    motor = 		std::make_shared<motor_filter>(canbus_producer, this);
    vehicle = 		std::make_shared<vehicle_filter>(canbus_producer, this);

    // Connect data to Graphics
    connectBatteryFilterToGraphics();
    connectMotorFilterToGraphics();
    connectVehicleFilterToGraphics();
    // pages
    // boat info

    // update datetime
    updateDatetime = new QTimer(nullptr);
    myProcess = new QProcess(nullptr);

    connect(myProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readDateFromSystem()));
    connect(updateDatetime, SIGNAL(timeout()), this, SLOT(timeoutToUpdateDate()));

    updateDatetime->start(1000);

    // connect to GPS
#ifdef SANTOKA
    gpsProcess = new QProcess(nullptr);
    gpsProcess->start("cat /dev/ttyACM0");
    connect(gpsProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readSubProcess()));
#else
    qDebug() << "fake GPS with no data";
#endif
}

float parseSOG(QString gpsdata){
    QStringList pieces = gpsdata.split( "\n" );
    float sum = 0;
    int count = 0;

    for(auto gp : pieces){
        if(gp != "" && gp.contains("GPVTG")){
            QString ssog = gp.split(",")[7];

            if(ssog != ""){
                std::stringstream ss{ssog.toStdString()};
                float conv = 0;
                ss >> conv;

                sum += conv;
                count++;
            }
        }
    }

    if(count > 0){
        return sum / count;
    }

    return -1;
}

void MainWindow::readSubProcess(){
    gpsOutput.append(gpsProcess->readAllStandardOutput());

    if (gpsOutput.endsWith("\n")) {
        // parse gps informations
        float sog = parseSOG(gpsOutput);

        // -1 if no data was converted
        if(sog >= 0){
            ui->l_speed_value->setText(QString::number(sog, 'f', 1));
        }

        gpsOutput = "";
    }
}

void MainWindow::connectBatteryFilterToGraphics(){
    connect(battery.get(), SIGNAL(new_bat_SOC(uint8_t)), this, SLOT(setSOC(uint8_t)));
    connect(battery.get(), SIGNAL(new_bat_Power(float)), this, SLOT(setPower(float)));
    connect(battery.get(), SIGNAL(new_bat_BatteryTemperature(uint8_t)), this, SLOT(setPowerTemperature(uint8_t)));
    connect(battery.get(), SIGNAL(new_bat_TimeToEmpty(uint16_t)), this, SLOT(setTTE(uint16_t)));

    connect(battery.get(), SIGNAL(new_bat_TotalVoltage(float)), this, SLOT(setBatteryVoltage(float)));
    //connect(battery.get(), SIGNAL(new_bat_TotalCurrent(float)), this, SLOT(setBatteryCurrent(float)));
    connect(motor.get(), SIGNAL(new_drv_motorCurrent(float)), this, SLOT(setBatteryCurrent(float)));
}

void MainWindow::connectVehicleFilterToGraphics(){
    connect(vehicle.get(), SIGNAL(new_vcl_mapInUse(uint8_t)), this, SLOT(setVehicleMapInUse(uint8_t)));
}

void MainWindow::connectMotorFilterToGraphics(){
    connect(motor.get(), SIGNAL(new_drv_motorSpeed(uint16_t)), this, SLOT(setMotorSpeed(uint16_t)));
    connect(motor.get(), SIGNAL(new_drv_motorTemperature(uint8_t)), this, SLOT(setMotorTemperature(uint8_t)));

    // TODO: connect to gps from antenna
    //connect(gps, SIGNAL(newposition), this, SLOT(displayspeed));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeoutToUpdateDate(){
    QStringList arguments;
    myProcess->start("date", arguments);
}

void MainWindow::readDateFromSystem(){
    ui->l_date->setText(myProcess->readAllStandardOutput());

    myProcess->terminate();
    myProcess->close();
    myProcess->kill();
}

void MainWindow::setTTE(uint16_t newTTE){
    uint16_t h = newTTE / 60;
    uint16_t m = newTTE % 60;

    if(h >= 100){
        ui->l_tte->setText("-- h -- min");
    }else{
        ui->l_tte->setText(QString::number(h) + " h " + QString::number(m) + " min");
    }
}

void MainWindow::setVehicleMapInUse(uint8_t newMapInUse){
    bool IsHibrid = newMapInUse & 1;
    bool IsElectric = newMapInUse & 2;
    bool IsDiesel = newMapInUse & 4;

    if(IsHibrid){
        ui->l_mapinuse->setText("Hibrid");
    }else if(IsElectric){
        ui->l_mapinuse->setText("Electric");
    }else if(IsDiesel){
        ui->l_mapinuse->setText("Diesel");
    }else{
        ui->l_mapinuse->setText("No Map");
    }
}

// Display graphics
void MainWindow::setSOC(uint8_t newSOC)
{
    ui->l_SOC_value->setText(QString::number(newSOC));
}

void MainWindow::setPowerTemperature(uint8_t newPowerTemperature)
{
   ui->l_powertemp_value->setText(QString::number(newPowerTemperature, 'f', 1));
}

void MainWindow::setPower(float newPower)
{
   ui->l_power_value->setText(QString::number(newPower, 'f', 1));
}

void MainWindow::setBatteryVoltage(float newVoltage){
   ui->l_battery_voltage->setText(QString::number(newVoltage, 'f', 1));
}

void MainWindow::setBatteryCurrent(float newCurrent){
   ui->l_battery_current->setText(QString::number(newCurrent, 'f', 1));
}

void MainWindow::setSpeed(uint16_t newSpeed)
{
   ui->l_speed_value->setText(QString::number(newSpeed));
}

void MainWindow::setMotorTemperature(uint8_t newMotorTemperature)
{
   ui->l_motortemp_value->setText(QString::number(newMotorTemperature, 'f', 1));
}

void MainWindow::setMotorSpeed(uint16_t newMotorSpeed)
{
   ui->l_RPM_value->setText(QString::number(newMotorSpeed));
}


void MainWindow::on_pb_faults_clicked()
{
    // Oper fault page
    if(fault_dialog == nullptr)
#ifdef SANTOKA
        fault_dialog = std::make_shared<faultsandwarnings>(canbus_producer, this);
    fault_dialog->showFullScreen();
#else
        fault_dialog = std::make_shared<faultsandwarnings>(one_second_producer, this);
    fault_dialog->show();
#endif

}

void MainWindow::on_pb_boatinfo_clicked()
{
    if(boatinfo_page == nullptr)
        boatinfo_page = std::make_shared<BoatInfoWindow>(this);

    boatinfo_page->connectInformations(battery, command, generalinfo, motor);
#ifdef SANTOKA
    boatinfo_page->showFullScreen();
#else
    boatinfo_page->show();
#endif
}

void MainWindow::on_pb_battery_clicked()
{
    battery_moreinfo_page = std::make_shared<battery_moreinfopage>(this);
#ifdef SANTOKA
    battery_moreinfo_page->showFullScreen();
#else
    battery_moreinfo_page->show();
#endif
}
