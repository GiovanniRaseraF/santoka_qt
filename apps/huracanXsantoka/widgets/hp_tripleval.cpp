#include "hp_tripleval.h"
#include "ui_hp_tripleval.h"

hp_tripleval::hp_tripleval(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hp_tripleval)
{
    ui->setupUi(this);
}

hp_tripleval::~hp_tripleval()
{
    delete ui;
}
