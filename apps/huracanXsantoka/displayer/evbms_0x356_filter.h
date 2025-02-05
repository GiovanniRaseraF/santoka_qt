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
class evbms_0x356: public filter
{
    Q_OBJECT
public:
    QString description = "";
    explicit evbms_0x356(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:
    void new_ev_Voltage(float);
    void new_ev_Current(float);
    // void new_ev_MaxCellVoltage(uint16_t);
    // void new_ev_ModuleMaxVoltage(uint8_t);
    // void new_ev_CellMaxVoltage(uint8_t);
    // void new_ev_MinCellVoltage(uint16_t);
    // void new_ev_ModuleMinVoltage(uint8_t);
    // void new_ev_CellMinVoltage(uint8_t);

public slots:
    void receivednewframe(const can_frame newframe);

private:
    float ev_Voltage = 0;
    float ev_Current = 0;
    // uint16_t ev_MaxCellVoltage = 0;
    // uint8_t ev_ModuleMaxVoltage = 0;
    // uint8_t ev_CellMaxVoltage = 0;
    // uint16_t ev_MinCellVoltage = 0;
    // uint8_t ev_ModuleMinVoltage = 0;
    // uint8_t ev_CellMinVoltage = 0;

private:
    virtual bool canupdateinfo() override;

    QString __to_QString() override;

};

#endif // EVBMS_0x356_FILTER_H
