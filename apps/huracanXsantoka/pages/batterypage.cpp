#include "batterypage.h"
#include "ui_batterypage.h"
#include <QDebug>
#include <QPushButton>

batterypage::batterypage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::batterypage)
{
    ui->setupUi(this);

    // update datetime
    updateDatetime = new QTimer(nullptr);
    myProcess = new QProcess(nullptr);

    // battery
    battery_w = std::make_shared<battery_widget>(this);
    ui->battery_layout->addWidget(battery_w.get());

    // Timer
    connect(myProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readDateFromSystem()));
    connect(updateDatetime, SIGNAL(timeout()), this, SLOT(timeoutToUpdateDate()));
    timeoutToUpdateDate();
    readDateFromSystem();
    updateDatetime->start(1000);
}

batterypage::~batterypage()
{
    delete ui;
}

void batterypage::connectInformations(
        PASSSHARED_NONULL (evbms_0x351, _ev0x351),
        PASSSHARED_NONULL (evbms_0x355, _ev0x355),
        PASSSHARED_NONULL (evbms_0x356, _ev0x356),
        PASSSHARED_NONULL (evbms_0x358, _ev0x358),
        PASSSHARED_NONULL (evbms_0x359, _ev0x359),
        PASSSHARED_NONULL (evbms_0x35A, _ev0x35A)
)
{
    ev0x351 = _ev0x351;
    ev0x355 = _ev0x355;
    ev0x356 = _ev0x356;
    ev0x358 = _ev0x358;
    ev0x359 = _ev0x359;
    ev0x35A = _ev0x35A;

    // 0x351
    connect(ev0x351.get(), SIGNAL(new_ev_CharginVoltageLimit(float)), this, SLOT(setCharginVoltageLimit(float)));
    connect(ev0x351.get(), SIGNAL(new_ev_CharginCurrentLimit(float)), this, SLOT(setCharginCurrentLimit(float)));
    connect(ev0x351.get(), SIGNAL(new_ev_DischargeCurrentLimit(float)), this, SLOT(setDischargeCurrentLimit(float)));
    connect(ev0x351.get(), SIGNAL(new_ev_DischargeVoltageLimit(float)), this, SLOT(setDischargeVoltageLimit(float)));

    // 0x355
    connect(ev0x355.get(), SIGNAL(new_ev_SOC(uint16_t)), this, SLOT(setSOC(uint16_t)));
    connect(ev0x355.get(), SIGNAL(new_ev_SOH(uint16_t)), this, SLOT(setSOH(uint16_t)));
    connect(ev0x355.get(), SIGNAL(new_ev_ResidualDischargeTime(uint16_t)), this, SLOT(setResidualDischargeTime(uint16_t)));
    connect(ev0x355.get(), SIGNAL(new_ev_Capacity(uint16_t)), this, SLOT(setCapacity(uint16_t)));

    // 0x356
    connect(ev0x356.get(), SIGNAL(new_ev_Voltage(float)), this, SLOT(setVoltage(float)));
    connect(ev0x356.get(), SIGNAL(new_ev_Current(float)), this, SLOT(setCurrent(float)));
    connect(ev0x356.get(), SIGNAL(new_ev_Status(evBatteryStatus)), this, SLOT(setBatteryStatus(evBatteryStatus)));

    // 0x358
    connect(ev0x358.get(), SIGNAL(new_ev_MaxCellVoltage(uint16_t)), this, SLOT(setMaxCellVoltage(uint16_t)));
    connect(ev0x358.get(), SIGNAL(new_ev_ModuleMaxVoltage(uint8_t)), this, SLOT(setModuleMaxVoltage(uint8_t)));
    connect(ev0x358.get(), SIGNAL(new_ev_CellMaxVoltage(uint8_t)), this, SLOT(setCellMaxVoltage(uint8_t)));
    connect(ev0x358.get(), SIGNAL(new_ev_MinCellVoltage(uint16_t)), this, SLOT(setMinCellVoltage(uint16_t)));
    connect(ev0x358.get(), SIGNAL(new_ev_ModuleMinVoltage(uint8_t)), this, SLOT(setModuleMinVoltage(uint8_t)));
    connect(ev0x358.get(), SIGNAL(new_ev_CellMinVoltage(uint8_t)), this, SLOT(setCellMinVoltage(uint8_t)));


    // 0x359
    connect(ev0x359.get(), SIGNAL(new_ev_MaxTemperature(int16_t)), this, SLOT(setMaxTemperature(int16_t)));
    connect(ev0x359.get(), SIGNAL(new_ev_ModuleMaxTemp(uint8_t)), this, SLOT(setModuleMaxTemp(uint8_t)));
    connect(ev0x359.get(), SIGNAL(new_ev_CellMaxTemp(uint8_t)), this, SLOT(setCellMaxTemp(uint8_t)));
    connect(ev0x359.get(), SIGNAL(new_ev_MinTemperature(int16_t)), this, SLOT(setMinTemperature(int16_t)));
    connect(ev0x359.get(), SIGNAL(new_ev_ModuleMinTemp(uint8_t)), this, SLOT(setModuleMinTemp(uint8_t)));
    connect(ev0x359.get(), SIGNAL(new_ev_CellMinTemp(uint8_t)), this, SLOT(setCellMinTemp(uint8_t)));

    // 0x35A
    connect(ev0x35A.get(), SIGNAL(new_ev_WarningProtection(QVector<bool>)), this, SLOT(setWarningProtection(QVector<bool>)));

    // add graphics
    connect(ev0x355.get(), SIGNAL(new_ev_SOC(uint16_t)), battery_w.get(), SLOT(setSOC(uint16_t)));
    connect(ev0x356.get(), SIGNAL(new_ev_Status(evBatteryStatus)), battery_w.get(), SLOT(setBatteryStatus(evBatteryStatus)));
}

void batterypage::on_pb_close_clicked()
{
    this->hide();
}

// Display graphics
void batterypage::setSOC(uint16_t newSOC)
{
    ui->l_soc_value->setText(QString::number(newSOC));
}

void batterypage::setSOH(uint16_t newSOH)
{
    ui->l_soh_value->setText(QString::number(newSOH));
}

void batterypage::setResidualDischargeTime(uint16_t newRDT)
{
    ui->l_residual_value->setText(QString::number(newRDT));
}

void batterypage::setCapacity(uint16_t newC)
{
    ui->l_capacity_value->setText(QString::number(newC));
}
void batterypage::setCharginVoltageLimit(float v){
    ui->l_charge_voltage_limit_value->setText(QString::number(v));
}
void batterypage::setCharginCurrentLimit(float v){
    ui->l_charge_current_limit_value->setText(QString::number(v));
}
void batterypage::setDischargeCurrentLimit(float v){
    ui->l_discharge_current_limit_value->setText(QString::number(v));
}
void batterypage::setDischargeVoltageLimit(float v){
    ui->l_discharge_voltage_limit_value->setText(QString::number(v));
}

// 0x356
void batterypage::setVoltage(float v){
    ui->l_voltage_value->setText(QString::number(v));
}
void batterypage::setCurrent(float v){
    ui->l_current_value->setText(QString::number(v));
}
void batterypage::setBatteryStatus(evBatteryStatus s){
    status = s;
}
// 0x358
void batterypage::setMaxCellVoltage(uint16_t v){
    ui->l_max_cell_voltage_value->setText(QString::number(v));
}
void batterypage::setModuleMaxVoltage(uint8_t v){
    ui->l_max_v_mod_value->setText(QString::number(v));
}
void batterypage::setCellMaxVoltage(uint8_t v){
    ui->l_max_v_mod_value->setText(QString::number(v));
}
void batterypage::setMinCellVoltage(uint16_t v){
    ui->l_min_cell_voltage_value->setText(QString::number(v));
}
void batterypage::setModuleMinVoltage(uint8_t v){
    ui->l_min_v_mod_value->setText(QString::number(v));
}
void batterypage::setCellMinVoltage(uint8_t v){
    ui->l_min_v_cell_value->setText(QString::number(v));
}

// 0x359
void batterypage::setMaxTemperature(int16_t v){
    ui->l_max_temperatue_value->setText(QString::number(v));
}
void batterypage::setModuleMaxTemp(uint8_t v){
    ui->l_max_t_mod_value->setText(QString::number(v));
}
void batterypage::setCellMaxTemp(uint8_t v){
    ui->l_max_t_cell_value->setText(QString::number(v));
}
void batterypage::setMinTemperature(int16_t v){
    ui->l_min_temperature_value->setText(QString::number(v));
}
void batterypage::setModuleMinTemp(uint8_t v){
    ui->l_min_t_mod_value->setText(QString::number(v));
}
void batterypage::setCellMinTemp(uint8_t v){
    //ui->
    ui->l_min_t_cell_value->setText(QString::number(v));
}

// 0x35A
void batterypage::setWarningProtection(QVector<bool> v){
    ui->lv_primaryprotection->reset();
    ui->lv_primaryprotection->clear();
    ui->lv_alarms->reset();
    ui->lv_alarms->clear();

    // add warnings and faults
    for(int i = 0; i < v.size(); i++){
       bool active = v[i];
       if(active){
        auto message = WP_GLOBAL[i];
        auto str = message.first;
        auto type = message.second;

        // add to graphics
        switch (type) {
        case PRIMARY_PROTECTION:
            ui->lv_primaryprotection->addItem(str);
            break;
        case ALARM:
            ui->lv_alarms->addItem(str);
            break;
        default:
            qDebug() << "Impossible type of protection error";
            break;
        }
       }
    }
}

void batterypage::timeoutToUpdateDate(){
    QStringList arguments;
    myProcess->start("date", arguments);
}

void batterypage::readDateFromSystem(){
    ui->l_date->setText(myProcess->readAllStandardOutput());

    myProcess->terminate();
    myProcess->close();
    myProcess->kill();
}


