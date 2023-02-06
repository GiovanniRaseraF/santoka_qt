#include "hp_motordesign.h"
#include "ui_hp_motordesign.h"

hp_motordesign::hp_motordesign(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hp_motordesign)
{
    ui->setupUi(this);
}

hp_motordesign::~hp_motordesign()
{
    delete ui;
}
