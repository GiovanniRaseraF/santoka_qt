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
#include "widgets/hp_warningdesign.h"

namespace Ui {
class faultdialog;
}


class faultdialog : public QDialog
{
    Q_OBJECT

public:
    explicit faultdialog(std::shared_ptr<canbus_thread> canbus = nullptr,QWidget *parent = nullptr);
    ~faultdialog();

private:
    void connectDesign();
    void loadDesignIntoColumns();

private slots:
    void on_faultdialog_accepted();
    void on_pb_close_clicked();

private:
    Ui::faultdialog *ui;

    // packets
    std::vector<std::shared_ptr<singlefaultwarningpacket>> packets;

    // designs
    std::vector<std::shared_ptr<hp_faultdesing>> faults;
    std::vector<std::shared_ptr<hp_warningdesign>> warnings;
};

#endif // FAULTDIALOG_H
