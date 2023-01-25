#include "batteryindicator.h"
#include "ui_batteryindicator.h"

BatteryIndicator::BatteryIndicator(QWidget *parent) : QDialog(parent),  ui(new Ui::BatteryIndicator)
{
     //ui->setupUi(this);

     //ui->batteryLevelBar->setValue(99);

     //connect(deviceInfo, SIGNAL(batteryLevelChanged(int)), ui->batteryLevelBar, SLOT(setValue(int)));
}
BatteryIndicator::~BatteryIndicator(){
    delete ui;
}
