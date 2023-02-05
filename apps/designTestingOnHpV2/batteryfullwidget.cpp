#include "batteryfullwidget.h"
#include "ui_batteryfullwidget.h"
#include <sstream>

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

    // Testing style change
    std::stringstream style{""};
    style << "border-radius: 150px;background-color: qconicalgradient(cx:0, cy:" << ((float)newvalue) / 100 << ", angle:90, stop:0.700 rgba(255, 0, 127, 0), stop:0.75 rgba(85, 170, 255, 255));";

    std::string s = style.str();
    QString st{s.c_str()};
    std::cout << s << std::endl;

    ui->frmProgressBar->setStyleSheet(st);
}
