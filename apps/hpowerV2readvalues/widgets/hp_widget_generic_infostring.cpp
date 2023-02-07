#include "hp_widget_generic_infostring.h"
#include "ui_hp_widget_generic_infostring.h"

hp_widget_generic_infostring::hp_widget_generic_infostring(std::shared_ptr<filter> type_filter, QWidget *parent):
    QWidget(parent),
    ui(new Ui::hp_widget_generic_infostring)
{
    ui->setupUi(this);

    // create connection with filter
    actual_filter = type_filter;

}


hp_widget_generic_infostring::~hp_widget_generic_infostring()
{

    actual_filter.reset();
    delete ui;
}

void hp_widget_generic_infostring::setText(QString newtext)
{
    ui->l_info->setText(newtext);
}
