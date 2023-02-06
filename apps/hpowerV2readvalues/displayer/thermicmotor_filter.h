#ifndef THERMICMOTOR_FILTER_H
#define THERMICMOTOR_FILTER_H

#include <QObject>
#include <QWidget>

#include <memory>
#include <chrono>

#include "filter.h"

class thermicmotor_filter : public filter
{
    Q_OBJECT
public:
    explicit thermicmotor_filter(std::shared_ptr<canbus_thread> canbus_producer = nullptr, QObject *parent = nullptr);


public slots:
    void receivednewframe(const can_frame newframe);

signals:
    void new_dsl_engineSpeed(uint16_t);
    void new_dsl_coolingTemperature(int8_t);
    void new_dsl_batteryVoltage(float);
    void new_dsl_Throttle(uint8_t);
    void new_dsl_GlowPlugStatus(uint8_t);
    void new_dsl_status(uint8_t);
    void new_dsl_FuelLevel1(uint8_t);
    void new_dsl_FuelLevel2(uint8_t);

private:
    uint16_t dsl_engineSpeed = 0;      // rpm
    int8_t dsl_coolingTemperature = 0; // °C
    float dsl_batteryVoltage = 0;      // V
    uint8_t dsl_Throttle = 0;          // %
    uint8_t dsl_GlowPlugStatus = 0;    // 0:OFF; 1:ON
    uint8_t dsl_status = 0;            // 0 = WAIT; 10 = WAIT CRANKING; 50 = RUNNING; 110 = FAULT
    uint8_t dsl_FuelLevel1 = 0;        // %
    uint8_t dsl_FuelLevel2 = 0;        // %

private:
    virtual bool canupdateinfo() override;
};

#endif // THERMICMOTOR_FILTER_H
