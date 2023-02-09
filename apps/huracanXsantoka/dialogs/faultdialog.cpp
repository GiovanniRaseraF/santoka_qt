#include "faultdialog.h"
#include "ui_faultdialog.h"

faultdialog::faultdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::faultdialog)
{
    ui->setupUi(this);

    // Add faults dinamics
    int c = 0x506;
    std::map<int, std::tuple<QString, QString>> vals{
        {1, {"fault", "Ciao"}},
        {2, {"fault", "Bella"}},
        {3, {"fault", "io"}}
    };
    packets[0].loaddata(c, vals);


}

faultdialog::~faultdialog()
{
    delete ui;
}

void faultdialog::on_faultdialog_accepted()
{

}

void faultdialog::on_pb_close_clicked()
{
    this->close();
}

void faultdialog::getFaults(uint32_t newfaultmap)
{

}

void faultdialog::getWarnings(uint32_t newwarningsmap)
{

}

