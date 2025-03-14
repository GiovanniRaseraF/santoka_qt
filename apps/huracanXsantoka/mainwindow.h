#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>

#include <memory>
#include <sstream>

#include "dataproducer.h"

#include "displayer/battery_filter.h"
#include "displayer/command_filter.h"
#include "displayer/generalinfo_filter.h"
#include "displayer/motor_filter.h"
#include "displayer/vehicle_filter.h"
#include "displayer/sniffer.h"
#include "displayer/evbms_0x351_filter.h"
#include "displayer/evbms_0x355_filter.h"
#include "displayer/evbms_0x356_filter.h"
#include "displayer/evbms_0x358_filter.h"
#include "displayer/evbms_0x359_filter.h"
#include "displayer/evbms_0x35A_filter.h"

#include "pages/boatinfowindow.h"
#include "pages/hp_objectmoreinfo.h"
#include "pages/faultsandwarnings.h"
#include "pages/softwareinfo.h"
#include "pages/batterypage.h"

#include "dialogs/faultdialog.h"

namespace Ui {
class MainWindow;
}
Q_DECLARE_METATYPE(struct can_frame)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connectBatteryFilterToGraphics();
    void connectMotorFilterToGraphics();
    void connectVehicleFilterToGraphics();

public slots:
    void timeoutToUpdateDate();
    void readDateFromSystem();
    void readSubProcess();
    void setVehicleMapInUse(uint8_t newMapInUse);

    void setTTE(uint16_t newTTE);
    void setSOC(uint8_t newSOC);
    void setPowerTemperature(uint8_t newPowerTemperature);
    void setPower(float newPower);
    void setBatteryVoltage(float newVoltage);
    void setBatteryCurrent(float newCurrent);

    void setSpeed(uint16_t newSpeed);
    void setMotorTemperature(uint8_t newMotorTemperature);
    void setBatteryTemperature(uint8_t newBatteryTemperature);
    void setBMSTemperature(uint8_t newBMSTemperature);
    void setMotorSpeed(uint16_t newMotorSpeed);

    void setWarningProtectionCounter(QVector<bool> w);

private slots:
    void on_pb_faults_clicked();

    void on_pb_boatinfo_clicked();

    void on_pb_battery_clicked();

    void on_pb_softwareinfo_clicked();

    void on_pb_evbms_wpcount_clicked();

private:
    Ui::MainWindow *ui;

    QProcess *myProcess;
    QTimer *updateDatetime;

    QProcess *gpsProcess;
    QString gpsOutput;

    // Can bus producer thread
    std::shared_ptr<canbus_thread> canbus_producer;

    // Displayer
    std::shared_ptr<filter> logger;
    std::shared_ptr<battery_filter> battery;
    std::shared_ptr<command_filter> command;
    std::shared_ptr<generalinfo_filter> generalinfo;
    std::shared_ptr<motor_filter> motor;
    std::shared_ptr<vehicle_filter> vehicle;
    std::shared_ptr<sniffer_filter> sniffer;
    // evbms
    std::shared_ptr<evbms_0x351> ev0x351;
    std::shared_ptr<evbms_0x355> ev0x355;
    std::shared_ptr<evbms_0x356> ev0x356;
    std::shared_ptr<evbms_0x358> ev0x358;
    std::shared_ptr<evbms_0x359> ev0x359;
    std::shared_ptr<evbms_0x35A> ev0x35A;

    // Pages:
    std::shared_ptr<BoatInfoWindow> boatinfo_page;
    std::shared_ptr<faultsandwarnings> fault_dialog;
    std::shared_ptr<hp_objectmoreinfo> battery_moreinfo_page;
    std::shared_ptr<softwareinfo> softwareinfo_page;
    std::shared_ptr<batterypage> evbms_page;

    // battery
    std::shared_ptr<battery_widget> battery_w;

    // Graphics
    bool toggle_ev_error_color = false;
};

#endif // MAINWINDOW_H
