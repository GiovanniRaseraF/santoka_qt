#include "batterywidget.h"
#include "ui_batterywidget.h"

batterywidget::batterywidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::batterywidget)
{
    ui->setupUi(this);
}

batterywidget::~batterywidget()
{
    delete ui;
}
