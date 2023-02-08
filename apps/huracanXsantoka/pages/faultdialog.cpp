#include "faultdialog.h"
#include <iostream>

faultdialog::faultdialog(QWidget *parent) : QDialog(parent)
{
   setupUi(this);

   // Setup informations
}

faultdialog::~faultdialog(){}

void faultdialog::on_pushButton_clicked()
{
    this->close();
}

