#ifndef MOTOR_FILTER_H
#define MOTOR_FILTER_H

#include <QObject>
#include <QWidget>

#include <memory>
#include <chrono>

#include "filter.h"

class motor_filter : public filter
{
    Q_OBJECT
public:
    explicit motor_filter(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);

signals:
    void new_drv_dcBusVoltage(float);
    void new_drv_motorCurrent(float);
    void new_drv_motorVoltage(float);
    void new_drv_motorSpeed(uint16_t);
    void new_drv_referement(uint16_t);
    void new_drv_currentLimit(uint16_t);
    void new_drv_regenerationLimit(uint16_t);
    void new_drv_powerTemperature(uint8_t);
    void new_drv_motorTemperature(uint8_t);
    void new_drv_status(uint8_t);
    void new_drv_warnings(uint32_t);
    void new_drv_faults(uint32_t);

    void to_QString(QString) override;

public slots:
    void receivednewframe(const can_frame newframe);

private:
    float drv_dcBusVoltage = 0; 			// V
    float drv_motorCurrent = 0;				// A
    float drv_motorVoltage = 0;				// V
    uint16_t drv_motorSpeed = 0;			// rpm
    uint16_t drv_referement = 0;			// rpm
    uint16_t drv_currentLimit = 0;				// A
    uint16_t drv_regenerationLimit = 0;			// A
    uint8_t drv_powerTemperature = 0;			// °C
    uint8_t drv_motorTemperature = 0;			// °C
    uint8_t drv_status = 0;						// bitfield
    uint32_t drv_warnings = 0;					// bitfield
    uint32_t drv_faults = 0;						// bitfield

private:
    virtual bool canupdateinfo() override;
    QString __to_QString() override;
};

#endif // MOTOR_FILTER_H
