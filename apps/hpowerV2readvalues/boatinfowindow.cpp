#include "boatinfowindow.h"
#include "ui_boatinfowindow.h"

BoatInfoWindow::BoatInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BoatInfoWindow)
{
    ui->setupUi(this);
}

BoatInfoWindow::~BoatInfoWindow()
{
    delete ui;
}
