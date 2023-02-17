#include "faultsandwarnings.h"
#include "ui_faultsandwarnings.h"
#include "loaders/hp_faultwarning_loader.h"

faultsandwarnings::faultsandwarnings(std::shared_ptr<canbus_thread> canbus, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::faultsandwarnings)
{
    ui->setupUi(this);

    // loading faults
    hp_faultwarning_loader faultloader(nullptr);
    faultloader.loadfromfile(":/configuration/configuration.json");

    faults = std::move(faultloader.faults);
    warnings = std::move(faultloader.warnings);
    packets = std::move(faultloader.packets);

    for(auto p : packets){
        p->addproducer(canbus);
    }

    // connect information to design
    loadDesignIntoColumns();
    connectDesign();
}

faultsandwarnings::~faultsandwarnings()
{
    delete ui;
}

void faultsandwarnings::connectDesign()
{
    for(auto p : packets) {
        for(auto f : faults){
            if(p->canchannel == f->canchannel)
                connect(p.get(), SIGNAL(updatebit(int, int, bool)), f.get(), SLOT(activatecolor(int, int, bool)));
        }
        for(auto w : warnings){
            if(p->canchannel == w->canchannel)
                connect(p.get(), SIGNAL(updatebit(int, int, bool)), w.get(), SLOT(activatecolor(int, int, bool)));
        }
    }
}

void faultsandwarnings::loadDesignIntoColumns()
{
    const int MAX_X_COLUMN = 16;
    int count = 0;
    for(auto f : faults){
        if (count <= MAX_X_COLUMN)
            ui->vl_fault1->addWidget(f.get());
        if (count >= MAX_X_COLUMN + 1 && count < 2 * (MAX_X_COLUMN + 1)+1)
            ui->vl_fault2->addWidget(f.get());
        if (count > 2 * (MAX_X_COLUMN + 1)+1  && count < 3 * (MAX_X_COLUMN + 1)+3)
            ui->vl_fault3->addWidget(f.get());
        count ++;
    }

    count = 0;
    for(auto w : warnings){
        if (count <= MAX_X_COLUMN-4)
            ui->vl_warnings1->addWidget(w.get());
        if (count >= MAX_X_COLUMN-3 && count < 2 * (MAX_X_COLUMN + 1)+1)
            ui->vl_warnings2->addWidget(w.get());

        count ++;
    }
}

void faultsandwarnings::on_pb_close_clicked()
{
      this->hide();
}

