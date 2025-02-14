#ifndef EVBMS_0x356_FILTER_H
#define EVBMS_0x356_FILTER_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>

#include <memory>
#include <chrono>
#include <string>

#include "filter.h"

// 0x356
enum evBatteryStatus{
    CHARGING, DISCHARGING, STANDBY
};

class evbms_0x356: public filter
{
    Q_OBJECT
public:
    QString description = "";
    explicit evbms_0x356(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:
    void new_ev_Voltage(float);
    void new_ev_Current(float);
    void new_ev_Status(evBatteryStatus);

public slots:
    void receivednewframe(const can_frame newframe);

private:
    float ev_Voltage = 0;
    float ev_Current = 0;

private:
    virtual bool canupdateinfo() override;

    QString __to_QString() override;

};

#endif // EVBMS_0x356_FILTER_H
