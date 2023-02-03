#include "batteryfullwidget.h"
#include "ui_batteryfullwidget.h"

batteryFullWidget::batteryFullWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::batteryFullWidget)
{
    ui->setupUi(this);
}

batteryFullWidget::~batteryFullWidget()
{
    delete ui;
}
