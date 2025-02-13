#include "softwareinfo.h"
#include "ui_softwareinfo.h"

#include <QDebug>
#include <iostream>

softwareinfo::softwareinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::softwareinfo)
{
    ui->setupUi(this);

    // info
    ui->l_git_version->setText(GIT_VERSION);
    ui->l_git_branch->setText(GIT_BRANCH);
    ui->l_build_date->setText(BUILD_DATE);
    QString typeVersion = "debug";
    if (SOFTWARE_VERSION % 2 == 0){
       typeVersion = "release";
    }
    ui->l_software_version->setText(QString::number(SOFTWARE_VERSION) + " - " + typeVersion);
    ui->l_build_date->setText(BUILD_DATE);
#ifdef SANTOKA
    ui->l_compiler_version->setText("imx6guf-guf-linux-gnueabi");
#else
    ui->l_compiler_version->setText(COMPILER_VERSION);

    // debug
    qDebug() << "GIT_VERSION: " << GIT_VERSION;
    qDebug() << "BUILD_DATE: " << BUILD_DATE ;
    qDebug() << "COMPILER_VERSION: " << __VERSION__ << " - " << COMPILER_VERSION;
#endif
}

softwareinfo::~softwareinfo()
{
    delete ui;
}

void softwareinfo::connectInformations(
        PASSSHARED_NONULL (sniffer_filter, _sniffer))
{
    mysniffer = _sniffer;
    connect(mysniffer.get(), SIGNAL(new_canpacket(QString)), this, SLOT(on_candata(QString)));
}

void softwareinfo::on_candata(QString data){
    std::cout << data.toStdString() << std::endl;
    updateCandumpText(data);
}

void softwareinfo::updateCandumpText(QString data){
    ui->candump_text->append(data);
    appendCount ++;
}

void softwareinfo::clearDump(){
    ui->candump_text->clear();
}

void softwareinfo::on_pb_close_clicked()
{
    ui->candump_text->clear();
    disconnect(mysniffer.get(), SIGNAL(new_canpacket(QString)), this, SLOT(on_candata(QString)));
    this->close();
}


void softwareinfo::on_softwareinfo_accepted()
{
    ui->candump_text->clear();
    disconnect(mysniffer.get(), SIGNAL(new_canpacket(QString)), this, SLOT(on_candata(QString)));
    this->close();
}


void softwareinfo::on_softwareinfo_rejected()
{
    ui->candump_text->clear();
    disconnect(mysniffer.get(), SIGNAL(new_canpacket(QString)), this, SLOT(on_candata(QString)));
    this->close();
}

