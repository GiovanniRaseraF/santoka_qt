#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "counter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        Counter a, b;
        QObject::connect(&a, &Counter::valueChanged,
                         &b, &Counter::setValue);

        a.setValue(12);     // a.value() == 12, b.value() == 12
        b.setValue(48);     // a.value() == 12, b.value() == 48
}

MainWindow::~MainWindow()
{
    delete ui;
}
