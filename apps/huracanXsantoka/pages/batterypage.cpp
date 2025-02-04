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


void batterypage::connectInformations(PASSSHARED_NONULL (evbms_0x351, _ev0x351), PASSSHARED_NONULL (evbms_0x355, _ev0x355))
{
    ev0x351 = _ev0x351;
    ev0x355 = _ev0x355;

    connect(ev0x355.get(), SIGNAL(new_ev_SOC(uint16_t)), this, SLOT(setSOC(uint16_t)));
}


void batterypage::on_pb_close_clicked()
{
    this->hide();
}

// Display graphics
void batterypage::setSOC(uint16_t newSOC)
{
    ui->l_SOC_value->setText(QString::number(newSOC));
}
