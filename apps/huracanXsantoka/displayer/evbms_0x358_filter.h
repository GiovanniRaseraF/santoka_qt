#ifndef EVBMS_0x358_FILTER_H
#define EVBMS_0x358_FILTER_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>

#include <memory>
#include <chrono>
#include <string>

#include "filter.h"

// 0x358
class evbms_0x358: public filter
{
    Q_OBJECT
public:
    QString description = "";
    explicit evbms_0x358(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:
    void new_ev_MaxCellVoltage(uint16_t);
    void new_ev_ModuleMaxVoltage(uint8_t);
    void new_ev_CellMaxVoltage(uint8_t);
    void new_ev_MinCellVoltage(uint16_t);
    void new_ev_ModuleMinVoltage(uint8_t);
    void new_ev_CellMinVoltage(uint8_t);

public slots:
    void receivednewframe(const can_frame newframe);

private:
    uint16_t ev_MaxCellVoltage = 0;
    uint8_t ev_ModuleMaxVoltage = 0;
    uint8_t ev_CellMaxVoltage = 0;
    uint16_t ev_MinCellVoltage = 0;
    uint8_t ev_ModuleMinVoltage = 0;
    uint8_t ev_CellMinVoltage = 0;

private:
    virtual bool canupdateinfo() override;

    QString __to_QString() override;

};

#endif // EVBMS_0x358_FILTER_H
