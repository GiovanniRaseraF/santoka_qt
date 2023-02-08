#include "batteryindicator.h"
#include "ui_batteryindicator.h"

BatteryIndicator::BatteryIndicator(QWidget *parent) : QDialog(parent),  ui(new Ui::BatteryIndicator)
{

}
BatteryIndicator::~BatteryIndicator(){
    delete ui;
}
