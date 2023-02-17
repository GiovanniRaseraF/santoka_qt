#ifndef FAULTSANDWARNINGS_H
#define FAULTSANDWARNINGS_H

#include <QMainWindow>

#include <map>
#include <vector>
#include <memory>

#include "widgets/hp_faultwarning.h"
#include "candata/singlefaultwarningpacket.h"
#include "widgets/hp_faultdesing.h"
#include "widgets/hp_warningdesign.h"

namespace Ui {
class faultsandwarnings;
}

class faultsandwarnings : public QMainWindow
{
    Q_OBJECT

public:
    explicit faultsandwarnings(std::shared_ptr<canbus_thread> canbus = nullptr, QWidget *parent = nullptr);
    ~faultsandwarnings();
private:
    void connectDesign();
    void loadDesignIntoColumns();

private slots:
    void on_pb_close_clicked();

private:
    Ui::faultsandwarnings *ui;

    // packets
    std::vector<std::shared_ptr<singlefaultwarningpacket>> packets;

    // designs
    std::vector<std::shared_ptr<hp_faultdesing>> faults;
    std::vector<std::shared_ptr<hp_warningdesign>> warnings;
};

#endif // FAULTSANDWARNINGS_H
