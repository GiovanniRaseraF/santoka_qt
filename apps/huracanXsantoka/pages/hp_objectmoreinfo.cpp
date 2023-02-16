#include "hp_objectmoreinfo.h"
#include "ui_hp_objectmoreinfo.h"

hp_objectmoreinfo::hp_objectmoreinfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hp_objectmoreinfo)
{
    ui->setupUi(this);
}

hp_objectmoreinfo::~hp_objectmoreinfo()
{
    delete ui;
}

void hp_objectmoreinfo::on_pb_close_clicked()
{
   this->close();
}

