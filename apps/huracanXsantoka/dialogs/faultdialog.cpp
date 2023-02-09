#include "faultdialog.h"
#include "ui_faultdialog.h"

faultdialog::faultdialog(std::shared_ptr<canbus_thread> canbus, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::faultdialog)
{
    ui->setupUi(this);

    std::shared_ptr<singlefaultwarningpacket> s = std::make_shared<singlefaultwarningpacket>();
    s->canchannel = 0x506;
    s->importantbits = {1, 2, 3, 4, 6};
    s->addproducer(canbus);
    packets.push_back(s);

    int count = 0;
    for(auto f : faults){
        if (count < 13)
            ui->vl_fault1->addWidget(f.get());
        if (count >= 14 && count < 28)
            ui->vl_fault2->addWidget(f.get());

        count ++;
    }

    for(auto p : packets){
        for(auto f : faults){
            connect(p.get(), SIGNAL(updatebit(int, int, bool)), f.get(), SLOT(activatecolor(int, int, bool)));
        }
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
    this->close();
}

void faultdialog::getFaults(uint32_t newfaultmap)
{

}

void faultdialog::getWarnings(uint32_t newwarningsmap)
{

}

