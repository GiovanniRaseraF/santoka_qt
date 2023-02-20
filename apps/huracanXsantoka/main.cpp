#include "mainwindow.h"
#include <QApplication>
#include "displayer/templatedconverter.h"
#include <addons/huracanremotedongle.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    HuracanRemoteDongle d{nullptr};
    d.start();

#ifdef SANTOKA
    w.showFullScreen();
#else
    w.show();
#endif

    return a.exec();
}
