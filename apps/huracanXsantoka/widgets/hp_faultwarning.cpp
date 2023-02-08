#include "hp_faultwarning.h"
#include "ui_hp_faultwarning.h"

hp_faultwarning::hp_faultwarning(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hp_faultwarning)
{
    ui->setupUi(this);
}

hp_faultwarning::~hp_faultwarning()
{
    delete ui;
}
