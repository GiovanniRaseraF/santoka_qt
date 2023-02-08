#include "hp_batterydesign.h"
#include "ui_hp_batterydesign.h"

hp_batterydesign::hp_batterydesign(std::shared_ptr<battery_filter> battery, QWidget *parent):
    QWidget(parent),
    ui(new Ui::hp_batterydesign)
{
    ui->setupUi(this);

    this->battery = battery;
    connect(battery.get(), SIGNAL(to_QString(QString)), this, SLOT(setText(QString)));
}

hp_batterydesign::~hp_batterydesign()
{
    disconnect(battery.get(), SIGNAL(to_QString(QString)), this, SLOT(setText(QString)));
    battery.reset();
    delete ui;
}

void hp_batterydesign::setText(QString newtext)
{
    ui->l_info->setText(newtext);
}
