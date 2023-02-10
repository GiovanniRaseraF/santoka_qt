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

    std::shared_ptr<singlefaultwarningpacket> w = std::make_shared<singlefaultwarningpacket>();
    w->canchannel = 0x507;
    w->importantbits = {1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38};
    w->addproducer(canbus);
    packets.push_back(w);

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
        connect(packets[1].get(), SIGNAL(updatebit(int, int, bool)), w.get(), SLOT(activatecolor(int, int, bool)));
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
