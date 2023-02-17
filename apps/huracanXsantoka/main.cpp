#include "mainwindow.h"
#include <QApplication>
#include "displayer/templatedconverter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

#ifdef SANTOKA
    w.showFullScreen();
#else
    w.show();
#endif

    return a.exec();
}
