#include "hp_faultdesing.h"
#include <iostream>

hp_faultdesing::hp_faultdesing(QString name, int _canchannel, int bit, QWidget *parent):hp_faultwarning(name, _canchannel, bit, parent)
{
}

void hp_faultdesing::activatecolor(int c, int b, bool active)
{
    if(c == hp_faultwarning::canchannel && b == hp_faultwarning::bit){
       if(active){
            ui->pushButton_2->setStyleSheet("background-color:rgb(100, 0, 0);color:rgb(0,0,0);");
       }else{
            ui->pushButton_2->setStyleSheet("background-color:rgb(154, 153, 150);color:rgb(255,255,255);");
       }
    }
}
