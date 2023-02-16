#include "battery_moreinfopage.h"


battery_moreinfopage::battery_moreinfopage(QWidget *parent) : hp_objectmoreinfo(parent)
{
    // Specific for battery
    ui->l_objname->setText("Battery");
    ui->l_icon->setStyleSheet("image: url(:/images/battery.png);");
}
