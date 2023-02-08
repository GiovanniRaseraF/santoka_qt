#include "hp_widget_generic_infostring.h"
#include "ui_hp_widget_generic_infostring.h"

hp_widget_generic_infostring::hp_widget_generic_infostring(QString _name, std::shared_ptr<filter> type_filter, QWidget *parent):
    QWidget(parent),
    ui(new Ui::hp_widget_generic_infostring),
    name{_name}
{
    ui->setupUi(this);
    ui->l_name->setText("    " + name);

    // create connection with filter
    actual_filter = type_filter;
    connect(actual_filter.get(), SIGNAL(to_QString(QString)), this, SLOT(setText(QString)));
}

hp_widget_generic_infostring::~hp_widget_generic_infostring()
{
    disconnect(actual_filter.get(), SIGNAL(to_QString(QString)), this, SLOT(setText(QString)));

    actual_filter.reset();

    delete ui;
}

void hp_widget_generic_infostring::setText(QString newtext)
{
    ui->l_info->setText(newtext);
}
