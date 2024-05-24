#include "softwareinfo.h"
#include "ui_softwareinfo.h"

#include <QDebug>

softwareinfo::softwareinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::softwareinfo)
{
    ui->setupUi(this);

    // debug
    qDebug() << "GIT_VERSION: " << GIT_VERSION;
    qDebug() << "BUILD_DATE: " << BUILD_DATE ;
    qDebug() << "COMPILER_VERSION: " << __VERSION__ << " - " << COMPILER_VERSION;

    // info
    ui->l_git_version->setText(GIT_VERSION);
    ui->l_build_date->setText(BUILD_DATE);
    ui->l_compiler_version->setText(COMPILER_VERSION);
}

softwareinfo::~softwareinfo()
{
    delete ui;
}

void softwareinfo::on_pb_close_clicked()
{
   this->close();
}

