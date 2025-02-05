#include "batterypage.h"
#include "ui_batterypage.h"

batterypage::batterypage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::batterypage)
{
    ui->setupUi(this);
}

batterypage::~batterypage()
{
    delete ui;
}


void batterypage::connectInformations(PASSSHARED_NONULL (evbms_0x351, _ev0x351), PASSSHARED_NONULL (evbms_0x355, _ev0x355), PASSSHARED_NONULL (evbms_0x356, _ev0x356))
{
    ev0x351 = _ev0x351;
    ev0x355 = _ev0x355;
    ev0x356 = _ev0x356;

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

    // 0x355
    connect(ev0x356.get(), SIGNAL(new_ev_Voltage(float)), this, SLOT(setVoltage(float)));
    connect(ev0x356.get(), SIGNAL(new_ev_Current(float)), this, SLOT(setCurrent(float)));
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

void batterypage::setVoltage(float v){
    ui->l_voltage_value->setText(QString::number(v));
}
void batterypage::setCurrent(float v){
    ui->l_current_value->setText(QString::number(v));
}





