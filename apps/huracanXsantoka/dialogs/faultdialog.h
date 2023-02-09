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

namespace Ui {
class faultdialog;
}


class faultdialog : public QDialog
{
    Q_OBJECT

public:
    explicit faultdialog(QWidget *parent = nullptr);
    ~faultdialog();

private slots:
    void on_faultdialog_accepted();

    void getFaults(uint32_t newfaultmap);
    void getWarnings(uint32_t newwarningsmap);

    void on_pb_close_clicked();

private:
    Ui::faultdialog *ui;

    // all fault warnings informations
    std::vector<singlefaultwarningpacket> packets{
        singlefaultwarningpacket(this)
    };

    // faults
    std::vector<std::shared_ptr<hp_faultwarning>> faultsgraphics{
        //{1, std::make_shared<hp_faultwarning>("No motor", nullptr)},
        //{2, std::make_shared<hp_faultwarning>("No can", nullptr)}

    };



    // warnings
};

#endif // FAULTDIALOG_H
