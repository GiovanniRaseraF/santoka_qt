#include "hp_faultwarning.h"
#include "ui_hp_faultwarning.h"

hp_faultwarning::hp_faultwarning(QString name, QWidget *parent):
        QWidget(parent),
        ui(new Ui::hp_faultwarning)
    {
        ui->setupUi(this);

        ui->pushButton_2->setText(name);
    }

hp_faultwarning::~hp_faultwarning()
{
    delete ui;
}
