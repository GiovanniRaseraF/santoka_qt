#ifndef FAULTDIALOG_H
#define FAULTDIALOG_H

#include <QDialog>
#include <QMap>
#include <QVector>

#include <map>
#include <vector>
#include <memory>

#include "widgets/hp_faultwarning.h"
#include "candata/singlefaultwarningpacket.h"
#include "widgets/hp_faultdesing.h"

namespace Ui {
class faultdialog;
}


class faultdialog : public QDialog
{
    Q_OBJECT

public:
    explicit faultdialog(std::shared_ptr<canbus_thread> canbus = nullptr,QWidget *parent = nullptr);
    ~faultdialog();

private slots:
    void on_faultdialog_accepted();

    void getFaults(uint32_t newfaultmap);
    void getWarnings(uint32_t newwarningsmap);

    void on_pb_close_clicked();

private:
    Ui::faultdialog *ui;


    // packets

    std::vector<std::shared_ptr<singlefaultwarningpacket>> packets;

    // designs
    std::vector<std::shared_ptr<hp_faultwarning>> faults{
        std::make_shared<hp_faultdesing>("test", 0x506, 1, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 3, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 9, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 3, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 1, this),

        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 34, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 12, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 9, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
        std::make_shared<hp_faultdesing>("test", 0x506, 6, this),
    };
};

#endif // FAULTDIALOG_H
