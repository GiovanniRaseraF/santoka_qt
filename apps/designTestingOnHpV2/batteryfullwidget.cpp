#include "batteryfullwidget.h"
#include "ui_batteryfullwidget.h"

batteryFullWidget::batteryFullWidget(std::shared_ptr<battery_filter> _battery, QWidget *parent):
    QWidget(parent),
    ui(new Ui::batteryFullWidget)
{
    battery = _battery;

    connect(battery.get(), SIGNAL(new_bat_SOC(uint8_t)), this, SLOT(setSOC(uint8_t)));

    ui->setupUi(this);
}


batteryFullWidget::~batteryFullWidget()
{
    disconnect(battery.get(), SIGNAL(new_bat_SOC(uint8_t)), this, SLOT(setSOC(uint8_t)));
    delete ui;
}

void batteryFullWidget::setSOC(uint8_t newvalue)
{
    ui->lblPercentage->setText(QString::number(newvalue));
    ui->
}
