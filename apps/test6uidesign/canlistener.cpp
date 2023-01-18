#include "canlistener.h"
#include <iostream>
#include <QTextStream>
#include <cstdlib>
#include <stdio.h>
#include <QDebug>

// Example only print to qInfo()
void CanPrintAll::update(struct can_frame frame){
    qInfo() << "ID: " << frame.can_id << " DATA:";
    for(int i = 0; i < frame.can_dlc; i++){
        uint8_t v = frame.data[i];
        qInfo() << " " << v;
    }
    qInfo() <<  "\n";
}

CanPrintAll::CanPrintAll()
    : CanListener("printall", std::vector<int>{ALLCHANNELS})
{

}

