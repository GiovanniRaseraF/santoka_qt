/*
 * Author: Giovanni Rasera
 * GitHub: www.github.com/GiovanniRaseraF
 */

/*
 * Description: HMI for Huracan Marine, Santoka display
 */

#include "mainwindow.h"
#include <QApplication>
#include <QtSystemInfo/QtSystemInfo>
#include <batteryindicator.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    BatteryIndicator b(nullptr);

    w.showFullScreen();

    return a.exec();
}
