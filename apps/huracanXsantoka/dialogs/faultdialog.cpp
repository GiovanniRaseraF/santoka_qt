#include "faultdialog.h"
#include "ui_faultdialog.h"

faultdialog::faultdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::faultdialog)
{
    ui->setupUi(this);
}

faultdialog::~faultdialog()
{
    delete ui;
}

void faultdialog::on_faultdialog_accepted()
{

}

void faultdialog::on_pushButton_51_clicked()
{
    this->close();
}

void faultdialog::getFaults(uint32_t newfaultmap)
{

}

void faultdialog::getWarnings(uint32_t newwarningsmap)
{

}

