#ifndef BATTERYPAGE_H
#define BATTERYPAGE_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>
#include <memory>

#include "dataproducer.h"
#include "displayer/evbms_0x351_filter.h"
#include "displayer/evbms_0x355_filter.h"
#include "displayer/evbms_0x356_filter.h"
#include "displayer/evbms_0x358_filter.h"
#include "displayer/evbms_0x359_filter.h"
#include "displayer/evbms_0x35A_filter.h"

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
        PASSSHARED(evbms_0x358, _ev0x358),
        PASSSHARED(evbms_0x359, _ev0x359),
        PASSSHARED(evbms_0x35A, _ev0x35A)
    );

private slots:
    void on_pb_close_clicked();
    // 0x355
    void setSOC(uint16_t newSOC);
    void setSOCBatteryGraphics(uint16_t newSOC);
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
    void setBatteryStatus(evBatteryStatus);

    // 0x358
    void setMaxCellVoltage(uint16_t);
    void setModuleMaxVoltage(uint8_t);
    void setCellMaxVoltage(uint8_t);
    void setMinCellVoltage(uint16_t);
    void setModuleMinVoltage(uint8_t);
    void setCellMinVoltage(uint8_t);

    // 0x359
    void setMaxTemperature(int16_t);
    void setModuleMaxTemp(uint8_t);
    void setCellMaxTemp(uint8_t);
    void setMinTemperature(int16_t);
    void setModuleMinTemp(uint8_t);
    void setCellMinTemp(uint8_t);

    // 0x35A
    void setWarningProtection(QVector<bool>);

    // Time
    void timeoutToUpdateDate();
    void readDateFromSystem();
private:
    Ui::batterypage *ui;

    QProcess *myProcess;
    QTimer *updateDatetime;

    // Can bus producer thread
    std::shared_ptr<canbus_thread> canbus;

    // evbms
    std::shared_ptr<evbms_0x351> ev0x351;
    std::shared_ptr<evbms_0x355> ev0x355;
    std::shared_ptr<evbms_0x356> ev0x356;
    std::shared_ptr<evbms_0x358> ev0x358;
    std::shared_ptr<evbms_0x359> ev0x359;
    std::shared_ptr<evbms_0x35A> ev0x35A;

    // Status
    evBatteryStatus status = STANDBY;
};
#endif // BATTERYPAGE_H
