#include "battery_widget.h"
#include "ui_battery_widget.h"
#include <QDebug>

battery_widget::battery_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::battery_widget)
{
    ui->setupUi(this);

    // internal graphics timer
    updateDatetime = std::make_shared<QTimer>(nullptr);
    updateDatetime->start(100);
}

battery_widget::~battery_widget()
{
    delete ui;
}

void battery_widget::setSOC(uint16_t newSOC){
    QString appendEnd = ".png);";

    if(status == CHARGING){
        // Do nothing here
    }else{
    // Set graphics
    if(newSOC >= 100){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_100"+appendEnd);
    }else if (newSOC >= 80 && newSOC < 100){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_80"+appendEnd);
    }else if (newSOC >= 50 && newSOC < 80){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_60"+appendEnd);
    }else if (newSOC >= 40 && newSOC < 50){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_40"+appendEnd);
    }else if (newSOC >= 20 && newSOC < 40){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_20"+appendEnd);
    }else if (newSOC < 20){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_5"+appendEnd);
    }
    }
}

void battery_widget::setBatteryStatus(evBatteryStatus s){
    status = s;
    if(status == CHARGING && !connected){
        connected = true;
        connect(updateDatetime.get(), SIGNAL(timeout()), this, SLOT(timeoutToUpdateGraphics()));
    }else{
        connected = false;
        disconnect(updateDatetime.get(), SIGNAL(timeout()), this, SLOT(timeoutToUpdateGraphics()));
    }
}

void battery_widget::timeoutToUpdateGraphics(){
    QString appendEnd = "_charging.png);";
    if(internalSOCRepresentation >= 100){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_100"+appendEnd);
    }else if (internalSOCRepresentation >= 80 && internalSOCRepresentation < 100){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_80"+appendEnd);
    }else if (internalSOCRepresentation >= 50 && internalSOCRepresentation < 80){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_60"+appendEnd);
    }else if (internalSOCRepresentation >= 40 && internalSOCRepresentation < 50){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_40"+appendEnd);
    }else if (internalSOCRepresentation >= 20 && internalSOCRepresentation < 40){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_20"+appendEnd);
    }else if (internalSOCRepresentation < 20){
        ui->l_battery_graphics->setStyleSheet("image: url(:/images/b_5"+appendEnd);
    }
    internalSOCRepresentation += 5;
    if(internalSOCRepresentation > 150){
        internalSOCRepresentation = 0;
    }
}
