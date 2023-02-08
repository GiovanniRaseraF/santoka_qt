#include "hp_generalinfo.h"
#include "ui_hp_generalinfo.h"

hp_generalinfo::hp_generalinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hp_generalinfo)
{
    ui->setupUi(this);
}

hp_generalinfo::~hp_generalinfo()
{
    delete ui;
}
