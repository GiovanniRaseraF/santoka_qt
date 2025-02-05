#ifndef BATTERYPAGE_H
#define BATTERYPAGE_H

#include <QMainWindow>
#include <memory>

#include "dataproducer.h"
#include "displayer/evbms_0x351_filter.h"
#include "displayer/evbms_0x355_filter.h"
#include "displayer/evbms_0x356_filter.h"
#include "displayer/evbms_0x358_filter.h"

#define PASSSHARED(cl, name) \
    std::shared_ptr<cl> name = nullptr

#define PASSSHARED_NONULL(cl, name) \
    std::shared_ptr<cl> name

namespace Ui {
class batterypage;
}

class batterypage : public QMainWindow
{
    Q_OBJECT

public:
    explicit batterypage(QWidget *parent = nullptr);
    ~batterypage();

    void connectInformations(
        PASSSHARED(evbms_0x351, _ev0x351),
        PASSSHARED(evbms_0x355, _ev0x355),
        PASSSHARED(evbms_0x356, _ev0x356),
        PASSSHARED(evbms_0x358, _ev0x358)
    );

private slots:
    void on_pb_close_clicked();
    // 0x355
    void setSOC(uint16_t newSOC);
    void setSOH(uint16_t newSOH);
    void setResidualDischargeTime(uint16_t newRDT);
    void setCapacity(uint16_t newC);

    // 0x351
    void setCharginVoltageLimit(float v);
    void setCharginCurrentLimit(float v);
    void setDischargeCurrentLimit(float v);
    void setDischargeVoltageLimit(float v);

    // 0x356
    void setVoltage(float v);
    void setCurrent(float v);

    // 0x358
    void setMaxCellVoltage(uint16_t);
    void setModuleMaxVoltage(uint8_t);
    void setCellMaxVoltage(uint8_t);
    void setMinCellVoltage(uint16_t);
    void setModuleMinVoltage(uint8_t);
    void setCellMinVoltage(uint8_t);

private:
    Ui::batterypage *ui;
    // Can bus producer thread
    std::shared_ptr<canbus_thread> canbus;

    // evbms
    std::shared_ptr<evbms_0x351> ev0x351;
    std::shared_ptr<evbms_0x355> ev0x355;
    std::shared_ptr<evbms_0x356> ev0x356;
    std::shared_ptr<evbms_0x358> ev0x358;
};
#endif // BATTERYPAGE_H
