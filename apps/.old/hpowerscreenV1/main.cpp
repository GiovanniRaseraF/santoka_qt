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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.showFullScreen();

    return a.exec();
}
