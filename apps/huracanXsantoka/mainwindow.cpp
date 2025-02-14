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
    canbus_producer = std::make_shared<canbus_thread>(nullptr, IF_CAN);

    canbus_producer->start();

    // Create filters
    logger = 		std::make_shared<filter>(canbus_producer, this);
    battery = 		std::make_shared<battery_filter>(canbus_producer, this);
    command = 		std::make_shared<command_filter>(canbus_producer, this);
    generalinfo = 	std::make_shared<generalinfo_filter>(canbus_producer, this);
    motor = 		std::make_shared<motor_filter>(canbus_producer, this);
    vehicle = 		std::make_shared<vehicle_filter>(canbus_producer, this);
    sniffer = 		std::make_shared<sniffer_filter>(canbus_producer, this);
    // Evbms filters
    ev0x351 = 		std::make_shared<evbms_0x351>(canbus_producer, this);
    ev0x355 = 		std::make_shared<evbms_0x355>(canbus_producer, this);
    ev0x356 = 		std::make_shared<evbms_0x356>(canbus_producer, this);
    ev0x358 = 		std::make_shared<evbms_0x358>(canbus_producer, this);
    ev0x359 = 		std::make_shared<evbms_0x359>(canbus_producer, this);
    ev0x35A = 		std::make_shared<evbms_0x35A>(canbus_producer, this);


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
            qDebug() << gp;
            // TODO: future support for different readings
            QString ssog_kmh = gp.split(",")[7];

            QString ssog_kt = gp.split(",")[5];

            if(ssog_kt != ""){
                std::stringstream ss{ssog_kt.toStdString()};
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
            ui->l_speed_value->setText(QString::number(sog, 'f', 0));
        }

        gpsOutput = "";
    }
}

void MainWindow::connectBatteryFilterToGraphics(){
    connect(battery.get(), SIGNAL(new_bat_SOC(uint8_t)), this, SLOT(setSOC(uint8_t)));
    connect(battery.get(), SIGNAL(new_bat_SOC(uint8_t)), this, SLOT(setSOCBatteryGraphics(uint8_t)));
    connect(battery.get(), SIGNAL(new_bat_Power(float)), this, SLOT(setPower(float)));
    connect(battery.get(), SIGNAL(new_bat_TimeToEmpty(uint16_t)), this, SLOT(setTTE(uint16_t)));

    connect(battery.get(), SIGNAL(new_bat_TotalVoltage(float)), this, SLOT(setBatteryVoltage(float)));
    connect(battery.get(), SIGNAL(new_bat_TotalCurrent(float)), this, SLOT(setBatteryCurrent(float)));
    connect(battery.get(), SIGNAL(new_bat_BatteryTemperature(uint8_t)), this, SLOT(setBatteryTemperature(uint8_t)));
    connect(battery.get(), SIGNAL(new_bat_BMSTemperature(uint8_t)), this, SLOT(setBMSTemperature(uint8_t)));
}

void MainWindow::connectVehicleFilterToGraphics(){
    connect(vehicle.get(), SIGNAL(new_vcl_mapInUse(uint8_t)), this, SLOT(setVehicleMapInUse(uint8_t)));
}

void MainWindow::connectMotorFilterToGraphics(){
    connect(motor.get(), SIGNAL(new_drv_motorSpeed(uint16_t)), this, SLOT(setMotorSpeed(uint16_t)));
    connect(motor.get(), SIGNAL(new_drv_motorTemperature(uint8_t)), this, SLOT(setMotorTemperature(uint8_t)));
    connect(motor.get(), SIGNAL(new_drv_powerTemperature(uint8_t)), this, SLOT(setPowerTemperature(uint8_t)));

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
        ui->l_tte->setText("-- h -- m");
    }else{
        ui->l_tte->setText(QString::number(h) + " h " + QString::number(m) + " m");
    }
}

void MainWindow::setVehicleMapInUse(uint8_t newMapInUse){
    bool IsHibrid = newMapInUse & 1;
    bool IsElectric = newMapInUse & 2;
    bool IsDiesel = newMapInUse & 4;

    // Text
    if(IsHibrid){
        ui->l_mapinuse->setText("Hibrid");
    }else if(IsElectric){
        ui->l_mapinuse->setText("Electric");
    }else if(IsDiesel){
        ui->l_mapinuse->setText("Diesel");
    }else{
        ui->l_mapinuse->setText("No Map");
    }

    // Image
    if(IsHibrid){
        ui->l_mapinuse_img->setStyleSheet("image: url(:/images/hibrid.png)");
    }else if(IsElectric){
        ui->l_mapinuse_img->setStyleSheet("image: url(:/images/electric.png)");
    }else if(IsDiesel){
        ui->l_mapinuse_img->setStyleSheet("image: url(:/images/diesel.png)");
    }else{
        ui->l_mapinuse_img->setStyleSheet("image: url(:/images/electric.png)");
    }

}

// Display graphics
void MainWindow::setSOC(uint8_t newSOC)
{
    ui->l_SOC_value->setText(QString::number(newSOC));
}

void MainWindow::setSOCBatteryGraphics(uint16_t newSOC)
{
    if(newSOC >= 100){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_100.png)");
    }else if (newSOC >= 80 && newSOC < 100){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_80.png)");
    }else if (newSOC >= 50 && newSOC < 80){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_60.png)");
    }else if (newSOC >= 40 && newSOC < 50){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_40.png)");
    }else if (newSOC >= 20 && newSOC < 40){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_20.png)");
    }else if (newSOC < 20){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_5.png)");
    }

    // Control if it is charging
}

void MainWindow::setPowerTemperature(uint8_t newPowerTemperature)
{
   ui->l_powertemp_value->setText(QString::number(newPowerTemperature));
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
   ui->l_motortemp_value->setText(QString::number(newMotorTemperature));
}
void MainWindow::setBatteryTemperature(uint8_t newBatteryTemperature)
{
   ui->l_battery_temp->setText(QString::number(newBatteryTemperature));
}

void MainWindow::setBMSTemperature(uint8_t newBMSTemperature)
{
   ui->l_bms_temp->setText(QString::number(newBMSTemperature));
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
        fault_dialog = std::make_shared<faultsandwarnings>(canbus_producer, this);
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

void MainWindow::on_pb_softwareinfo_clicked()
{
    if(softwareinfo_page == nullptr)
        softwareinfo_page = std::make_shared<softwareinfo>(this);

    softwareinfo_page->connectInformations(sniffer);
#ifdef SANTOKA
    softwareinfo_page->showFullScreen();
#else
    softwareinfo_page->show();
#endif
    return;
}

// evbms page
void MainWindow::on_pb_evbmspage_clicked()
{
   if(evbms_page == nullptr)
       evbms_page = std::make_shared<batterypage>(this);

   evbms_page->connectInformations(ev0x351, ev0x355, ev0x356, ev0x358, ev0x359, ev0x35A);
#ifdef SANTOKA
   evbms_page->showFullScreen();
#else
   evbms_page->show();
#endif
   return;
}

