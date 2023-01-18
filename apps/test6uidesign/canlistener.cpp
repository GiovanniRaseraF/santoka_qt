#include "canlistener.h"
#include <iostream>
#include <QTextStream>
#include <cstdlib>
#include <stdio.h>
#include <QDebug>
#include <QString>
#include <sstream>
#include <string>

// Example only print to qInfo()
void CanPrintAll::update(struct can_frame frame){
    QString ss;
    for(int i = 0; i < frame.can_dlc; i++){
        uint8_t v = frame.data[i];
        ss += " " + QString::number(v);
    }

    qInfo() << "ID: " << frame.can_id << " DATA:" << ss;
}

CanPrintAll::CanPrintAll()
    : CanListener("printall", std::vector<int>{ALLCHANNELS})
{

}

