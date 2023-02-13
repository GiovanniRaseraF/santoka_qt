#include "faultdialog.h"
#include "ui_faultdialog.h"
#include "loaders/hp_faultwarning_loader.h"

faultdialog::faultdialog(std::shared_ptr<canbus_thread> canbus, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::faultdialog)
{
    ui->setupUi(this);

    // loading faults
    hp_faultwarning_loader faultloader(this);
    faultloader.loadfromfile(":/configuration/configuration.json");

    faults = std::move(faultloader.faults);
    warnings = std::move(faultloader.warnings);
    packets = std::move(faultloader.packets);

    for(auto p : packets){
        p->addproducer(canbus);
    }

    int count = 0;
    for(auto f : faults){
        if (count < 13)
            ui->vl_fault1->addWidget(f.get());
        if (count >= 14 && count < 28)
            ui->vl_fault2->addWidget(f.get());

        count ++;
    }

    count = 0;
    for(auto w : warnings){
        if (count < 13)
            ui->vl_warnings1->addWidget(w.get());
        if (count >= 14 && count < 28)
            ui->vl_warnings2->addWidget(w.get());

        count ++;
    }

    for(auto f : faults){
        connect(packets[0].get(), SIGNAL(updatebit(int, int, bool)), f.get(), SLOT(activatecolor(int, int, bool)));
    }
    for(auto w : warnings){
        connect(packets[0].get(), SIGNAL(updatebit(int, int, bool)), w.get(), SLOT(activatecolor(int, int, bool)));
    }
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
    this->hide();
}
