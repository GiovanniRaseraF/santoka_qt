#include "battery.h"
#include "ui_battery.h"

battery::battery(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::battery)
{
    ui->setupUi(this);
}

battery::~battery()
{
    delete ui;
}
