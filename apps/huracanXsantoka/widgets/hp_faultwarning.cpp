#include "hp_faultwarning.h"
#include "ui_hp_faultwarning.h"

hp_faultwarning::hp_faultwarning(QString name, int _canchannel, int _bit, QWidget *parent):
        QWidget(parent),
        ui(new Ui::hp_faultwarning)
{
        ui->setupUi(this);

        canchannel = _canchannel;
        bit = _bit;
        ui->pushButton_2->setText(name);
}

hp_faultwarning::~hp_faultwarning()
{
    delete ui;
}

void hp_faultwarning::activatecolor(int c, int b, bool active) {
    if(canchannel == c && bit == b){
        if(active){
            ui->pushButton_2->setStyleSheet("background-color:rgb(100, 0, 0);color:rgb(0,0,0);");
        }
        else {
            ui->pushButton_2->setStyleSheet("background-color:rgb(154, 153, 150);color:rgb(255,255,255);");
        }
    }
}
